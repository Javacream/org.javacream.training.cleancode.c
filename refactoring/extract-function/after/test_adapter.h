/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double invoice_case(int n){double p[]={10,20};return invoice_total(p,n==0?0:2,n==1?0.19:0);}
