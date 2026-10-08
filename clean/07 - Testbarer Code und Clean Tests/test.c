#include <stdio.h>

int calculate_gross_price(int net, int tax_rate);

static int check_equal(const char *name, int expected, int actual)
{
    if (expected != actual) {
        printf("FAIL %s: expected %d, got %d\n", name, expected, actual);
        return 1;
    }
    printf("PASS %s\n", name);
    return 0;
}

int main(void)
{
    int failures = 0;
    failures += check_equal("standard tax", 119, calculate_gross_price(100, 19));
    failures += check_equal("zero tax", 100, calculate_gross_price(100, 0));
    failures += check_equal("zero net", 0, calculate_gross_price(0, 19));
    return failures;
}
