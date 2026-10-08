#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"
#include "postgres_store.h"

static int self_test(void) {
    int fee, ok = 1;
    ok = ok && shipping_cost(9999, 5000, SHIPPING_STANDARD, &fee) && fee == 500;
    ok = ok && shipping_cost(10000, 5000, SHIPPING_STANDARD, &fee) && fee == 0;
    ok = ok && shipping_cost(10000, 5001, SHIPPING_STANDARD, &fee) && fee == 300;
    ok = ok && shipping_cost(10000, 5001, SHIPPING_EXPRESS, &fee) && fee == 1500;
    ok = ok && !shipping_cost(10000, 0, 3, &fee);
    puts(ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
static int integration_test(const char *conninfo) {
    Order order, loaded;
    OrderItem items[2];
    int ok;
    if (!conninfo) { fputs("PG_CONNINFO fehlt\n", stderr); return 1; }
    /* Dedicated test ID: run only against an isolated training database. */
    order.id = 900001; order.customer = 4711; order.subtotal_cents = 9200;
    order.weight_grams = 2200; order.shipping = SHIPPING_STANDARD; order.status = 1;
    items[0].position = 1; items[0].article_code = "A-100";
    items[0].quantity = 2; items[0].unit_price_cents = 3000;
    items[1].position = 2; items[1].article_code = "B-200";
    items[1].quantity = 1; items[1].unit_price_cents = 3200;
    ok = postgres_save_order(conninfo, &order, items, 2);
    ok = ok && postgres_find_order(conninfo, order.id, &loaded);
    ok = ok && loaded.subtotal_cents == 9200 && loaded.status == 1;
    /* Duplicate position violates PK: transaction must roll back. */
    items[1].position = 1;
    order.subtotal_cents = 9999;
    ok = ok && !postgres_save_order(conninfo, &order, items, 2);
    ok = ok && postgres_find_order(conninfo, order.id, &loaded);
    ok = ok && loaded.subtotal_cents == 9200;
    ok = ok && postgres_cancel_order(conninfo, order.id);
    ok = ok && postgres_find_order(conninfo, order.id, &loaded);
    ok = ok && loaded.status == 0;
    puts(ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
int main(int argc, char **argv) {
    const char *conninfo;
    Order order;
    OrderItem items[2];
    if (argc > 1 && strcmp(argv[1], "--self-test") == 0) return self_test();
    conninfo = getenv("PG_CONNINFO");
    if (argc > 1 && strcmp(argv[1], "--integration-test") == 0)
        return integration_test(conninfo);
    if (!conninfo) { fputs("PG_CONNINFO fehlt\n", stderr); return 1; }
    order.id = 1001; order.customer = 4711; order.subtotal_cents = 9200;
    order.weight_grams = 2200; order.shipping = SHIPPING_STANDARD; order.status = 1;
    items[0].position = 1; items[0].article_code = "A-100";
    items[0].quantity = 2; items[0].unit_price_cents = 3000;
    items[1].position = 2; items[1].article_code = "B-200";
    items[1].quantity = 1; items[1].unit_price_cents = 3200;
    if (!postgres_save_order(conninfo, &order, items, 2)) {
        fputs("Transaktion fehlgeschlagen\n", stderr); return 1;
    }
    puts("Auftrag und Positionen atomar gespeichert");
    return 0;
}
