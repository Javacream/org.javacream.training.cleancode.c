#include <stdio.h>
enum { PICKUP = 0, STANDARD = 1, EXPRESS = 2 };
int shipping_cost(int weight, int mode, int international, int blocked)
{
    if (blocked || weight <= 0) return -1;
    switch (mode) {
        case PICKUP: return 0;
        case STANDARD: return international ? 20 : 5;
        case EXPRESS: return international ? 35 : 15;
        default: return -1;
    }
}
int main(void)
{
    printf("%d\n", shipping_cost(10, EXPRESS, 0, 0));
    return 0;
}
