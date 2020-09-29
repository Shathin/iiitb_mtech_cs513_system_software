// Question: Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not using `fcntl`

// Imports for `open` system call
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
// Additional import required for `fcntl` system call
#include<unistd.h>
// Import required for `perror` function
#include<stdio.h>

void main(int argc, char *argv[])
{

    char *filename;                        // File name of the source file
    int fileDescriptor, dupFileDescriptor; // The original & duplicate file descriptor
    int writeByteCount;                    // Number of bytes written to the source file

    if (argc != 2)
        printf("Pass the file name as the argument!");
    else
    {
        filename = argv[1];
        fileDescriptor = open(filename, O_WRONLY | O_APPEND);
        if (fileDescriptor == -1)
            perror("Error while opening file");
        else
        {
            dupFileDescriptor = fcntl(fileDescriptor, F_DUPFD);

            // Writing using original file descriptor
            writeByteCount = write(fileDescriptor, "Using original FD", 17);
            if (writeByteCount == -1)
                perror("Error while writing file using original FD");

            // Writing using duplicate file descriptor
            writeByteCount = write(dupFileDescriptor, "Using duplicate FD", 18);
            if (writeByteCount == -1)
                perror("Error while writing file using duplicate FD");

            close(fileDescriptor);
        }
    }
}

