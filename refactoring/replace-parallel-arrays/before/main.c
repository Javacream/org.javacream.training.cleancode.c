#include <stdio.h>
#include <stddef.h>
double total(const double *prices, const unsigned *qty, size_t n) {
    size_t i;
    double sum = 0;
    for (i = 0; i < n; ++i) sum += prices[i] * qty[i];
    return sum;
}
int main(void) { double p[] = {2, 3}; unsigned q[] = {4, 5}; printf("%.2f\n", total(p, q, 2));  return 0; }
