/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double parse_case(const char *s){double result;if(!parse_temperature(s,&result))return -9999;return result;}
