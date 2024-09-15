// Question: Write a program to copy file1 into file2 ($cp file1 file2).

#include <sys/types.h> // Import for `open`  system call.
#include <sys/stat.h>  // Import for `open` system call.
#include <fcntl.h>     // Import for `open`  system call.
#include <unistd.h>    // Import for `read` and `write` system call
#include <stdio.h>     // Import for `perrro` and `printf` functions

// Drawback of program - If source file contains more than 1000 bytes all the contents will not be transferred to the destination
void main(int argc, char *argv[])
{

    char *sourcePath;
    char *destinationPath;

    int sourceFD, destinationFD; // The file descriptors of the source and destination files
    int sourceReadCount;         // Number of bytes read into the buffer from the source file
    int destinationWriteCount;   // Number of bytes written into destination file from buffer

    char *buffer[100]; // Buffer to store contents of the source file

    if (argc != 3)
        printf("Pass the source & destination file name as the argument\n");
    else
    {
        sourcePath = argv[1];
        destinationPath = argv[2];

        // Open source file in read only mode
        sourceFD = open(sourcePath, O_RDONLY);
        // Create destination file if it doesn't exist and open in read-write mode
        // Give the user all the permissions
        destinationFD = open(destinationPath, O_CREAT | O_RDWR, S_IRWXU);

        if (sourceFD == -1 || destinationFD == -1)
        {
            perror("Error while opening source / destination file");
            _exit(1);
        }

        // Keep reading 100 bytes at a time till no more can be read
        while ((sourceReadCount = read(sourceFD, buffer, 100)) > 0)
        {
            destinationWriteCount = write(destinationFD, buffer, sourceReadCount);
            if (destinationWriteCount == -1)
                perror("Error while writing content");
        }

        if (sourceReadCount == -1)
            perror("Error while reading content");
        else
            printf("Successfully copied the contents!\n");

        close(sourceFD);
        close(destinationFD);
    }
}