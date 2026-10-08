#include <stdio.h>
#include <stdlib.h>
int parse_temperature(const char *text, double *out) {
    char *end;
    double value;
    if (out == NULL || text == NULL) return 0;
    value = strtod(text, &end);
    if (end == text || *end != '\0') return 0;
    *out = value;
    return 1;
}
int main(void) { double value; if (parse_temperature("-5", &value)) printf("%.1f\n", value);  return 0; }
