#include <stdio.h>
typedef enum { STANDARD, EXPRESS, OVERNIGHT } ShippingType;
typedef double (*Calculator)(double);
static double standard(double w) { return 5 + w * 0.5; }
static double express(double w) { return 10 + w; }
static double overnight(double w) { return 20 + w * 2; }
static const Calculator table[] = {standard, express, overnight};
double shipping(ShippingType type, double weight) {
    if ((int)type < 0 || (int)type >= (int)(sizeof table / sizeof table[0])) return -1;
    return table[type](weight);
}
int main(void) { printf("%.2f\n", shipping(EXPRESS, 3));  return 0; }
