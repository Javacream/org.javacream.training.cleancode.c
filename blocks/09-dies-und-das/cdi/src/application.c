#include "application.h"

int application_init(ApplicationContext *ctx, StorageDependency storage)
{
    if (ctx == 0 || storage.save == 0) {
        return 0;
    }
    ctx->requests = 0U;
    ctx->storage = storage;
    return 1;
}

int process_order(ApplicationContext *ctx, int order_id, int amount)
{
    if (ctx == 0 || ctx->storage.save == 0 || order_id <= 0 || amount < 0) {
        return 0;
    }
    ++ctx->requests;
    return ctx->storage.save(ctx->storage.user_data, order_id, amount) != 0;
}
