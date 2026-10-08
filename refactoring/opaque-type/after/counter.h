#ifndef COUNTER_H
#define COUNTER_H
typedef struct Counter Counter;
Counter *counter_create(void);
void counter_increment(Counter *counter);
int counter_value(const Counter *counter);
void counter_destroy(Counter *counter);
#endif
