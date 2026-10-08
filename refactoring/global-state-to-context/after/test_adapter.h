/* Variantenadapter: der Test ../test.c bleibt unveraendert. */
#define main refactoring_example_main
#include "main.c"
#undef main
static MetricsContext test_ctx={0}; static int count_after(int n){int i;for(i=0;i<n;i++)record_request(&test_ctx);return (int)request_count(&test_ctx);}
