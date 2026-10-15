#include "account.h"
static double balance = 0.0;
double account_get_balance(void) { return balance; }
void account_deposit(double amount) { balance += amount; }
