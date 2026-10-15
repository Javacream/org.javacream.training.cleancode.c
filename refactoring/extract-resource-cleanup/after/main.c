#include <stdio.h>
#include <stdlib.h>
int write_value(const char *path, int value) {
    int status = -1;
    FILE *f;
    char *buffer;
    f = fopen(path, "w");
    if (!f) return -1;
    buffer = malloc(64);
    if (!buffer) goto cleanup;
    if (sprintf(buffer, "%d\n", value) < 0) goto cleanup;
    if (fputs(buffer, f) == EOF) goto cleanup;
    status = 0;
cleanup:
    free(buffer);
    if (fclose(f) != 0) status = -1;
    return status;
}
int main(void) { return write_value("result.txt", 42) != 0;  return 0; }
