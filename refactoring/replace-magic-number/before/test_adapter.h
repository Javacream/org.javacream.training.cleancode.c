/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double tax_case(double n){return surcharge(n);} static double gross_case(double n){return gross(n);}
