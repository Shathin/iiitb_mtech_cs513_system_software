// Question : Write a program to open an existing file with read write mode. Try O_EXCL flag also.

// Imports for `open` system call
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Import for `printf` & `perror` function
#include <stdio.h>
// Import for `write` call
#include <unistd.h>

void main(int argc, char *argv[])
{

    char *filename;
    int fileDescriptor; // FD -> Success, -1 -> Failure

    if (argc != 2)
    {
        write(STDOUT_FILENO, "Pass the file to be opened as the argument\n", 43);
    }
    else
    {
        filename = argv[1];

        fileDescriptor = open(filename, O_RDWR);

        if (fileDescriptor == -1)
            perror("Error while opening the file!");
        else
            printf("The file was successfully created with the file descriptor -> %dn", fileDescriptor);
    }
}