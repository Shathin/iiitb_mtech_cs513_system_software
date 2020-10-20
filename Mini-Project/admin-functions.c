#include <stdio.h>   // Import for `printf` & `perror`
#include <unistd.h>  // Import for `read` & `write
#include <string.h>  // Import for string functions
#include <stdbool.h> // Import for `bool` data type

#include "./db-schema/customer.h"
#include "./db-schema/admin.h"
#include "./db-schema/account.h"
#include "./server-literals.c"

// Function prototype ================================

void admin_operation_handler(int connectionFileDesciptor);

// ADMIN OPERATION
bool add_customer(struct customer customerInfo);
bool add_account(bool isCustomerExisting, struct customer customerInfo, struct account accountInfo);
bool modify_customer(char *customerID, short int field);
bool modify_account(int accountNumber, short int field);

// ====================================================

// Function definition ================================

void admin_operation_handler(int connectionFileDescriptor)
{
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];
    int adminMenuChoice;

    if (login_handler(true, connectionFileDescriptor))
    {

        do
        {
            writeBytes = write(connectionFileDescriptor, adminMainMenu, strlen(adminMainMenu));
            if (writeBytes <= 0)
            {
                perror("Error while writing admin main menu prompt");
                return;
            }

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
            }

        } while (adminMenuChoice != 7);
    }
}


// ====================================================