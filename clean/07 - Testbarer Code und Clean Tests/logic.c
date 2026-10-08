#include "logic.h"
int calculate_gross_price(int net_cents, int tax_percent)
{
    if (net_cents < 0 || tax_percent < 0 || tax_percent > 100) return -1;
    return net_cents + net_cents * tax_percent / 100;
}
