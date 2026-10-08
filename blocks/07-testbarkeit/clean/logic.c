#include "logic.h"
int calculate_gross_price(int net_cents, int tax_percent)
{
    return net_cents + net_cents * tax_percent / 100;
}
