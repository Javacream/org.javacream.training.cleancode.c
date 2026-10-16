/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int buffer_case(void){char *p=buffer_create();if(!p)return 0;p[0]='x';buffer_destroy(p);return 1;}
