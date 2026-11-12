#include <stdio.h>
#include "application.h"

/* Produktiver Adapter: in diesem Demo schreibt er auf stdout. */
int console_save(void *user_data, int order_id, int amount)
{
    (void)user_data;
    return printf("order=%d amount=%d\n", order_id, amount) >= 0;
}
