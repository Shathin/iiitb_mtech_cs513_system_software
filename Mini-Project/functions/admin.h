#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS

#include "./common.h"

// Function Prototypes =================================

bool admin_operation_handler(int connFD);
bool add_account(int connFD);
int add_customer(int connFD, bool isPrimary);
bool delete_account(int connFD);
bool modify_customer_info(int connFD);

// =====================================================

// Function Definition =================================

// =====================================================

bool admin_operation_handler(int connFD)
{

    if (login_handler(true, connFD))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client

        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, ADMIN_LOGIN_SUCCESS, strlen(ADMIN_LOGIN_SUCCESS));
        // TODO : Add error checking
    }
    else
    {
        // ADMIN LOGIN FAILED
        return false;
    }
}

bool add_account(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct Account newAccount, prevAccount;

    int accountFileDescriptor = open("../records/account.bank", O_RDONLY);
    if (errno == EACCES)
    {
        // Customer file was never created
        newAccount.accountNumber = 0;
    }
    else if (accountFileDescriptor == -1)
    {
        perror("Error while opening account file");
        return false;
    }
    else
    {
        int offset = lseek(accountFileDescriptor, -sizeof(struct Account), SEEK_END);
        // TODO : Add error checking
        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
        int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
        // TODO : Add error checking
        readBytes = read(accountFileDescriptor, &prevAccount, sizeof(struct Account));
        // TODO : Add error checking
        lock.l_type = F_UNLCK;
        fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
        // TODO : Add error checking
        close(accountFileDescriptor);

        newAccount.accountNumber = prevAccount.accountNumber + 1;
    }
    writeBytes = write(connFD, ADMIN_ADD_ACCOUNT_TYPE, strlen(ADMIN_ADD_ACCOUNT_TYPE));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, &readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    newAccount.isRegularAccount = atoi(readBuffer) == 1 ? true : false; // TODO : Add checking for erroneous input

    newAccount.owners[0] = add_customer(connFD, true);

    if (newAccount.isRegularAccount)
        newAccount.owners[1] = -1;
    else
        newAccount.owners[1] = add_customer(connFD, false);

    newAccount.active = true;
    newAccount.balance = 0;

    accountFileDescriptor = open("../records/account.bank", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    // TODO : Add error checking
    writeBytes = write(accountFileDescriptor, &newAccount, sizeof(struct Account));
    // TODO : Add error checking
    close(accountFileDescriptor);

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "%s%d", ADMIN_ADD_ACCOUNT_NUMBER, newAccount.accountNumber);
    strcpy(writeBuffer, "%");
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));

    return true;
}

int add_customer(int connFD, bool isPrimary)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct Customer newCustomer, previousCustomer;

    int customerFileDescriptor = open("../records/customer.bank", O_RDONLY);
    if (errno == EACCES)
    {
        // Customer file was never created
        newCustomer.id = 0;
    }
    else if (customerFileDescriptor == -1)
    {
        perror("Error while opening customer file");
        return -1;
    }
    else
    {
        int offset = lseek(customerFileDescriptor, -sizeof(struct Customer), SEEK_END);
        // TODO : Add error checking
        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
        int fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
        // TODO : Add error checking
        readBytes = read(customerFileDescriptor, &previousCustomer, sizeof(struct Customer));
        // TODO : Add error checking
        lock.l_type = F_UNLCK;
        fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
        // TODO : Add error checking
        close(customerFileDescriptor);

        newCustomer.id = previousCustomer.id + 1;
    }

    if (isPrimary)
        sprintf(writeBuffer, "%s%s", ADMIN_ADD_CUSTOMER_PRIMARY, ADMIN_ADD_CUSTOMER_NAME);
    else
        sprintf(writeBuffer, "%s%s", ADMIN_ADD_CUSTOMER_SECONDARY, ADMIN_ADD_CUSTOMER_NAME);

    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));
    // TODO : Add error checking

    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    strcpy(newCustomer.name, readBuffer);

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, ADMIN_ADD_CUSTOMER_GENDER);
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    newCustomer.gender = readBuffer[0]; // TODO : Add checking for errneous input

    bzero(writeBuffer, sizeof(writeBuffer));
    strcpy(writeBuffer, ADMIN_ADD_CUSTOMER_AGE);
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    newCustomer.age = atoi(readBuffer);

    customerFileDescriptor = open("../records/customer.bank", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    // TODO : Add error checking
    writeBytes = write(customerFileDescriptor, &newCustomer, sizeof(struct Customer));
    // TODO : Add error checking
    close(customerFileDescriptor);

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "%s%s-%d\n%s%s", ADMIN_ADD_CUSTOMER_AUTOGEN_LOGIN, newCustomer.name, newCustomer.id, ADMIN_ADD_CUSTOMER_AUTOGEN_PASSWORD, AUTOGEN_PASSWORD);
    strcpy(writeBuffer, "%");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO : Add error checking

    return newCustomer.id;
}

