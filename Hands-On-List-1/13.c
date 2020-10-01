// Question : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).

#include <sys/time.h>  // Import for `select` system call
#include <sys/types.h> // Import for `select` system call
#include <unistd.h>    // Import for `select` system call
#include <stdio.h>     // Imports for `perror & `printf` function

void main()
{
    fd_set readFDSet, writeFDSet;

    struct timeval time;

    int returnVal;

    // FD_ZERO(&readFDSet);
    FD_SET(STDIN_FILENO, &readFDSet);   // Adding STDIN to the set of file descriptors to read from
    FD_SET(STDOUT_FILENO, &writeFDSet); // Adding STDOUT to the set of file descriptors to write to

    // Setting the time to wait to 10s
    time.tv_sec = 10;
    time.tv_usec = 0;

    returnVal = select(1, &readFDSet, &writeFDSet, NULL, &time);

    if (returnVal == -1)
        perror("ERROR ");
    else if (returnVal) // returnVal -> 1 due because STDIN will contain the data
        printf("The data is now available\n");
    else // returnVal -> 0 due to time out
        printf("No data was given for 10 seconds\n");
}
