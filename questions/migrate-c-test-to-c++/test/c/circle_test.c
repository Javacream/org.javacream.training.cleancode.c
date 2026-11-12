#include "circle.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define EPSILON 1e-10

static int failures = 0;

static void expect_near(const char *name, double actual, double expected)
{
    double delta = fabs(actual - expected);
    if (!(delta <= EPSILON)) {
        fprintf(stderr, "FAIL %s: expected %.12f, actual %.12f\n", name, expected, actual);
        failures++;
    }
}

static void expect_invalid(const char *name, double actual)
{
    expect_near(name, actual, -1.0);
}

int main(void)
{
    expect_near("area zero", area(0.0), 0.0);
    expect_near("perimeter zero", perimeter(0.0), 0.0);
    expect_near("area radius 1", area(1.0), PI);
    expect_near("perimeter radius 1", perimeter(1.0), 2.0 * PI);
    expect_near("area radius 2", area(2.0), 4.0 * PI);
    expect_near("perimeter radius 2", perimeter(2.0), 4.0 * PI);
    expect_near("area fractional", area(0.5), 0.25 * PI);
    expect_near("perimeter fractional", perimeter(0.5), PI);
    expect_invalid("area negative", area(-1.0));
    expect_invalid("perimeter negative", perimeter(-1.0));
    expect_invalid("area NaN", area(0.0 / HUGE_VAL));
    expect_invalid("perimeter NaN", perimeter(0.0 / HUGE_VAL));
    expect_invalid("area infinity", area(HUGE_VAL));
    expect_invalid("perimeter infinity", perimeter(HUGE_VAL));

    if (failures != 0) {
        fprintf(stderr, "%d test(s) failed\n", failures);
        return 1;
    }
    puts("All 14 C assertions passed");
    return 0;
}
