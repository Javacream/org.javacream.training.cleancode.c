#include <stdio.h>
static unsigned requests = 0;
void record_request(void) { ++requests; }
unsigned request_count(void) { return requests; }
int main(void) { record_request(); record_request(); printf("%u\n", request_count());  return 0; }
