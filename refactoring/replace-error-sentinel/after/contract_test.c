#include <stdio.h>
#define main sample_main
#include "main.c"
#undef main
int main(void)
{
    double value = 0.0;
    if (!parse_temperature("-9999", &value) || value != -9999.0) return 1;
    if (parse_temperature("invalid", &value)) return 1;
    if (parse_temperature((const char *)0, &value)) return 1;
    if (parse_temperature("12", (double *)0)) return 1;
    puts("PASS: status distinguishes sentinel collision");
    return 0;
}
