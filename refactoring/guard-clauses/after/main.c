#include <stdio.h>
typedef struct { const int *items; unsigned count; } Order;
int process(const Order *o) {
    if (o == NULL) return -1;
    if (o->items == NULL) return -1;
    if (o->count == 0) return -1;
    return (int)o->count;
}
int main(void) { int items[] = {1, 2}; Order o; o.items = items; o.count = 2; printf("%d\n", process(&o));  return 0; }
