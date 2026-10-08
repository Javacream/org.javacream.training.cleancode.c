#include <stdio.h>
#include <string.h>
#include "order.h"
#include "file_store.h"
static int test(void) {
    OrderList list;
    int total, fee, ok = 1;
    list.count = 0;
    ok = ok && shipping_cost(9999, 5000, SHIPPING_STANDARD, &fee) && fee == 500;
    ok = ok && shipping_cost(10000, 5000, SHIPPING_STANDARD, &fee) && fee == 0;
    ok = ok && shipping_cost(10000, 5001, SHIPPING_STANDARD, &fee) && fee == 300;
    ok = ok && shipping_cost(10000, 5001, SHIPPING_EXPRESS, &fee) && fee == 1500;
    ok = ok && !shipping_cost(10000, 0, 3, &fee);
    ok = ok && !order_add(&list, 0, 10, 100, 1, SHIPPING_STANDARD);
    ok = ok && order_add(&list, 1, 10, 10000, 5001, SHIPPING_STANDARD);
    ok = ok && !order_add(&list, 1, 10, 10000, 5001, SHIPPING_STANDARD);
    ok = ok && order_total(&list, 1, &total) && total == 10300;
    ok = ok && !order_total(&list, 999, &total);
    ok = ok && file_save("test.txt", &list) && file_load("test.txt", &list);
    ok = ok && list.count == 1 && order_total(&list, 1, &total) && total == 10300;
    ok = ok && order_cancel(&list, 1) && !order_cancel(&list, 1);
    ok = ok && file_save("test.txt", &list) && file_load("test.txt", &list);
    ok = ok && list.count == 1 && list.items[0].status == ORDER_CANCELLED;
    remove("test.txt");
    puts(ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
int main(int argc, char **argv) {
    OrderList list;
    int i, total;
    if (argc > 1 && strcmp(argv[1], "--self-test") == 0) return test();
    if (!file_load("orders.txt", &list)) { fputs("Lesefehler\n", stderr); return 1; }
    if (list.count == 0) {
        if (!order_add(&list, 1001, 4711, 9200, 2200, SHIPPING_STANDARD) ||
            !order_add(&list, 1002, 4712, 15000, 6100, SHIPPING_EXPRESS) ||
            !file_save("orders.txt", &list)) return 1;
    }
    for (i = 0; i < list.count; ++i) {
        if (!order_total(&list, list.items[i].id, &total)) return 1;
        printf("Auftrag %d Kunde %d: %d Cent, Status %d\n",
               list.items[i].id, list.items[i].customer, total, list.items[i].status);
    }
    return 0;
}
