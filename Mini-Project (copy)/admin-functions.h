#include <stdio.h>   // Import for `printf` & `perror`
#include <unistd.h>  // Import for `read` & `write
#include <string.h>  // Import for string functions
#include <stdbool.h> // Import for `bool` data type
#include <stdlib.h>  // Import for `atoi`

// #include "./db-schema/customer.h"
// #include "./db-schema/admin.h"
// #include "./db-schema/account.h"
#include "./server-literals.h"
#include "./common-functions.h"

// Function prototype ================================

void admin_operation_handler(int connectionFileDesciptor);

// ADMIN OPERATION
bool add_customer(struct customer *customer);
bool add_account(struct account *account);
bool add_account_handler(int connectionFileDescriptor);
bool modify_customer(char *customerID, short int field);
bool modify_account(int accountNumber, short int field);

// ====================================================

// Function definition ================================

void admin_operation_handler(int connectionFileDescriptor)
{
    printf("admin_operation_handler() is now running!\n");
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];
    int adminMenuChoice;

    if (login_handler(true, connectionFileDescriptor))
    {
        printf("Successful login detected!\n");

        do
        {
            writeBytes = write(connectionFileDescriptor, adminMainMenu, strlen(adminMainMenu));
            if (writeBytes <= 0)
            {
                perror("Error while writing admin main menu prompt");
                return;
            }

            bzero(readBuffer, sizeof(readBuffer));

            readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
            if (readBytes <= 0)
            {
                perror("Error while reading admin choice!");
                return;
            }

            adminMenuChoice = atoi(readBuffer);

            switch (adminMenuChoice)
            {
            case 1:
                // Add a new account
                add_account_handler(connectionFileDescriptor);
                break;
            case 2:
                // Delete an account
                break;
            case 3:
                // Modify customer info
                break;
            case 4:
                // Modify account info
                break;
            case 5:
                // Get customer details
                break;
            case 6:
                // Get account details
                break;
            case 7:
                // Logout
                break;
            default:
                // Invalid choice
                break;
            }

        } while (adminMenuChoice != 7);
    }
}

bool add_account_handler(int connectionFileDescriptor)
{
    ssize_t writeBytes, readBytes;            // Number of bytes written to / read from the socket
    char readBuffer[1000], writeBuffer[1000]; // Buffers used from writing & reading

    bool isExistingCustomer = false;

    int accountFileDescriptor, customerFileDescriptor;
    off_t lseekOffset;

    struct customer *customer;
    struct account *account;

    short int isAccountRegular;
    writeBytes = write(connectionFileDescriptor, acmAccountType, strlen(acmAccountType));
    if (writeBytes <= 0)
    {
        perror("Error while writing account type request to client!");
        return false;
    }
    do
    {
        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
        if (readBytes <= 0)
        {
            perror("Error while reading account type response from client!");
            return false;
        }
        isAccountRegular = atoi(readBuffer);
        if (isAccountRegular == 0 || isAccountRegular == 1)
            account->isAccountRegular = isAccountRegular;
        else
        {
            writeBytes = write(connectionFileDescriptor, acmAccountTypeInvalid, strlen(acmAccountTypeInvalid));
            if (writeBuffer <= 0)
            {
                perror("Error while writing acmAccountTypeInvalid message to client!");
                return false;
            }
        }
    } while (isAccountRegular != 0 || isAccountRegular != 1);

    bzero(writeBuffer, sizeof(writeBuffer));

    writeBytes = write(connectionFileDescriptor, acmCustomerExists, strlen(acmCustomerExists));
    if (writeBytes <= 0)
    {
        perror("Error while writing customer exists prompt to the client!");
        return false;
    }

    bzero(readBuffer, sizeof(readBuffer));

    readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
    if (readBytes <= 0)
    {
        perror("Error while reading customer exists prompt response from client!");
        return false;
    }

    isExistingCustomer = strcmp(readBuffer, "y") == 0 ? true : false;

    if (isExistingCustomer)
    {

        bzero(writeBuffer, sizeof(writeBuffer));
        writeBytes = write(connectionFileDescriptor, acmCustomerID, strlen(acmCustomerID));
        if (writeBytes <= 0)
        {
            perror("Error while writing customer ID request to client!");
            return false;
        }

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
        if (readBytes <= 0)
        {
            perror("Error while reading customer ID response from client!");
            return false;
        }

        int customerID = atoi(readBuffer);

        customerFileDescriptor = open("./db/customer", O_CREAT | O_RDONLY | S_IRWXU);
        if (customerFileDescriptor == -1)
        {
            perror("Error while opening customer db file!");
            return false;
        }
        lseekOffset = lseek(customerFileDescriptor, SEEK_SET, customerID * sizeof(struct customer));
        if (lseekOffset == -1)
        {
            perror("Error while seeking through customer file!");
            return false;
        }

        bzero(readBuffer, sizeof(readBuffer));
        readBytes = read(customerFileDescriptor, customer, sizeof(struct customer));
        if (readBytes == -1)
        {
            perror("Error while reading customer struct from customer db file!");
            return false;
        }
    }
    else
    {
    }

    add_account(account);

    if (account == NULL)
    {
        // Error while creating account
        writeBytes = write(connectionFileDescriptor, acmAccountCreationError, strlen(acmAccountCreationError));
        if (writeBytes <= 0)
        {
            perror("Error while writing account creation error message to client!");
            return false;
        }
    }
    else
    {
        bzero(writeBuffer, sizeof(writeBuffer));

        strcpy(writeBuffer, acmAccountCreationSuccess);
        sprintf(writeBuffer, "\nBasic Customer Info:\n\tCustomer ID: %d\n\tCustomer Name: %s\nAccount Information\n\tAccount number: %d\n\tAccount Type: %s\n\t", customer->customerID, customer->customerName, account->accountNumber, (account->isAccountRegular ? "Regular" : "Joint"));
        sprintf(writeBuffer, "[ ");
        for (int iter = 0; iter < 4 && account->owners[iter] != -1; iter++)
        {
            // TODO : Do a call to get get_customer_info_by_id to get customer name & ID instead
            // Temporary printing of customer ID.
            sprintf(writeBuffer, "%d, ", account->owners[iter]);
        }
        sprintf(writeBuffer, "\b\b ]");
        sprintf(writeBuffer, "Opening Balance : %d\n", account->balance);

        writeBytes = write(connectionFileDescriptor, writeBuffer, strlen(writeBuffer));
        if (writeBytes <= 0)
        {
            perror("Error while writing to new account info to client!");
            return false;
        }
    }
}

bool add_account(struct account *account)
{
}

// ====================================================