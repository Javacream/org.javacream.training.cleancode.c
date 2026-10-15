#include <stdio.h>
#include "counter.h"
int main(void) { Counter c = {0}; c.value++; printf("%d\n", c.value);  return 0; }
