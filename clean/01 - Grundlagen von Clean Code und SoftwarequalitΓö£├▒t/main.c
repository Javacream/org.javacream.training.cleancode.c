#include <stdio.h>

#define BULK_THRESHOLD 300
#define BULK_DISCOUNT 30

static int calculate_total(int unit_price, int quantity)
{
    int total = unit_price * quantity;
    if (total > BULK_THRESHOLD) {
        total -= BULK_DISCOUNT;
    }
    return total;
}

int main(void)
{
    int unit_price = 120;
    int quantity = 3;
    int total = calculate_total(unit_price, quantity);
    printf("Total: %d\n", total);
    return 0;
}
