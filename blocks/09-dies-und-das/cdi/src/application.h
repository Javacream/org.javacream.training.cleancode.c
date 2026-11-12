#ifndef APPLICATION_H
#define APPLICATION_H

/* C90: technische Abhaengigkeit als Funktion und benutzerdefinierter Kontext. */
typedef int (*SaveFunction)(void *user_data, int order_id, int amount);

typedef struct {
    SaveFunction save;
    void *user_data;
} StorageDependency;

typedef struct {
    unsigned requests;
    StorageDependency storage;
} ApplicationContext;

/* 1 = erfolgreich, 0 = ungueltige Abhaengigkeit oder Argumente. */
int application_init(ApplicationContext *ctx, StorageDependency storage);

/* 1 = gespeichert, 0 = Speicherfehler/ungueltige Argumente.
   requests zaehlt gueltige Speicher-Versuche, auch bei Fehlern. */
int process_order(ApplicationContext *ctx, int order_id, int amount);

#endif
