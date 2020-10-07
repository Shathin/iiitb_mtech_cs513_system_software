// Question : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.

#include <sys/types.h> // Import for `open`, `select`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <sys/time.h>  // Import for `select`
#include <unistd.h>    // Import for `select`, `read`
#include <stdio.h>     // Import for `perror`

#include "./22-global.h"

void main()
{
    int fileDescriptor, writeBytes;
    char data[100];

    fileDescriptor = open(fifoName, O_NONBLOCK | O_WRONLY);

    if (fileDescriptor == -1)
    {
        perror("Error while opening FIFO file!");
        _exit(0);
    }

    writeBytes = write(fileDescriptor, "Hello there . . . ", 18);

    if (writeBytes == -1)
        perror("Error while writing to FIFO!");

    close(fileDescriptor);
}