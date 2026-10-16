/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int counter_case(int n){Counter *c=counter_create();int i;int result;if(!c)return -1;for(i=0;i<n;i++)counter_increment(c);result=counter_value(c);counter_destroy(c);return result;}
