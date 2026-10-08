#include <stdio.h>

int calculate(int p, int q, int premium, int express, int blocked)
{
    int x = 0;
    if (!blocked) {
        x = p * q;
        if (premium) x = x - x / 10;
        if (express) x = x + 20;
        if (x > 1000) x = x - 50;
    } else {
        x = -1;
    }
    return x;
}

int main(void)
{
    printf("%d\n", calculate(100, 12, 1, 1, 0));
    return 0;
}
