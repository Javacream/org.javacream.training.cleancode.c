#include <stdio.h>

int f(int x, int y)
{
    int z = x * y;
    if (z > 1000) z = z - 50;
    return z;
}

int main(void)
{
    int a = 25;
    int b = 50;
    printf("%d\n", f(a, b));
    return 0;
}