bool delete_account(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct Account account;

    writeBytes = write(connFD, ADMIN_DEL_ACCOUNT_NO, strlen(ADMIN_DEL_ACCOUNT_NO));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    int accountNumber = atoi(readBuffer); // TODO : Handle erroneous input

    int accountFileDescriptor = open("../records/account.bank", O_RDONLY);
    // TODO : Add error checking

    int offset = lseek(accountFileDescriptor, accountNumber * sizeof(struct Account), SEEK_SET);
    // TODO : Add error checking

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Account), getpid()};
    int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking
    readBytes = read(accountFileDescriptor, &account, sizeof(struct Account));
    //TODO : Add error checking
    lock.l_type = F_UNLCK;
    fcntlStatus = fcntl(accountFileDescriptor, F_SETLK, &lock);
    // TODO : Add error checking
    close(accountFileDescriptor);

    bzero(writeBuffer, sizeof(writeBuffer));
    if (account.balance == 0)
    {
        // No money, hence can close account
        account.active = false;
        accountFileDescriptor = open("../records/account.bank", O_WRONLY);
        // TODO : Add error checking

        offset = lseek(accountFileDescriptor, accountNumber * sizeof(struct Account), SEEK_SET);
        // TODO : Add error checking

        lock.l_type = F_WRLCK;
        lock.l_start = offset;

        int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
        // TODO : Add error checking
        writeBytes = write(accountFileDescriptor, &account, sizeof(struct Account));
        //TODO : Add error checking
        lock.l_type = F_UNLCK;
        fcntlStatus = fcntl(accountFileDescriptor, F_SETLK, &lock);
        // TODO : Add error checking

        strcpy(writeBuffer, ADMIN_DEL_ACCOUNT_SUCCESS);
    }
    else
        // Account has some money ask customer to withdraw it
        strcpy(writeBuffer, ADMIN_DEL_ACCOUNT_FAILURE);
    strcpy(writeBuffer, "%");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    return true;
}

bool modify_customer_info(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct Customer customer;

    int customerID;

    writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_ID, strlen(ADMIN_MOD_CUSTOMER_ID));
    // TODO : Add error checking
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    customerID = atoi(readBuffer);

    int customerFileDescriptor = open("../records/customer.bank", O_RDONLY);
    if (customerFileDescriptor == -1)
    {
        perror("Error while opening customer file");
        return false;
    }
    int offset = lseek(customerFileDescriptor, customerID * sizeof(struct Customer), SEEK_SET);
    // TODO : Add error checking
    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
    int fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking
    readBytes = read(customerFileDescriptor, &customer, sizeof(struct Customer));
    // TODO : Add error checking
    lock.l_type = F_UNLCK;
    fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking
    close(customerFileDescriptor);

    writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_MENU, strlen(ADMIN_MOD_CUSTOMER_MENU));
    // TODO : Add error checking
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    int choice = atoi(readBuffer); // TODO : Handle errneous input

    bzero(readBuffer, sizeof(readBuffer));
    switch (choice)
    {
    case 1:
        writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_NEW_NAME, strlen(ADMIN_MOD_CUSTOMER_NEW_NAME));
        // TODO : Add error checking
        readBytes = read(connFD, &readBuffer, sizeof(readBuffer));
        // TODO : Add error checking
        strcpy(customer.name, readBuffer);
        break;
    case 2:
        writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_NEW_AGE, strlen(ADMIN_MOD_CUSTOMER_NEW_AGE));
        // TODO : Add error checking
        readBytes = read(connFD, &readBuffer, sizeof(readBuffer));
        // TODO : Add error checking
        customer.age = atoi(readBuffer); // TODO : Handle erreneous input
        break;
    case 3:
        writeBytes = write(connFD, ADMIN_MOD_CUSTOMER_NEW_GENDER, strlen(ADMIN_MOD_CUSTOMER_NEW_GENDER));
        // TODO : Add error checking
        readBytes = read(connFD, &readBuffer, sizeof(readBuffer));
        // TODO : Add error checking
        customer.gender = readBuffer[0];
        break;
    default:
        return false;
    }

    customerFileDescriptor = open("../records/customer.bank", O_WRONLY);
    if (customerFileDescriptor == -1)
    {
        perror("Error while opening customer file");
        return false;
    }
    int offset = lseek(customerFileDescriptor, customerID * sizeof(struct Customer), SEEK_SET);
    // TODO : Add error checking
    struct flock lock = {F_WRLCK, SEEK_SET, offset, sizeof(struct Customer), getpid()};
    int fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking
    writeBytes = write(customerFileDescriptor, &customer, sizeof(struct Customer));
    // TODO : Add error checking
    lock.l_type = F_UNLCK;
    fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking
    close(customerFileDescriptor);

    return true;
}

#endif