#include "counter.h"
#include <stdlib.h>
struct Counter { int value; };
Counter *counter_create(void) { return calloc(1, sizeof(Counter)); }
void counter_increment(Counter *counter) { if (counter) ++counter->value; }
int counter_value(const Counter *counter) { return counter ? counter->value : 0; }
void counter_destroy(Counter *counter) { free(counter); }
