#include <stdio.h>     // Import for `printf` & `perror`
#include <unistd.h>    // Import for `read`, `write & `lseek`
#include <string.h>    // Import for string functions
#include <stdbool.h>   // Import for `bool` data type
#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <stdlib.h>    // Import for `atoi`

#include "./db-schema/customer.h"
#include "./db-schema/admin.h"
#include "./db-schema/account.h"
#include "./server-literals.h"

#ifndef COMMON_FUNCTIONS
#define COMMON_FUNCTIONS
// Function prototype ================================
bool login_handler(bool isAdmin, int connectionFileDescriptor);

// ADMIN - CUSTOMER COMMON OPERATIONS
char *get_customer_info_by_id(int customerID);
char *get_account_info(int accountNumber);

// ====================================================

// Function definition ================================

bool login_handler(bool isAdmin, int connectionFileDescriptor)
{
    // printf("Login procedure has now begun!\n");

    ssize_t readBytes, writeBytes;   // Number of bytes written to / read from the socket
    char outputString[1000];         // A general buffer used to write to the socket
    char loginID[50], password[100]; // A buffer used to store the incoming client's login ID and password
    bool isLoginSuccessful = false;  // Determines success of the `login_handler` function
    struct admin admin;
    struct customer customer;
    int ID;             // Holds the customer's / admin's ID. Used to reference directly to the admin / customer information structure
    int fileDescriptor; // Holds the file descriptor to the admin or the customer file

    bzero(outputString, sizeof(outputString)); // Empty the outputString

    // Get the welcome prompt for the respective type of client
    if (isAdmin)
        strcpy(outputString, alpWelcome);
    else
        strcpy(outputString, clpWelcome);

    // Get the 'enter login ID' prompt
    strcpy(outputString, "\n");
    strcat(outputString, lpLogin);

    writeBytes = write(connectionFileDescriptor, outputString, strlen(outputString));
    if (writeBytes <= 0)
    {
        perror("Error while sending loginID prompt!");
        return isLoginSuccessful;
    }

    bzero(loginID, sizeof(loginID)); // Empty the loginID buffer
    readBytes = read(connectionFileDescriptor, loginID, sizeof(loginID));
    if (readBytes <= 0)
    {
        perror("Error while receiving loginID!");
        return isLoginSuccessful;
    }

    // Get the admin / customer ID
    ID = atoi(strtok(loginID, "-"));

    // Search for admin / customer & get their data (struct)
    if (isAdmin)
    {
        fileDescriptor = open("./db/admin", O_RDONLY);
        lseek(fileDescriptor, SEEK_SET, (int)(ID * sizeof(admin)));
        readBytes = read(fileDescriptor, &admin, sizeof(admin));
        if (readBytes == -1)
        {
            perror("Error while reading from admin file");
            return isLoginSuccessful;
        }
        else if (readBytes == 0)
        {
            printf("Credentials don't match!");
            write(connectionFileDescriptor, lpFailedCredentials, strlen(lpFailedCredentials));
            return isLoginSuccessful;
        }
    }
    else
    {
        fileDescriptor = open("./db/customer", O_RDONLY);
        lseek(fileDescriptor, SEEK_SET, (int)(ID * sizeof(admin)));
        readBytes = read(fileDescriptor, &customer, sizeof(customer));
        if (readBytes == -1)
        {
            perror("Error while reading from customer file");
            return isLoginSuccessful;
        }
        else if (readBytes == 0)
        {
            write(connectionFileDescriptor, lpFailedCredentials, strlen(lpFailedCredentials));
            return isLoginSuccessful;
        }
    }

    writeBytes = write(connectionFileDescriptor, lpPassword, strlen(lpPassword));
    if (writeBytes <= 0)
    {
        perror("Error while writing password prompt!");
        return isLoginSuccessful;
    }

    bzero(password, sizeof(password));

    readBytes = read(connectionFileDescriptor, password, sizeof(password));
    if (readBytes <= 0)
    {
        perror("Error while receiving password!");
        return isLoginSuccessful;
    }

    if (isAdmin && !strcmp(password, admin.password))
    {
        isLoginSuccessful = true; // Successful login

        bzero(outputString, sizeof(outputString)); // Empty the outputString buffer

        strcat(outputString, alpSuccessful);
        strcat(outputString, admin.adminName);
        strcat(outputString, "\nPress enter to continue!");

        writeBytes = write(connectionFileDescriptor, outputString, strlen(outputString));
        if (writeBytes <= 0)
        {
            perror("Error while writing auth success prompt!");
            return isLoginSuccessful;
        }
    }
    else if (!isAdmin && !strcmp(password, customer.password))
    {
        isLoginSuccessful = true; // Successful login

        strcat(outputString, clpSuccessful);
        strcat(outputString, customer.customerName);
        strcat(outputString, "\nPress enter to continue!");

        writeBytes = write(connectionFileDescriptor, strcat(strcat(outputString, clpSuccessful), admin.adminName), strlen(outputString));
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

    return isLoginSuccessful;
}

// ====================================================

#endif