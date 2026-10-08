#include <stdio.h>

int shipping_cost(int weight, int express, int international, int blocked)
{
    int cost;
    if (blocked) return -1;
    if (weight <= 0) return -1;

    cost = international ? 20 : 5;
    if (express) cost += international ? 15 : 10;
    return cost;
}

int main(void)
{
    printf("%d\n", shipping_cost(10, 1, 0, 0));
    return 0;
}
