/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int order_case(int n){int items[]={1,2};Order o;o.items=n==1?NULL:items;o.count=n==2?0:2;return n==0?process(NULL):process(&o);}
