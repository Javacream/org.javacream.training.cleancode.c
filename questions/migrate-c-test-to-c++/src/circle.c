#include "circle.h"
#include <float.h>

#define CIRCLE_PI 3.14159265358979323846

static int valid_radius(double radius)
{
    /* Die Vergleiche schliessen negative Werte, NaN und +/-Inf aus. */
    return radius >= 0.0 && radius <= DBL_MAX;
}

double area(double radius)
{
    if (!valid_radius(radius)) {
        return -1.0;
    }
    return CIRCLE_PI * radius * radius;
}

double perimeter(double radius)
{
    if (!valid_radius(radius)) {
        return -1.0;
    }
    return 2.0 * CIRCLE_PI * radius;
}
