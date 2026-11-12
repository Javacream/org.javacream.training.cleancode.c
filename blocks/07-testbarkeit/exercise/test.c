#include <stdio.h>
#include "rectangle.h"

static int assert_equal(const char *name, double expected, double actual)
{
    if (expected == actual) {
        printf("PASS %s\n", name);
        return 0;
    }
    fprintf(stderr, "FAIL %s: expected %.2f, got %.2f\n",
            name, expected, actual);
    return 1;
}

int main(void)
{
    int failures = 0;
    failures += assert_equal("area 5x37", 185.0, rectangle_area(5.0, 37.0));
    failures += assert_equal("perimeter 5x37", 84.0, rectangle_perimeter(5.0, 37.0));
    failures += assert_equal("area square", 16.0, rectangle_area(4.0, 4.0));
    failures += assert_equal("perimeter square", 16.0, rectangle_perimeter(4.0, 4.0));
    failures += assert_equal("area zero side", 0.0, rectangle_area(0.0, 37.0));
    failures += assert_equal("perimeter zero side", 74.0, rectangle_perimeter(0.0, 37.0));
    failures += assert_equal("area fractional", 3.75, rectangle_area(1.5, 2.5));
    failures += assert_equal("perimeter fractional", 8.0, rectangle_perimeter(1.5, 2.5));
    return failures ? 1 : 0;
}
