#include "order.h"
#define STANDARD_FEE 500
#define EXPRESS_FEE 1200
#define HEAVY_FEE 300
#define FREE_STANDARD_FROM 10000
#define HEAVY_FROM_GRAMS 5000

int shipping_cost(int cents, int grams, int shipping, int *result) {
    int fee;
    if (!result || cents < 0 || grams < 0) return 0;
    if (shipping == SHIPPING_STANDARD)
        fee = cents >= FREE_STANDARD_FROM ? 0 : STANDARD_FEE;
    else if (shipping == SHIPPING_EXPRESS)
        fee = EXPRESS_FEE;
    else return 0;
    if (grams > HEAVY_FROM_GRAMS) fee += HEAVY_FEE;
    *result = fee;
    return 1;
}
int order_add(OrderList *list, int id, int customer, int cents, int grams, int shipping) {
    int i, fee; Order *order;
    if (!list || id <= 0 || customer <= 0 || list->count >= MAX_ORDERS ||
        !shipping_cost(cents, grams, shipping, &fee)) return 0;
    for (i = 0; i < list->count; ++i) if (list->items[i].id == id) return 0;
    order = &list->items[list->count++];
    order->id = id; order->customer = customer; order->subtotal_cents = cents;
    order->weight_grams = grams; order->shipping = shipping; order->status = ORDER_OPEN;
    return 1;
}
int order_cancel(OrderList *list, int id) {
    int i;
    if (!list) return 0;
    for (i = 0; i < list->count; ++i)
        if (list->items[i].id == id && list->items[i].status == ORDER_OPEN) {
            list->items[i].status = ORDER_CANCELLED; return 1;
        }
    return 0;
}
int order_total(const OrderList *list, int id, int *result) {
    int i, fee;
    if (!list || !result) return 0;
    for (i = 0; i < list->count; ++i)
        if (list->items[i].id == id) {
            if (!shipping_cost(list->items[i].subtotal_cents, list->items[i].weight_grams,
                               list->items[i].shipping, &fee)) return 0;
            *result = list->items[i].subtotal_cents + fee; return 1;
        }
    return 0;
}
