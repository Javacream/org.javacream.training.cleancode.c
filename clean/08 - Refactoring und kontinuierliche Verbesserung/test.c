#include <stdio.h>

int calculate_order_total(int unit_price, int quantity, int premium, int express, int blocked);

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
    failures += expect("regular", 500, calculate_order_total(100, 5, 0, 0, 0));
    failures += expect("premium", 450, calculate_order_total(100, 5, 1, 0, 0));
    failures += expect("express", 520, calculate_order_total(100, 5, 0, 1, 0));
    failures += expect("combined", 1050, calculate_order_total(100, 12, 1, 1, 0));
    return failures;
}
