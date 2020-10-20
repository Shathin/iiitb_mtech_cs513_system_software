#include <stdio.h> // Import for `printf` & `perror` functions
#include <errno.h> // Import for `errno` variable

#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `accept`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `accept` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture

#include <string.h>  // Import for string functions
#include <stdbool.h> // Import for `bool` data type
#include <stdlib.h>  // Import for `atoi` function

#include "./server-literals.c"

#include "./common-functions.c"
#include "./admin-functions.c"
#include "./customer-functions.c"

void connection_handler(int connectionFileDescriptor); // Handles the communication with the client

void main()
{
    int socketFileDescriptor, socketBindStatus, socketListenStatus, connectionFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Error while creating server socket!");
        _exit(0);
    }

    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8081);              // Server will listen to port 8080
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Binds the socket to all interfaces

    socketBindStatus = bind(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (socketBindStatus == -1)
    {
        perror("Error while binding to server socket!");
        _exit(0);
    }

    socketListenStatus = listen(socketFileDescriptor, 10);
    if (socketListenStatus == -1)
    {
        perror("Error while listening for connections on the server socket!");
        close(socketFileDescriptor);
        _exit(0);
    }

    int clientSize;
    while (1)
    {
        if (!fork())
        {
            // Child will enter this branch
            clientSize = (int)sizeof(clientAddress);
            connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress, &clientSize);
            if (connectionFileDescriptor == -1)
            {
                perror("Error while connecting to client!");
                close(socketFileDescriptor);
                _exit(0);
            }

            connection_handler(connectionFileDescriptor);
        }
    }

    close(socketFileDescriptor);
}

void connection_handler(int connectionFileDescriptor)
{
    char readBuffer[1000], writeBuffer[1000];
    ssize_t readBytes, writeBytes;
    int userChoice;
    bool invalidChoice = false;

    writeBytes = write(connectionFileDescriptor, initialPrompt, strlen(initialPrompt));
    if (writeBytes == -1)
        perror("Error while sending first prompt to the user!");

    do
    {
        readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error while reading from client");
            invalidChoice = true;
        }
        else if (readBytes == 0)
        {
            printf("No data was sent by the client");
            invalidChoice = true;
        }
        else
        {
            userChoice = atoi(readBuffer);
            switch (userChoice)
            {
            case 1:
                // Admin
                admin_operation_handler(connectionFileDescriptor);
                break;
            case 2:
                // Customer
                customer_operation_handler(connectionFileDescriptor);
                break;
            case 3:
                // Exit
                break;
            default:
                // Invalid Choice
                invalidChoice = true;
                break;
            }
        }
    } while (invalidChoice);

    close(connectionFileDescriptor);
}




