#include <stdio.h>

int g = 0;

int calc(int a, int b, int c, int d, int e)
{
    int x = a * b;
    if (c == 1) x = x - x / 10;
    if (d > 100) x = x + 15;
    if (e == 7) x = x + 5;
    g = x;
    return x;
}

int main(void)
{
    int result = calc(50, 4, 1, 120, 7);
    printf("%d %d\n", result, g);
    return 0;
}
