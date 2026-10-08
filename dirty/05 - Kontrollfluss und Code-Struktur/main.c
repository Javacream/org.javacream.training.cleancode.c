#include <stdio.h>
/* -1 = ungültig; Abholung 0, Standard 1, Express 2 */
int shipping_cost(int weight, int mode, int international, int blocked)
{
    int cost = 0;
    if (!blocked) {
        if (weight > 0) {
            if (mode == 0) cost = 0;
            else if (mode == 1) {
                if (international) cost = 20; else cost = 5;
            } else if (mode == 2) {
                if (international) cost = 35; else cost = 15;
            } else cost = -1;
        } else cost = -1;
    } else cost = -1;
    return cost;
}
int main(void)
{
    printf("%d\n", shipping_cost(10, 2, 0, 0));
    return 0;
}
