#include <stdio.h>

static int calculate_total(int price, int quantity)
{
    return price * quantity;
}

static int apply_premium_discount(int total, int premium)
{
    if (premium) return total - total / 10;
    return total;
}

static void print_order(const char *customer, int total)
{
    printf("Customer: %s\n", customer);
    printf("Total: %d\n", total);
    if (total > 500) printf("Large order\n");
}

static void process_order(int price, int quantity, const char *customer, int premium)
{
    int total = calculate_total(price, quantity);
    total = apply_premium_discount(total, premium);
    print_order(customer, total);
}

int main(void)
{
    process_order(120, 5, "Miller", 1);
    return 0;
}
