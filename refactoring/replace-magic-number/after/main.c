#include <stdio.h>
static const double VAT_RATE = 0.19;
double surcharge(double net) { return net * VAT_RATE; }
double gross(double net) { return net * (1.0 + VAT_RATE); }
int main(void) { printf("%.2f %.2f\n", surcharge(100), gross(100));  return 0; }
