#include <stdio.h>
#include "logic.h"
static int expect(const char *name, int expected, int actual)
{
    if (expected != actual) {
        printf("FAIL %s: expected %d got %d\n", name, expected, actual);
        return 1;
    }
    printf("PASS %s\n", name);
    return 0;
}
int main(void)
{
    int failures = 0;
    failures += expect("blocked", -1, calculate_order_total(100, 1, 0, 0, 1));
    failures += expect("zero quantity", -1, calculate_order_total(100, 0, 0, 0, 0));
    failures += expect("negative unit price", -1, calculate_order_total(-1, 5, 0, 0, 0));
    failures += expect("regular", 500, calculate_order_total(100, 5, 0, 0, 0));
    failures += expect("premium", 450, calculate_order_total(100, 5, 1, 0, 0));
    failures += expect("express", 520, calculate_order_total(100, 5, 0, 1, 0));
    failures += expect("combined", 1050, calculate_order_total(100, 12, 1, 1, 0));
    failures += expect("threshold exact", 1000, calculate_order_total(100, 10, 0, 0, 0));
    failures += expect("above threshold", 1050, calculate_order_total(100, 11, 0, 0, 0));
    return failures ? 1 : 0;
}
