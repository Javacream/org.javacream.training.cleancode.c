/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double total_case(int n){double p[]={2,3};unsigned q[]={4,5};return total(p,q,(size_t)n);}
