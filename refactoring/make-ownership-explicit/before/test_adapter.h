/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static int buffer_case(void){char *p=create_buffer();if(!p)return 0;p[0]='x';free(p);return 1;}
