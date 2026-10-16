/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int count_after(int n){int i;for(i=0;i<n;i++)record_request();return (int)request_count();}
