#include <stdio.h>
#include <stddef.h>
typedef struct { double price; unsigned quantity; } LineItem;
double total(const LineItem *items, size_t n) {
    size_t i;
    double sum = 0;
    for (i = 0; i < n; ++i) sum += items[i].price * items[i].quantity;
    return sum;
}
int main(void) { LineItem items[] = {{2, 4}, {3, 5}}; printf("%.2f\n", total(items, 2));  return 0; }
