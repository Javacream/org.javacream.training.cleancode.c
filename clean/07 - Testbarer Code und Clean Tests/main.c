#include <stdio.h>

int calculate_gross_price(int net, int tax_rate)
{
    return net + net * tax_rate / 100;
}

int main(void)
{
    int gross = calculate_gross_price(100, 19);
    printf("Calculated: %d\n", gross);
    return 0;
}
