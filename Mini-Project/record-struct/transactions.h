#ifndef TRANSACTIONS
#define TRANSACTIONS

struct Transaction
{
    int transactionID; // 0, 1, 2, 3 ...
    int accountNumber;
    short int operation; // 0 -> Withdraw, 1 -> Deposit
    long int oldBalance;
    long int newBalance;
    // Date
};

#endif