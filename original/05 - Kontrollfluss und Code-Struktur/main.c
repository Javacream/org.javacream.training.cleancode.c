#include <stdio.h>

int shipping_cost(int weight, int express, int international, int blocked)
{
    int cost = 0;
    if (!blocked) {
        if (weight > 0) {
            if (international) {
                cost = 20;
                if (express) cost += 15;
            } else {
                cost = 5;
                if (express) cost += 10;
            }
        } else {
            cost = -1;
        }
    } else {
        cost = -1;
    }
    return cost;
}

int main(void)
{
    printf("%d\n", shipping_cost(10, 1, 0, 0));
    return 0;
}
