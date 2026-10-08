#include "logic.h"
int calculate_order_total(int p, int q, int a, int b, int c)
{
    int x = 0;
    if (!c) {
        if (q > 0 && p >= 0) {
            x = p * q;
            if (a) x = x - x / 10;
            if (b) x = x + 20;
            if (x > 1000) x = x - 50;
        } else x = -1;
    } else x = -1;
    return x;
}
