/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double shipping_case(int type,double w){return shipping((ShippingType)type,w);}
