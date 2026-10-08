#include <stdio.h>
int main(void)
{
    int s = 2;
    int x = 1;
    int y = 0;
    int z = 3;
    if (s == 2 && x == 1 && y == 0) printf("Shipment %d: ready\n", z);
    else printf("Shipment %d: not ready\n", z);
    return 0;
}
