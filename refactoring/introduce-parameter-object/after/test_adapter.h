/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double shipping_case(double w,double d){Shipment s;Tariff t;s.weight=w;s.distance=d;t.base=5;t.per_km=0.1;t.per_kg=0.5;return shipping(&s,&t);}
