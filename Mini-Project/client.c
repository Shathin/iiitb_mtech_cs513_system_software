#include <stdio.h> // Import for `printf` & `perror` functions
#include <errno.h> // Import for `errno` variable

#include <fcntl.h>      // Import for `fcntl` functions
#include <unistd.h>     // Import for `fork`, `fcntl`, `read`, `write`, `lseek, `_exit` functions
#include <sys/types.h>  // Import for `socket`, `bind`, `listen`, `connect`, `fork`, `lseek` functions
#include <sys/socket.h> // Import for `socket`, `bind`, `listen`, `connect` functions
#include <netinet/ip.h> // Import for `sockaddr_in` stucture

#include <string.h> // Import for string functions


void connection_handler(int socketFileDescriptor) // Handles the communication with the client
{
    char readBuffer[1000], writeBuffer[100];
    ssize_t readBytes, writeBytes;

    readBytes = read(socketFileDescriptor, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
        perror("Error while reading data from server!");
    else if (readBytes == 0)
        printf("No data was sent by the server!\n");

    while (readBytes > 0)
    {
        printf("%s\n", readBuffer);

        scanf("%[^\n]%*c", writeBuffer); // Take user input!

        writeBytes = write(socketFileDescriptor, writeBuffer, sizeof(writeBuffer));
        if (writeBytes == -1)
            perror("Error while writing to server!");

        readBytes = read(socketFileDescriptor, readBuffer, sizeof(readBuffer));
    }
}

void main()
{
    int socketFileDescriptor, connectStatus;
    struct sockaddr_in serverAddress;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Error while creating server socket!");
        _exit(0);
    }

    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_port = htons(8081);              // Server will listen to port 8080
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Binds the socket to all interfaces

    connectStatus = connect(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        close(socketFileDescriptor);
        _exit(0);
    }

    connection_handler(socketFileDescriptor);

    close(socketFileDescriptor);
}

