#include <stdio.h>
typedef struct { const char *customer; int unit_price; int quantity; int premium; int shipping_fee; } Order;
static int is_valid_order(const Order *order) { return order->quantity > 0; }
static int calculate_total(const Order *order)
{
    int total = order->unit_price * order->quantity;
    if (order->premium) total -= total / 10;
    return total + order->shipping_fee;
}
static void print_receipt(const Order *order, int total)
{
    printf("Customer: %s\n", order->customer);
    printf("Total: %d\n", total);
    if (total > 500) printf("Large order\n");
}
static void process_order(const Order *order)
{
    if (!is_valid_order(order)) { printf("Invalid quantity\n"); return; }
    print_receipt(order, calculate_total(order));
}
int main(void)
{
    Order order = { "Miller", 120, 5, 1, 10 };
    process_order(&order);
    return 0;
}
