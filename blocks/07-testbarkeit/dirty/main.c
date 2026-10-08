#include <stdio.h>

int current_tax_rate = 19;

int final_price(int net)
{
    int gross = net + net * current_tax_rate / 100;
    printf("Calculated: %d\n", gross);
    return gross;
}

int main(void)
{
    final_price(100);
    return 0;
}
