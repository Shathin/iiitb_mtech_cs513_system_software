#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS

#include <stdio.h>     // Import for `printf` & `perror`
#include <unistd.h>    // Import for `read`, `write & `lseek`
#include <string.h>    // Import for string functions
#include <stdbool.h>   // Import for `bool` data type
#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <stdlib.h>    // Import for `atoi`
#include <errno.h>     // Import for `errno`

#include "../record-struct/account.h"
#include "../record-struct/customer.h"
#include "./admin-credentials.h"
#include "../server-constants.h"

// Function Prototypes =================================

bool login_handler(bool isAdmin, int connFD);
bool get_account_details(int connFD);
bool get_customer_details(int connFD, int customerID);

// =====================================================

// Function Definition =================================

// =====================================================

bool login_handler(bool isAdmin, int connFD)
{
    ssize_t readBytes, writeBytes;            // Number of bytes written to / read from the socket
    char readBuffer[1000], writeBuffer[1000]; // Buffer for reading from / writing to the client

    struct Customer customer;

    bzero(readBuffer, sizeof(readBuffer));
    bzero(writeBuffer, sizeof(writeBuffer));

    // Get login message for respective user type
    if (isAdmin)
        strcpy(writeBuffer, ADMIN_LOGIN_WELCOME);
    else
        strcpy(writeBuffer, CUSTOMER_LOGIN_WELCOME);

    // Append the request for LOGIN ID message
    strcat(writeBuffer, "\n");
    strcat(writeBuffer, LOGIN_ID);

    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO: Add error checking

    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO: Add error checking

    bool userFound = false;

    if (isAdmin)
    {
        if (strcmp(readBuffer, ADMIN_LOGIN_ID) == 0)
            userFound = true;
    }
    else
    {
        int ID = atoi(strtok(readBuffer, "-"));

        int customerFileFD = open("../records/customer.bank", O_RDONLY);
        // TODO : Add error checking

        off_t offset = lseek(customerFileFD, ID * sizeof(struct Customer), SEEK_SET);
        if (offset >= 0)
        {

            struct flock lock = {F_RDLCK, SEEK_SET, ID * sizeof(struct Customer), sizeof(struct Customer), getpid()};

            int lockingStatus = fcntl(customerFileFD, F_SETLKW, &lock);
            // TODO : Add error checking

            readBytes = read(customerFileFD, &customer, sizeof(struct Customer));
            // TODO : Add error checking

            lock.l_type = F_UNLCK;
            lockingStatus = fcntl(customerFileFD, F_SETLK, &lock);

            if (strcmp(customer.password, readBuffer) == 0)
                userFound == true;

            close(customerFileFD);
        }
    }

    if (userFound)
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, PASSWORD, strlen(PASSWORD));
        // TODO : Add error checking

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        // TODO : Add error checking

        if (isAdmin)
        {
            if (strcmp(readBuffer, ADMIN_PASSWORD) == 0)
                return true;
        }
        else
        {
            if (strcmp(readBuffer, customer.password) == 0)
                return true;
        }

        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, INVALID_PASSWORD, strlen(INVALID_PASSWORD));
        // TODO : Add error checking
    }
    else
    {
        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connFD, INVALID_LOGIN, strlen(INVALID_LOGIN));
        // TODO : Add error checking
        return false;
    }

    return false;
}

bool get_account_details(int connFD)
{
    ssize_t readBytes, writeBytes;            // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[1000]; // A buffer for reading from / writing to the socket

    int accountNumber;
    struct Account account;
    int accountFileDescriptor;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Account), getpid()};

    writeBytes = write(connFD, GET_ACCOUNT_NUMBER, strlen(GET_ACCOUNT_NUMBER));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking

    accountNumber = atoi(readBuffer);
    // TODO : Add error checking

    accountFileDescriptor = open("../records/account.bank", O_RDONLY);
    // TODO : Add error checking
    int offset = lseek(accountFileDescriptor, accountNumber * sizeof(struct Account), SEEK_SET);
    // TODO : Add error checking
    lock.l_start = offset;

    // TODO : Check for any existing locks
    int fcntlStatus = fcntl(accountFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking

    readBytes = read(accountFileDescriptor, &account, sizeof(struct Account));
    // TODO : Add error checking

    lock.l_type = F_UNLCK;
    fcntlStatus = fcntl(accountFileDescriptor, F_SETLK, &lock);
    // TODO : Add error checking

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Account Details - \n\tAccount Number : %d\n\tAccount Type : %s\n\tAccount Status : %s", account.accountNumber, (account.isRegularAccount ? "Regular" : "Joint"), (account.active) ? "Active" : "Deactived");
    if (account.active)
        sprintf(writeBuffer, "\n\tAccount Balance:₹ %ld", account.balance);

    // TODO : Print customer names instead (requires seeking to the customer record and getting the data)
    sprintf(writeBuffer, "\n\tPrimary Owner ID: %d", account.owners[0]);
    if (account.owners[1] != -1)
        sprintf(writeBuffer, "\n\tSecondary Owner ID: %d", account.owners[1]);

    strcat(writeBuffer, "\n%");

    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking
    return true;
}

bool get_customer_details(int connFD, int customerID)
{
    ssize_t readBytes, writeBytes;            // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[1000]; // A buffer for reading from / writing to the socket

    struct Customer customer;
    int customerFileDescriptor;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Account), getpid()};

    if (customerID == -1)
    {
        writeBytes = write(connFD, GET_ACCOUNT_NUMBER, strlen(GET_ACCOUNT_NUMBER));
        // TODO : Add error checking

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
        // TODO : Add error checking

        customerID = atoi(readBuffer);
        // TODO : Add error checking
    }

    customerFileDescriptor = open("../records/customer.bank", O_RDONLY);
    // TODO : Add error checking
    int offset = lseek(customerFileDescriptor, customerID * sizeof(struct Customer), SEEK_SET);
    // TODO : Add error checking
    lock.l_start = offset;

    // TODO : Check for any existing locks
    int fcntlStatus = fcntl(customerFileDescriptor, F_SETLKW, &lock);
    // TODO : Add error checking

    readBytes = read(customerFileDescriptor, &customer, sizeof(struct Account));
    // TODO : Add error checking

    lock.l_type = F_UNLCK;
    fcntlStatus = fcntl(customerFileDescriptor, F_SETLK, &lock);
    // TODO : Add error checking

    bzero(writeBuffer, sizeof(writeBuffer));
    sprintf(writeBuffer, "Customer Details - \n\tID : %d\n\tName : %s\n\tGender : %c\n\tAge: %d\n\tAccount Number : %d", customer.id, customer.name, customer.gender, customer.age, customer.account);

    strcat(writeBuffer, "\n%");

    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
    // TODO : Add error checking

    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    // TODO : Add error checking
    return true;
}

#endif