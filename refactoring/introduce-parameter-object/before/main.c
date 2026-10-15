#include <stdio.h>
double shipping(double weight, double distance, double base, double per_km, double per_kg) {
    return base + distance * per_km + weight * per_kg;
}
int main(void) { printf("%.2f\n", shipping(2, 100, 5, 0.1, 0.5));  return 0; }
