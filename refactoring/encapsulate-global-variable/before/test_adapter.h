/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static double value_after_deposit(double n){account_balance+=n;return account_balance;}
