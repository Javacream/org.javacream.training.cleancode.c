#include <stdio.h>
#include <stdlib.h>
double price(const char *text) {
    char *end;
    double amount = strtod(text, &end);
    if (end == text || *end != '\0') return -1;
    return amount * 1.19;
}
int main(void) { printf("%.2f\n", price("20"));  return 0; }
