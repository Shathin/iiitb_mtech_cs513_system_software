// Question: Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.

#include <unistd.h> // Import for `pipe`, `write` & `read` system call
#include <stdio.h>  // Import for `perror` and `printf`

void main()
{
    // File descriptor used for pipe operations
    int pipefd[2];                // pipefd[0] -> read, pipefd[1] -> write
    char *writeBuffer = "Yolo!!"; // Data sent through the pipe
    char *readBuffer;
    int pipeStatus;            // Variable used to determine success of `pipe` call
    int readBytes, writeBytes; // Number of bytes written using `write` & read using `read`

    // Creating a pipe
    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating the pipe! ");
    else
    {
        printf("Writing to the pipe!\n");
        writeBytes = write(pipefd[1], &writeBuffer, sizeof(writeBuffer));
        if (writeBytes == -1)
            perror("Error while writing to pipe!");
        else
        {
            printf("Now reading from the pipe!\n");
            readBytes = read(pipefd[0], &readBuffer, writeBytes);
            if (readBytes == -1)
                perror("Error while reading from pipe!");
            else
                printf("Data from pipe: %s\n", readBuffer);
        }
    }
}