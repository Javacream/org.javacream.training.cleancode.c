#include <stdio.h>
static int incident_score(int age, int incidents, int overdue)
{
    int score = 0;
    if (age < 21) {
        score = 2;
        if (incidents > 0) score += 3 + (overdue ? 2 : 0);
        else if (overdue) score += 1;
    } else {
        score = incidents > 2 ? 3 : (incidents > 0 ? 1 : 0);
        if (overdue) score += 2;
    }
    return score;
}
int risk_score(int age, int incidents, int overdue, int verified)
{
    int score = incident_score(age, incidents, overdue);
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
