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

#include "../record-struct/account.h"
#include "../record-struct/customer.h"
#include "./admin-credentials.h"
#include "../server-constants.h"

// Function Prototypes =================================

bool login_handler(bool isAdmin, int connFD);

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

        off_t offset = lseek(customerFileFD, SEEK_SET, ID * sizeof(struct Customer));
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

#endif