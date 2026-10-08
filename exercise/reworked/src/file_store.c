#include <stdio.h>
#include <errno.h>
#include "file_store.h"

int file_load(const char *path, OrderList *list) {
    FILE *file;
    char line[256];
    Order item;
    if (!list || !path) return 0;
    list->count = 0;
    file = fopen(path, "r");
    if (!file) return errno == ENOENT;
    while (fgets(line, sizeof line, file)) {
        if (list->count >= MAX_ORDERS ||
            sscanf(line, "%d;%d;%d;%d;%d;%d", &item.id, &item.customer,
                   &item.subtotal_cents, &item.weight_grams, &item.shipping, &item.status) != 6) {
            fclose(file);
            return 0;
        }
        list->items[list->count++] = item;
    }
    if (ferror(file)) { fclose(file); return 0; }
    return fclose(file) == 0;
}
int file_save(const char *path, const OrderList *list) {
    FILE *file;
    int i;
    if (!path || !list) return 0;
    file = fopen(path, "w");
    if (!file) return 0;
    for (i = 0; i < list->count; ++i) {
        const Order *o = &list->items[i];
        if (fprintf(file, "%d;%d;%d;%d;%d;%d\n", o->id, o->customer, o->subtotal_cents,
                    o->weight_grams, o->shipping, o->status) < 0) {
            fclose(file);
            return 0;
        }
    }
    return fclose(file) == 0;
}
