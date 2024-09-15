// Question : Write a program to send and receive data from parent to child vice versa. Use two way communication.

#include <unistd.h>    // Import for `pipe`, `write`, `read` & `fork` system calls
#include <sys/types.h> // Import for `fork`
#include <stdio.h>     // Import for `printf` and `perror`

void main()
{
    // File descriptor used for pipe operations
    int childToParentfd[2], parentToChildfd[2]; // fd[0] -> read, fd[1] -> write
    int childToParentPipeStatus;
    int parentToChildPipeStatus; // Variable used to determine success of `pipe` call
    int readBytes, writeBytes;   // Number of bytes written using `write` & read using `read`
    char *writeBuffer, *readBuffer;

    pid_t childPid;

    childToParentPipeStatus = pipe(childToParentfd);
    parentToChildPipeStatus = pipe(parentToChildfd);

    if (childToParentPipeStatus == -1 || parentToChildPipeStatus == -1)
        perror("Error while creating the pipe!");
    else
    {
        childPid = fork();

        if (childPid == -1)
            perror("Error while forking child!");
        else if (childPid == 0)
        {
            // Child will enter this loop
            close(parentToChildfd[1]); // Close the write fd for the pipe used to send data from parent to child
            close(childToParentfd[0]); // Close the read fd for the pipe used to send data from child to parent

            // Sending data to parent
            writeBuffer = "Hi mom! It's me!";
            writeBytes = write(childToParentfd[1], &writeBuffer, sizeof(writeBuffer));
            if (writeBytes == -1)
                perror("Error while writing to  child to parent pipe!");

            // Reading from parent
            readBytes = read(parentToChildfd[0], &readBuffer, 100);
            if (readBytes == -1)
                perror("Error while reading from parent to child pipe!");
            else
                printf("The parent said: %s\n", readBuffer);
        }
        else
        {
            close(parentToChildfd[0]); // Close the read fd for the pipe used to send data from parent to child
            close(childToParentfd[1]); // Close the write fd for the pipe used to send data from child to parent

            // Sending data to child
            writeBuffer = "Hi child! It's me, mom!";
            writeBytes = write(parentToChildfd[1], &writeBuffer, sizeof(writeBuffer));
            if (writeBytes == -1)
                perror("Error while writing to  parent to child pipe!");

            // Reading from child!

            readBytes = read(childToParentfd[0], &readBuffer, 100);
            if (readBytes == -1)
                perror("Error while reading from child to parent pipe!");
            else
                printf("The child said: %s\n", readBuffer);
        }
    }
}