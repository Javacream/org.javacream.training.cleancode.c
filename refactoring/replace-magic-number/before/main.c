#include <stdio.h>
double surcharge(double net) { return net * 0.19; }
double gross(double net) { return net * 1.19; }
int main(void) { printf("%.2f %.2f\n", surcharge(100), gross(100));  return 0; }
