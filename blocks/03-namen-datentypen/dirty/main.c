#include <stdio.h>
int main(int argc, char *argv[])
{
    int s, x, y, z;
    if (argc != 5 || sscanf(argv[1], "%d", &s) != 1 ||
        sscanf(argv[2], "%d", &x) != 1 ||
        sscanf(argv[3], "%d", &y) != 1 ||
        sscanf(argv[4], "%d", &z) != 1 ||
        s < 0 || s > 2 || (x != 0 && x != 1) ||
        (y != 0 && y != 1) || z < 0) {
        fprintf(stderr, "Usage: %s STATUS(0-2) PAID(0/1) INVALID_ADDRESS(0/1) ID(>=0)\n", argv[0]);
        return 1;
    }
    if (s == 2 && x == 1 && y == 0) printf("Shipment %d: ready\n", z);
    else printf("Shipment %d: not ready\n", z);
    return 0;
}
