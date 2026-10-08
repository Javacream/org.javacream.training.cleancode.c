#include <stdio.h>

#define PREMIUM_CUSTOMER 1
#define EXPRESS_CODE 7
#define LARGE_ORDER_LIMIT 100

static int calculate_base_price(int unit_price, int quantity)
{
    return unit_price * quantity;
}

static int apply_discounts_and_fees(int total, int premium_customer, int order_size, int shipping_code)
{
    if (premium_customer == PREMIUM_CUSTOMER) total -= total / 10;
    if (order_size > LARGE_ORDER_LIMIT) total += 15;
    if (shipping_code == EXPRESS_CODE) total += 5;
    return total;
}

int main(void)
{
    int total = calculate_base_price(50, 4);
    total = apply_discounts_and_fees(total, PREMIUM_CUSTOMER, 120, EXPRESS_CODE);
    printf("%d\n", total);
    return 0;
}
