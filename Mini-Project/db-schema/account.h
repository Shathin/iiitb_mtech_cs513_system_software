#ifndef ACCOUNT
#define ACCOUNT 

struct account
{
    int accountNumber;
    bool isAccountRegular; // 1 -> regular, 0 -> joint
    bool accountStatus;    // 0 -> inactive, 1 -> active
    int owners[4];         // list of customer IDs.
    int balance;           // amount of money
};

#endif