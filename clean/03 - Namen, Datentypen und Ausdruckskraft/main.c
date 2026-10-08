#include <stdio.h>

#define DISCOUNT_THRESHOLD 1000
#define DISCOUNT_AMOUNT 50

static int calculate_order_total(int unit_price, int quantity)
{
    int order_total = unit_price * quantity;
    if (order_total > DISCOUNT_THRESHOLD) {
        order_total -= DISCOUNT_AMOUNT;
    }
    return order_total;
}

int main(void)
{
    int unit_price = 25;
    int quantity = 50;
    printf("%d\n", calculate_order_total(unit_price, quantity));
    return 0;
}
