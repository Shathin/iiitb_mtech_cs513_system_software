#ifndef ACCOUNT_RECORD
#define ACCOUNT_RECORD

#include "./transactions.h"

struct Account
{
    int accountNumber;     // 0, 1, 2, ....
    int owners[2];         // Customer IDs
    bool isRegularAccount; // 1 -> Regular account, 0 -> Joint account
    bool active;           // 1 -> Active, 0 -> Deactivated (Deleted)
    long int balance;      // Amount of money in the account
    int transactions[10];  // A list of transaction IDs. Used to look up the transactions
};

#endif