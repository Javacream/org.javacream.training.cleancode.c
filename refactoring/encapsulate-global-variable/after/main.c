#include <stdio.h>
#include "account.h"
int main(void) { account_deposit(100.0); printf("%.2f\n", account_get_balance());  return 0; }
