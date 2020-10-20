#include <stdio.h>   // Import for `printf` & `perror`
#include <unistd.h>  // Import for `read` & `write
#include <string.h>  // Import for string functions
#include <stdbool.h> // Import for `bool` data type

#include "./db-schema/customer.h"
#include "./db-schema/admin.h"
#include "./db-schema/account.h"
#include "./server-literals.c"

// Function prototype ================================

void customer_operation_handler(int connectionFileDescriptor);

// CUSTOMER OPERATION
bool deposit(int accountNumber, int depositAmount);
bool withdraw(int accountNumber, int withdrawAmount);
char *balance_enquiry(int accountNumber);
bool verify_password(char *password);
bool password_change(char *newPassword, char *reNewPassword);

// ====================================================

// Function definition ================================

void customer_operation_handler(int connectionFileDescriptor)
{
    ssize_t writeBytes, readBytes;
    char readBuffer[1000], writeBuffer[1000];

    if (login_handler(false, connectionFileDescriptor))
    {
    }
}

// ====================================================