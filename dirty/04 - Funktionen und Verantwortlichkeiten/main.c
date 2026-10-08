#include <stdio.h>
void process_order(int unit_price, int quantity, const char *customer,
                   int premium, int print_details, int shipping_fee)
{
    int total = unit_price * quantity;
    if (quantity <= 0) { printf("Invalid quantity\n"); return; }
    if (premium) total -= total / 10;
    total += shipping_fee;
    if (print_details) printf("Customer: %s\n", customer);
    printf("Total: %d\n", total);
    if (total > 500) printf("Large order\n");
}
int main(void)
{
    process_order(120, 5, "Miller", 1, 1, 10);
    return 0;
}
