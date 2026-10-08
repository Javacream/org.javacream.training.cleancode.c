/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int counter_case(int n){Counter c;int i;c.value=0;for(i=0;i<n;i++)c.value++;return c.value;}
