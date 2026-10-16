#include <stdio.h>
#include <stdlib.h>
static int closes = 0;
static void *fail_alloc(size_t n) { (void)n; return NULL; }
static int tracked_close(FILE *f) { ++closes; return fclose(f); }
#define malloc fail_alloc
#define fclose tracked_close
#define main sample_main
#include "main.c"
#undef main
#undef fclose
#undef malloc
int main(void)
{
    if (write_value("cleanup-failure-test.txt", 42) != -1) return 1;
    if (closes != 1) return 1;
    remove("cleanup-failure-test.txt");
    puts("PASS: file closed on allocation failure");
    return 0;
}
