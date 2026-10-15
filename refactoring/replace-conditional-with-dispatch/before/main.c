#include <stdio.h>
typedef enum { STANDARD, EXPRESS, OVERNIGHT } ShippingType;
double shipping(ShippingType type, double weight) {
    switch (type) {
        case STANDARD: return 5 + weight * 0.5;
        case EXPRESS: return 10 + weight;
        case OVERNIGHT: return 20 + weight * 2;
    }
    return -1;
}
int main(void) { printf("%.2f\n", shipping(EXPRESS, 3));  return 0; }
