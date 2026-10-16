#include <stdio.h>
#define main sample_main
#include "main.c"
#undef main
#define incident_score alternative_incident_score
#define risk_score baseline_risk_score
#define category baseline_category
#define main alternative_main
#include "alternative.c"
#undef main
#undef category
#undef risk_score
#undef incident_score
/* The preprocessor names above isolate the functions from the two variants. */
int main(void)
{
    int age, incidents, overdue, verified;
    for (age = 18; age <= 25; ++age)
        for (incidents = 0; incidents <= 5; ++incidents)
            for (overdue = 0; overdue <= 1; ++overdue)
                for (verified = 0; verified <= 1; ++verified)
                    if (risk_score(age, incidents, overdue, verified) !=
                        baseline_risk_score(age, incidents, overdue, verified)) {
                        fputs("Different result\n", stderr);
                        return 1;
                    }
    puts("PASS: both implementations agree");
    return 0;
}
