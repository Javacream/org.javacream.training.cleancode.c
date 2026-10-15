#include <stdio.h>
#include "counter.h"
int main(void) { Counter *c = counter_create(); if (!c) return 1; counter_increment(c); printf("%d\n", counter_value(c)); counter_destroy(c);  return 0; }
