#include <stdio.h>
#include "rectangle.h"

int main(void)
{
    const double a = 5.0;
    const double b = 37.0;

    printf("Rechteck: a=%.2f, b=%.2f\n", a, b);
    printf("Flaeche: %.2f\n", rectangle_area(a, b));
    printf("Umfang: %.2f\n", rectangle_perimeter(a, b));
    return 0;
}
