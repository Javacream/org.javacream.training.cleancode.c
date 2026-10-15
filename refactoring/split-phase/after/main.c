#include <stdio.h>
#include <stdlib.h>
static int parse_amount(const char *text, double *result) {
    char *end;
    double amount = strtod(text, &end);
    if (end == text || *end != '\0') return 0;
    *result = amount;
    return 1;
}
static double gross_price(double net) { return net * 1.19; }
double price(const char *text) {
    double amount;
    if (!parse_amount(text, &amount)) return -1;
    return gross_price(amount);
}
int main(void) { printf("%.2f\n", price("20"));  return 0; }
