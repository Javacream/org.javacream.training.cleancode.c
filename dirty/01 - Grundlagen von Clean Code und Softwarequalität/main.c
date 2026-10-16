#include <stdio.h>

int main(void)
{
    int p = 120;
    int q = 3;
    int r = p * q;
    if (r > 300) {
        r = r - 30;
    }
    printf("Total: %d\n", r);
    return 0;
}
