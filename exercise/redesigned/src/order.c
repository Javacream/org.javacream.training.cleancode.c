#include "order.h"
int shipping_cost(int cents, int grams, int shipping, int *result) {
    int fee;
    if (!result || cents < 0 || grams < 0) return 0;
    if (shipping == SHIPPING_STANDARD) fee = cents >= 10000 ? 0 : 500;
    else if (shipping == SHIPPING_EXPRESS) fee = 1200;
    else return 0;
    if (grams > 5000) fee += 300;
    *result = fee; return 1;
}
