#ifndef ADMIN_FUNCTIONS
#define ADMIN_FUNCTIONS

#include "./common.h"

// Function Prototypes =================================

bool admin_operation_handler(int connFD);

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

#endif