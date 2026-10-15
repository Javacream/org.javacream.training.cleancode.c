#include <stdio.h>
#include <stddef.h>
static double subtotal(const double *prices, size_t count) {
    size_t i;
    double sum = 0;
    for (i = 0; i < count; ++i) sum += prices[i];
    return sum;
}
double invoice_total(const double *prices, size_t count, double tax_rate) {
    double net = subtotal(prices, count);
    return net + net * tax_rate;
}
int main(void) { double p[] = {10, 20}; printf("%.2f\n", invoice_total(p, 2, 0.19));  return 0; }
