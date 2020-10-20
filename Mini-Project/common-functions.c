#include <stdio.h>     // Import for `printf` & `perror`
#include <unistd.h>    // Import for `read`, `write & `lseek`
#include <string.h>    // Import for string functions
#include <stdbool.h>   // Import for `bool` data type
#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`

#include "./db-schema/customer.h"
#include "./db-schema/admin.h"
#include "./db-schema/account.h"
#include "./server-literals.c"

// Function prototype ================================
bool login_handler(bool isAdmin, int connectionFileDescriptor);

// ADMIN - CUSTOMER COMMON OPERATIONS
char *get_customer_info_by_id(int customerID);
char *get_account_info(int accountNumber);

// ====================================================

// Function definition ================================

bool login_handler(bool isAdmin, int connectionFileDescriptor)
{
    ssize_t readBytes, writeBytes;
    char loginIDBuffer[50], passwordBuffer[100];
    bool isLoginSuccessful = false;
    struct admin admin;
    struct customer customer;
    int ID;
    int fileDescriptor; // Holds the file descriptor to the admin or the customer file

    if (isAdmin)
    {
        writeBytes = write(connectionFileDescriptor, alpWelcome, strlen(alpWelcome));
        if (writeBytes <= 0)
        {
            perror("Error while sending admin welcome prompt!");
            return isLoginSuccessful;
        }
    }
    else
    {
        writeBytes = write(connectionFileDescriptor, clpWelcome, strlen(clpWelcome));
        if (writeBytes <= 0)
        {
            perror("Error while sending customer welcome prompt!");
            return isLoginSuccessful;
        }
    }

    writeBytes = write(connectionFileDescriptor, lpLogin, strlen(lpLogin));
    if (writeBytes <= 0)
    {
        perror("Error while sending loginID prompt!");
        return isLoginSuccessful;
    }

    readBytes = read(connectionFileDescriptor, loginIDBuffer, sizeof(loginIDBuffer));
    if (readBytes <= 0)
    {
        perror("Error while receiving loginID!");
        return isLoginSuccessful;
    }

    // Get the admin / customer ID
    ID = atoi(strtok(loginIDBuffer, "-"));

    // TODO : Search for admin / customer & get their data (structure)
    if (isAdmin)
    {
        // TODO : Seek to ID'th admin record and get the record
        fileDescriptor = open("./db/admin", O_RDONLY);
        lseek(fileDescriptor, SEEK_SET, (int) (ID*sizeof(admin)));
        readBytes = read(fileDescriptor, &admin, sizeof(admin));
        if(readBytes == -1) {
            perror("Error while reading from admin file");
            return isLoginSuccessful;
        } else if(readBytes == 0) {
            write(connectionFileDescriptor, lpFailedCredentials, strlen(lpFailedCredentials));
            return isLoginSuccessful;
        }
    }
    else
    {
        // TODO : Seek to ID'th customer record and get the record
        fileDescriptor = open("./db/customer", O_RDONLY);
        lseek(fileDescriptor, SEEK_SET, (int) (ID*sizeof(admin)));
        readBytes = read(fileDescriptor, &customer, sizeof(customer));
        if(readBytes == -1) {
            perror("Error while reading from customer file");
            return isLoginSuccessful;
        } else if(readBytes == 0) {
            write(connectionFileDescriptor, lpFailedCredentials, strlen(lpFailedCredentials));
            return isLoginSuccessful;
        }
    }

    writeBytes = write(connectionFileDescriptor, lpPassword, strlen(lpPassword));
    if (writeBytes <= 0)
    {
        perror("Error while write password prompt!");
        return isLoginSuccessful;
    }

    readBytes = read(connectionFileDescriptor, passwordBuffer, sizeof(passwordBuffer));
    if (readBytes <= 0)
    {
        perror("Error while receiving password!");
        return isLoginSuccessful;
    }

    if (isAdmin && !strcmp(passwordBuffer, admin.password))
    {
        isLoginSuccessful = true;

        writeBytes = write(connectionFileDescriptor, strcat(alpSuccessful, admin.adminName), strlen(alpSuccessful));
        if (writeBytes <= 0)
        {
            perror("Error while writing auth success prompt!");
            return isLoginSuccessful;
        }
    }
    else if (!isAdmin && !strcmp(passwordBuffer, customer.password))
    {
        isLoginSuccessful = true;

        writeBytes = write(connectionFileDescriptor, strcat(clpSuccessful, customer.customerName), strlen(clpSuccessful));
        if (writeBytes <= 0)
        {
            perror("Error while writing auth success prompt!");
            return isLoginSuccessful;
        }
    }
    else
    {
        writeBytes = write(connectionFileDescriptor, lpFailedCredentials, strlen(lpFailedCredentials));
        if (writeBytes <= 0)
        {
            perror("Error while writing auth failed credentials prompt!");
            return isLoginSuccessful;
        }
    }

    return isLoginSuccessful; // Failed login
}

// ====================================================