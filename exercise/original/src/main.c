#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id; int customer; int cents; int grams; int shipping; int status; } Order;
Order orders[100];
int n = 0;
char file_name[] = "orders.txt";

int calc(int c, int g, int s) {
    int x = 0;
    if (s == 1) { x = 500; if (c >= 10000) x = 0; }
    else { if (s == 2) x = 1200; else return -1; }
    if (g > 5000) x += 300;
    return x;
}
int load(void) {
    FILE *f; char line[256]; Order a;
    n = 0; f = fopen(file_name, "r");
    if (!f) return 0;
    while (fgets(line, sizeof line, f) && n < 100) {
        if (sscanf(line, "%d;%d;%d;%d;%d;%d", &a.id, &a.customer, &a.cents, &a.grams, &a.shipping, &a.status) == 6)
            orders[n++] = a;
    }
    fclose(f); return n;
}
int save(void) {
    FILE *f = fopen(file_name, "w"); int i;
    if (!f) return 0;
    for (i = 0; i < n; ++i)
        if (fprintf(f, "%d;%d;%d;%d;%d;%d\n", orders[i].id, orders[i].customer, orders[i].cents, orders[i].grams, orders[i].shipping, orders[i].status) < 0) { fclose(f); return 0; }
    if (fclose(f) != 0) return 0;
    return 1;
}
int add(int id, int customer, int cents, int grams, int shipping) {
    int i;
    if (id <= 0 || customer <= 0 || cents < 0 || grams < 0 || calc(cents, grams, shipping) < 0 || n >= 100) return 0;
    for (i = 0; i < n; ++i) if (orders[i].id == id) return 0;
    orders[n].id = id; orders[n].customer = customer; orders[n].cents = cents;
    orders[n].grams = grams; orders[n].shipping = shipping; orders[n].status = 1;
    ++n; return 1;
}
int cancel(int id) {
    int i;
    for (i = 0; i < n; ++i) if (orders[i].id == id && orders[i].status == 1) { orders[i].status = 0; return 1; }
    return 0;
}
int total(int id) {
    int i;
    for (i = 0; i < n; ++i) if (orders[i].id == id) return orders[i].cents + calc(orders[i].cents, orders[i].grams, orders[i].shipping);
    return -1;
}
int self_test(void) {
    char old[sizeof file_name]; int ok = 1;
    strcpy(old, file_name); strcpy(file_name, "test.txt");
    n = 0;
    ok = ok && calc(9999, 5000, 1) == 500;
    ok = ok && calc(10000, 5001, 1) == 300;
    ok = ok && calc(10000, 5001, 2) == 1500;
    ok = ok && add(1, 10, 10000, 5001, 1);
    ok = ok && !add(1, 10, 10000, 5001, 1);
    ok = ok && total(1) == 10300;
    ok = ok && save() && load() == 1 && total(1) == 10300;
    ok = ok && cancel(1) && save() && load() == 1 && orders[0].status == 0;
    remove(file_name); strcpy(file_name, old);
    puts(ok ? "PASS" : "FAIL"); return ok ? 0 : 1;
}
int main(int argc, char **argv) {
    int i;
    if (argc > 1 && strcmp(argv[1], "--self-test") == 0) return self_test();
    load();
    if (n == 0) {
        if (!add(1001, 4711, 9200, 2200, 1) || !add(1002, 4712, 15000, 6100, 2) || !save()) { fputs("Speichern fehlgeschlagen\n", stderr); return 1; }
    }
    for (i = 0; i < n; ++i)
        printf("Auftrag %d Kunde %d: %d Cent, Status %d\n", orders[i].id, orders[i].customer, total(orders[i].id), orders[i].status);
    return 0;
}
