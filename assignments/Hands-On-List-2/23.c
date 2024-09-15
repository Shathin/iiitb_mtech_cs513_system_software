// Question : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).

#include <unistd.h>    // Import for `sysconf`, `sysconf`
#include <sys/types.h> // Import for `mkfifo`
#include <sys/stat.h>  // Import for `mkfifo`
#include <stdio.h>     // Import for `perrore & `printf`
#include <errno.h>     // Import for `errno`

void main()
{
    int fifoStatus;  // Determines success of `mkfifo` call
    long maxFiles;   // Maximum number of files that can be opened within process
    long sizeOfPipe; // The maximim size of a FIFO file

    char *fifoName = "23-fifo";
    fifoStatus = mkfifo(fifoName, S_IRWXU);

    if (!(errno == EEXIST || fifoStatus != -1))
        perror("Error while creating FIFO file!");
    else
    {
        maxFiles = sysconf(_SC_OPEN_MAX);

        if (maxFiles == -1)
            perror("Error while calling sysconf!");
        else
            printf("Maximum number of files that can be opened is: %ld\n", maxFiles);

        sizeOfPipe = pathconf(fifoName, _PC_PIPE_BUF);

        if (sizeOfPipe == -1)
            perror("Error while calling pathconf!");
        else
            printf("Maximum size of pipe: %ld\n", sizeOfPipe);
    }
}
