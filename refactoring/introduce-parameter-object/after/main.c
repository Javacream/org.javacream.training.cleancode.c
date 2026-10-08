#include <stdio.h>
typedef struct { double weight, distance; } Shipment;
typedef struct { double base, per_km, per_kg; } Tariff;
double shipping(const Shipment *s, const Tariff *t) {
    return t->base + s->distance * t->per_km + s->weight * t->per_kg;
}
int main(void) { Shipment s = {2, 100}; Tariff t = {5, 0.1, 0.5}; printf("%.2f\n", shipping(&s, &t));  return 0; }
