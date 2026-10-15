#include <stdio.h>
#include <stdlib.h>
int write_value(const char *path, int value) {
    FILE *f;
    char *buffer;
    f = fopen(path, "w");
    if (!f) return -1;
    buffer = malloc(64);
    if (!buffer) { fclose(f); return -1; }
    if (sprintf(buffer, "%d\n", value) < 0) { free(buffer); fclose(f); return -1; }
    if (fputs(buffer, f) == EOF) { free(buffer); fclose(f); return -1; }
    free(buffer);
    return fclose(f) == 0 ? 0 : -1;
}
int main(void) { return write_value("result.txt", 42) != 0;  return 0; }
