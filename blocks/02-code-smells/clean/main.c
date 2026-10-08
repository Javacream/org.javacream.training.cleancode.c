#include <stdio.h>
/* Diagnosebeispiel: nur offensichtlichen Ballast entfernen.
   Die Duplikation und der globale Zustand bleiben bewusst für spätere Blöcke. */
int last_total = 0;
int process(int price, int quantity, int premium, int delivery)
{
    int total = price * quantity;
    if (premium) total -= total / 10;
    if (delivery == 1) total += 15;
    last_total = total;
    printf("Order A: %d\n", total);
    total = price * (quantity + 1);
    if (premium) total -= total / 10;
    if (delivery == 1) total += 15;
    last_total = total;
    printf("Order B: %d\n", total);
    return total;
}
int main(void)
{
    process(80, 4, 1, 1);
    printf("Last: %d\n", last_total);
    return 0;
}
