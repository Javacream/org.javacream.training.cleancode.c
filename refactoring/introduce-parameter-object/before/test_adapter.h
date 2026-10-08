/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double shipping_case(double w,double d){return shipping(w,d,5,0.1,0.5);}
