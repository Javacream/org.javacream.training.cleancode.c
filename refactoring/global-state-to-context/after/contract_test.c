#include <stdio.h>
#define main sample_main
#include "main.c"
#undef main
int main(void)
{
    MetricsContext first = {0}, second = {0};
    record_request(&first); record_request(&first); record_request(&second);
    if (request_count(&first) != 2 || request_count(&second) != 1) return 1;
    record_request(&second);
    if (request_count(&first) != 2 || request_count(&second) != 2) return 1;
    puts("PASS: independent contexts");
    return 0;
}
