#include "rectangle.h"

/* Reine Berechnungsfunktionen ohne Ein-/Ausgabe oder globalen Zustand. */
double rectangle_area(double a, double b)
{
    return a * b;
}

double rectangle_perimeter(double a, double b)
{
    return 2.0 * (a + b);
}
