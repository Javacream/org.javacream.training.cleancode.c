/* Zusaetzliche Tests nur fuer die extrahierte static-Funktion (C90). */
#include <stdio.h>
#include <math.h>

/* Gleiche Uebersetzungseinheit: subtotal() bleibt static und testbar. */
#define main refactoring_example_main
#include "../main.c"
#undef main

static int failures = 0;

static void check_near(const char *name, double actual, double expected)
{
    if (fabs(actual - expected) > 0.000001) {
        fprintf(stderr, "FAIL %s: %.9g != %.9g\n", name, actual, expected);
        ++failures;
    } else {
        printf("PASS %s\n", name);
    }
}

int main(void)
{
    const double prices[] = {10.0, 20.0, 7.5};

    /* 1. Die Extraktion macht die Summierung isoliert pruefbar. */
    check_near("subtotal of three prices", subtotal(prices, 3U), 37.5);

    /* 2. Die leere Liste ist unabhaengig von der Steuerlogik testbar. */
    check_near("subtotal of empty list", subtotal(prices, 0U), 0.0);

    if (failures != 0) {
        fprintf(stderr, "%d additional test(s) failed\n", failures);
        return 1;
    }
    puts("PASS: additional extract-function tests");
    return 0;
}
