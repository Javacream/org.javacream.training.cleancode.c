#include <stdio.h>
#include <stdlib.h>
/* Returns owned memory. Caller must call buffer_destroy(). */
char *buffer_create(void) { return malloc(32); }
void buffer_destroy(char *buffer) { free(buffer); }
int main(void) { char *buffer = buffer_create(); if (!buffer) return 1; puts("allocated"); buffer_destroy(buffer);  return 0; }
