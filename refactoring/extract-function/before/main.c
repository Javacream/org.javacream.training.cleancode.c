#include <stdio.h>
#include <stddef.h>
double invoice_total(const double *prices, size_t count, double tax_rate) {
    size_t i;
    double subtotal = 0;
    for (i = 0; i < count; ++i) subtotal += prices[i];
    return subtotal + subtotal * tax_rate;
}
int main(void) { double p[] = {10, 20}; printf("%.2f\n", invoice_total(p, 2, 0.19));  return 0; }
