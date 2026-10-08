#include <stdio.h>
#include <string.h>

void process_order(int price, int quantity, const char *customer, int premium)
{
    int total = price * quantity;
    if (premium) total -= total / 10;
    printf("Customer: %s\n", customer);
    printf("Total: %d\n", total);
    if (total > 500) printf("Large order\n");
}

int main(void)
{
    process_order(120, 5, "Miller", 1);
    return 0;
}
