#include <stdio.h>
#include <stdlib.h>
double parse_temperature(const char *text) {
    char *end;
    double value = strtod(text, &end);
    if (end == text || *end != '\0') return -9999.0;
    return value;
}
int main(void) { printf("%.1f\n", parse_temperature("-5"));  return 0; }
