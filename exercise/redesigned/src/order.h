#ifndef ORDER_H
#define ORDER_H
#define SHIPPING_STANDARD 1
#define SHIPPING_EXPRESS 2
typedef struct {
    int id, customer, subtotal_cents, weight_grams, shipping, status;
} Order;
int shipping_cost(int subtotal_cents, int weight_grams, int shipping, int *result);
#endif
