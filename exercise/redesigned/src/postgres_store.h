#ifndef POSTGRES_STORE_H
#define POSTGRES_STORE_H
#include "order.h"
typedef struct {
    int position;
    const char *article_code;
    int quantity;
    int unit_price_cents;
} OrderItem;
/* A successful save replaces the complete set of order items atomically. */
int postgres_save_order(const char *conninfo, const Order *order,
                        const OrderItem *items, int count);
int postgres_find_order(const char *conninfo, int id, Order *order);
int postgres_cancel_order(const char *conninfo, int id);
#endif
