#include <stdio.h>
#include "logic.h"
static int assert_equal(const char *test_name, int expected, int actual)
{
    if (expected == actual) { printf("PASS %s\n", test_name); return 0; }
    printf("FAIL %s: expected %d, got %d\n", test_name, expected, actual);
    return 1;
}
int main(void)
{
    int failures = 0;
    /* Arrange: konkrete Eingabewerte; Act: Funktionsaufruf; Assert: Erwartung */
    failures += assert_equal("standard tax", 119, calculate_gross_price(100, 19));
    failures += assert_equal("zero tax", 100, calculate_gross_price(100, 0));
    failures += assert_equal("zero net", 0, calculate_gross_price(0, 19));
    failures += assert_equal("maximum tax", 200, calculate_gross_price(100, 100));
    failures += assert_equal("rounding down", 102, calculate_gross_price(101, 1));
    failures += assert_equal("negative net", -1, calculate_gross_price(-1, 19));
    failures += assert_equal("negative tax", -1, calculate_gross_price(100, -1));
    failures += assert_equal("tax above 100", -1, calculate_gross_price(100, 101));
    return failures ? 1 : 0;
}
