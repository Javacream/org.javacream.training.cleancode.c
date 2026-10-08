#ifndef ORDER_H
#define ORDER_H
#define MAX_ORDERS 100
#define SHIPPING_STANDARD 1
#define SHIPPING_EXPRESS 2
#define ORDER_OPEN 1
#define ORDER_CANCELLED 0
typedef struct {
    int id;
    int customer;
    int subtotal_cents;
    int weight_grams;
    int shipping;
    int status;
} Order;
typedef struct { Order items[MAX_ORDERS]; int count; } OrderList;
int shipping_cost(int subtotal_cents, int weight_grams, int shipping, int *result);
int order_add(OrderList *list, int id, int customer, int cents, int grams, int shipping);
int order_cancel(OrderList *list, int id);
int order_total(const OrderList *list, int id, int *result);
#endif
