#include <stdio.h>
#include "application.h"

int console_save(void *user_data, int order_id, int amount);

int main(void)
{
    ApplicationContext app;
    StorageDependency storage;
    storage.save = console_save;
    storage.user_data = 0;

    if (!application_init(&app, storage)) {
        return 1;
    }
    if (!process_order(&app, 42, 120)) {
        return 1;
    }
    printf("requests=%u\n", app.requests);
    return 0;
}
