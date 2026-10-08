#ifndef FILE_STORE_H
#define FILE_STORE_H
#include "order.h"
int file_load(const char *path, OrderList *list);
int file_save(const char *path, const OrderList *list);
#endif
