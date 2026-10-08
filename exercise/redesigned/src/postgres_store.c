#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include "postgres_store.h"

static int command(PGconn *connection, const char *sql, int count,
                   const char *const *params) {
    PGresult *result;
    int ok;
    result = PQexecParams(connection, sql, count, NULL, params, NULL, NULL, 0);
    ok = result && PQresultStatus(result) == PGRES_COMMAND_OK;
    if (result) PQclear(result);
    return ok;
}
static PGconn *connect_db(const char *conninfo) {
    PGconn *connection;
    if (!conninfo) return NULL;
    connection = PQconnectdb(conninfo);
    if (!connection) return NULL;
    if (PQstatus(connection) != CONNECTION_OK) {
        PQfinish(connection);
        return NULL;
    }
    return connection;
}
int postgres_save_order(const char *conninfo, const Order *order,
                        const OrderItem *items, int count) {
    PGconn *connection;
    char id[24], customer[24], cents[24], grams[24], shipping[24], status[24];
    char pos[24], qty[24], price[24];
    const char *values[6], *item_values[5];
    int i, ok, fee;
    if (!order || order->id <= 0 || order->customer <= 0 ||
        (order->status != 0 && order->status != 1) ||
        count < 0 || (count > 0 && !items) ||
        !shipping_cost(order->subtotal_cents, order->weight_grams,
                       order->shipping, &fee)) return 0;
    for (i = 0; i < count; ++i)
        if (items[i].position <= 0 || !items[i].article_code ||
            items[i].quantity <= 0 || items[i].unit_price_cents < 0) return 0;
    connection = connect_db(conninfo);
    if (!connection) return 0;
    sprintf(id, "%d", order->id);
    sprintf(customer, "%d", order->customer);
    sprintf(cents, "%d", order->subtotal_cents);
    sprintf(grams, "%d", order->weight_grams);
    sprintf(shipping, "%d", order->shipping);
    sprintf(status, "%d", order->status);
    values[0] = id; values[1] = customer; values[2] = cents;
    values[3] = grams; values[4] = shipping; values[5] = status;
    ok = command(connection, "BEGIN", 0, NULL);
    if (ok) ok = command(connection,
        "INSERT INTO orders(id,customer,subtotal_cents,weight_grams,shipping,status) "
        "VALUES($1,$2,$3,$4,$5,$6) ON CONFLICT(id) DO UPDATE SET "
        "customer=EXCLUDED.customer,subtotal_cents=EXCLUDED.subtotal_cents,"
        "weight_grams=EXCLUDED.weight_grams,shipping=EXCLUDED.shipping,status=EXCLUDED.status",
        6, values);
    if (ok) ok = command(connection,
        "DELETE FROM order_items WHERE order_id=$1", 1, values);
    for (i = 0; ok && i < count; ++i) {
        sprintf(pos, "%d", items[i].position);
        sprintf(qty, "%d", items[i].quantity);
        sprintf(price, "%d", items[i].unit_price_cents);
        item_values[0] = id; item_values[1] = pos;
        item_values[2] = items[i].article_code;
        item_values[3] = qty; item_values[4] = price;
        ok = command(connection,
            "INSERT INTO order_items(order_id,position,article_code,quantity,unit_price_cents) "
            "VALUES($1,$2,$3,$4,$5)", 5, item_values);
    }
    if (ok) ok = command(connection, "COMMIT", 0, NULL);
    if (!ok) command(connection, "ROLLBACK", 0, NULL);
    PQfinish(connection);
    return ok;
}
int postgres_find_order(const char *conninfo, int id, Order *order) {
    PGconn *connection;
    PGresult *result;
    char id_text[24];
    const char *params[1];
    int found = 0;
    if (!order || id <= 0) return 0;
    connection = connect_db(conninfo);
    if (!connection) return 0;
    sprintf(id_text, "%d", id);
    params[0] = id_text;
    result = PQexecParams(connection,
        "SELECT id,customer,subtotal_cents,weight_grams,shipping,status "
        "FROM orders WHERE id=$1", 1, NULL, params, NULL, NULL, 0);
    if (result && PQresultStatus(result) == PGRES_TUPLES_OK &&
        PQntuples(result) == 1) {
        order->id = atoi(PQgetvalue(result, 0, 0));
        order->customer = atoi(PQgetvalue(result, 0, 1));
        order->subtotal_cents = atoi(PQgetvalue(result, 0, 2));
        order->weight_grams = atoi(PQgetvalue(result, 0, 3));
        order->shipping = atoi(PQgetvalue(result, 0, 4));
        order->status = atoi(PQgetvalue(result, 0, 5));
        found = 1;
    }
    if (result) PQclear(result);
    PQfinish(connection);
    return found;
}
int postgres_cancel_order(const char *conninfo, int id) {
    PGconn *connection;
    PGresult *result;
    char id_text[24];
    const char *params[1];
    int ok = 0;
    if (id <= 0) return 0;
    connection = connect_db(conninfo);
    if (!connection) return 0;
    sprintf(id_text, "%d", id);
    params[0] = id_text;
    result = PQexecParams(connection,
        "UPDATE orders SET status=0 WHERE id=$1 AND status=1",
        1, NULL, params, NULL, NULL, 0);
    if (result && PQresultStatus(result) == PGRES_COMMAND_OK &&
        strcmp(PQcmdTuples(result), "1") == 0) ok = 1;
    if (result) PQclear(result);
    PQfinish(connection);
    return ok;
}
