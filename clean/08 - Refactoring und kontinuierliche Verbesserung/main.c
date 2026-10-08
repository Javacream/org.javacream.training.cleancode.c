#include <stdio.h>

#define EXPRESS_FEE 20
#define LARGE_ORDER_THRESHOLD 1000
#define LARGE_ORDER_DISCOUNT 50

static int base_total(int unit_price, int quantity)
{
    return unit_price * quantity;
}

static int apply_premium_discount(int total, int premium)
{
    return premium ? total - total / 10 : total;
}

static int apply_express_fee(int total, int express)
{
    return express ? total + EXPRESS_FEE : total;
}

static int apply_large_order_discount(int total)
{
    return total > LARGE_ORDER_THRESHOLD ? total - LARGE_ORDER_DISCOUNT : total;
}

int calculate_order_total(int unit_price, int quantity, int premium, int express, int blocked)
{
    int total;
    if (blocked) return -1;
    total = base_total(unit_price, quantity);
    total = apply_premium_discount(total, premium);
    total = apply_express_fee(total, express);
    return apply_large_order_discount(total);
}

int main(void)
{
    printf("%d\n", calculate_order_total(100, 12, 1, 1, 0));
    return 0;
}
