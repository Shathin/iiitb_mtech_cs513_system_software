#include <stdio.h> // Import for `printf` & `perror` functions
#include <errno.h> // Import for `errno` variable

#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `accept`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `accept` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture

#include <string.h> // Import for string functions
#include<stdbool.h> // Import for `bool` data type

#include "./server-text.h"
#include "./db-schema/customer.h"
#include "./db-schema/admin.h"
#include "./db-schema/account.h"


void connectionHandler(int connectionFileDescriptor); // Handles the communication with the client

// ADMIN OPERATION
bool add_customer(struct customer customerInfo);
bool add_account(bool isCustomerExisting, struct customer customerInfo, struct account accountInfo);
bool modify_customer(char* customerID, short int field);
bool modify_account(int accountNumber, short int field);
char* get_customer_info_by_id(int customerID);
char* get_account_info(int accountNumber);
// Experimental ADMIN OPERATION
char* get_customer_info_by_name(char *customerName); 

// CUSTOMER OPERATION




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

    int clientSize = (int)sizeof(clientAddress);
    connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress, &clientSize);
    if (connectionFileDescriptor == -1)
    {
        perror("Error while connecting to client!");
        close(socketFileDescriptor);
        _exit(0);
    }

    connectionHandler(connectionFileDescriptor);

    close(socketFileDescriptor);
}

void connectionHandler(int connectionFileDescriptor)
{

    ssize_t writeBytes;
    writeBytes = write(connectionFileDescriptor, initialPrompt, strlen(initialPrompt));
    if (writeBytes == -1)
        perror("Error while sending first prompt to the user!");
    else
    {
        printf("Wrote: %ld bytes\n!", writeBytes);
    }

    /*char readBuffer[1000];
    ssize_t readBytes, writeBytes;

    writeBytes = write(connectionFileDescriptor, "Hello there General Kenobi\0", 26);
    if(writeBytes == -1) {
        perror("Error while writing to client!");
    }
    else 
        printf("Data successfully sent to client!\n");
    
    readBytes = read(connectionFileDescriptor, readBuffer, sizeof(readBuffer));
    if(readBytes == -1) {
        perror("Error while reading data from client!");
    } else if(readBytes == 0) 
        printf("No data was sent by the client!\n");
    else 
        printf("Client says: %s\n", readBuffer);*/

    close(connectionFileDescriptor);
}
