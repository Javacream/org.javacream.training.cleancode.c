#include <stdio.h>
#include <stdlib.h>
char *create_buffer(void) { return malloc(32); }
int main(void) { char *buffer = create_buffer(); if (!buffer) return 1; puts("allocated"); free(buffer);  return 0; }
