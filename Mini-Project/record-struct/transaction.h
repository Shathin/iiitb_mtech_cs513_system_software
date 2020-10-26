#ifndef TRANSACTIONS
#define TRANSACTIONS

#include <time.h>

struct Transaction
{
    int transactionID; // 0, 1, 2, 3 ...
    int accountNumber;
    bool operation; // 0 -> Withdraw, 1 -> Deposit
    long int oldBalance;
    long int newBalance;
    time_t transactionTime;
};

#endif