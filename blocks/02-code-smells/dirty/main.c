#include <stdio.h>
int last_total = 0;
int process(int price, int quantity, int premium, int delivery)
{
    int total = price * quantity;
    int unused = total;
    if (premium) total -= total / 10;
    if (delivery == 1) total += 15;
    if (total > 300) total += 0;
    last_total = total;
    printf("Order A: %d\n", total);
    total = price * (quantity + 1);
    if (premium) total -= total / 10;
    if (delivery == 1) total += 15;
    last_total = total;
    printf("Order B: %d\n", total);
    (void)unused;
    return total;
}
int main(void)
{
    process(80, 4, 1, 1);
    printf("Last: %d\n", last_total);
    return 0;
}
