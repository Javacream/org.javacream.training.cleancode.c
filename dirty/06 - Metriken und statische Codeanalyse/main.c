#include <stdio.h>
int risk_score(int age, int incidents, int overdue, int verified)
{
    int score = 0;
    if (age < 21) {
        score += 2;
        if (incidents > 0) {
            score += 3;
            if (overdue) score += 2;
        } else if (overdue) score += 1;
    } else {
        if (incidents > 2) score += 3;
        else if (incidents > 0) score += 1;
        if (overdue) score += 2;
    }
    if (!verified && (score > 2 || incidents > 1)) score += 2;
    return score;
}
int category(int score)
{
    if (score >= 7) return 3;
    if (score >= 4) return 2;
    if (score > 0) return 1;
    return 0;
}
int main(void)
{
    printf("%d\n", category(risk_score(20, 2, 1, 0)));
    return 0;
}
