#include <stdio.h>

static int positive_case(int b, int c)
{
    if (b <= 0) return c > 10 ? 2 : 0;
    return c > 0 ? 2 : 1;
}

int classify(int a, int b, int c)
{
    if (a > 0) return positive_case(b, c);
    return (b > 5 || c > 5) ? 1 : 0;
}

int main(void)
{
    printf("%d\n", classify(1, 2, 3));
    return 0;
}
