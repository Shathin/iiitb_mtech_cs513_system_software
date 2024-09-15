// Question: Write a program to create a file and print the file descriptor value. Use creat() system call

#include <sys/types.h> // Import for `creat` system call
#include <sys/stat.h>  // Import for `creat` system call
#include <fcntl.h>     // Import for `creat` system call
#include <stdio.h>     // Import for `printf` & `perror` function

void main(int argc, char *argv[])
{

    char *filename;
    int fileDescriptor; // FD -> Success, -1 -> Error

    if (argc != 2)
        printf("Pass the file to open as argument\n");
    else
    {
        filename = argv[1];

        fileDescriptor = creat(filename, S_IRWXU);

        if (fileDescriptor == -1)
            perror("Error while creating the file!");
        else
            printf("The file was successfully created with the file descriptor -> %dn", fileDescriptor);
    }
}