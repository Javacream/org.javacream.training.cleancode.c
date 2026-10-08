#include <stdio.h>

int classify(int a, int b, int c)
{
    int score = 0;
    if (a > 0) {
        if (b > 0) {
            score++;
            if (c > 0) score++;
        } else if (c > 10) {
            score += 2;
        }
    } else if (b > 5 || c > 5) {
        score++;
    }
    return score;
}

int main(void)
{
    printf("%d\n", classify(1, 2, 3));
    return 0;
}
