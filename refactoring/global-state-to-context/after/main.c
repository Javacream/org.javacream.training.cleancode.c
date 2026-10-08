#include <stdio.h>
typedef struct { unsigned requests; } MetricsContext;
void record_request(MetricsContext *ctx) { ++ctx->requests; }
unsigned request_count(const MetricsContext *ctx) { return ctx->requests; }
int main(void) { MetricsContext ctx = {0}; record_request(&ctx); record_request(&ctx); printf("%u\n", request_count(&ctx));  return 0; }
