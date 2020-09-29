/* Question: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes. 

    1. Check the return value of `lseek` 
    2. Open the file with `od` and check the empty spaces in between the data.
*/

// Imports for `open` and `close` system call
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Additional import required for `lseek` system call
#include <unistd.h>
// Import for `perror` and `printf` functions
#include <stdio.h>

void main(int argc, char *argv[])
{
    char *filename;     // File name of the source file
    int fileDescriptor; // File descriptor obtained after opening the source file
    int offset;         // Holds the new offset after seeking
    int writeByteCount; // Number of bytes written using `write`

    if (argc != 2)
        printf("Pass the file name as the argument!");
    else
    {
        filename = argv[1];
        fileDescriptor = open(filename, O_RDWR);

        if (fileDescriptor == -1)
            perror("Error while opening file! ");
        else
        {
            offset = lseek(fileDescriptor, 10, SEEK_SET); // Move forward 10 bytes from start of the file
            writeByteCount = write(fileDescriptor, "ABCDEFGHIJ", 10);
            if (writeByteCount == -1)
            {
                perror("Error while writing to the file!");
                _exit(1);
            }

            offset = lseek(fileDescriptor, 10, SEEK_CUR); // Move forward 10 bytes from the current position in the file
            writeByteCount = write(fileDescriptor, "ABCDEFGHIJ", 10);
            if (writeByteCount == -1)
            {
                perror("Error while writing to the file!");
                _exit(1);
            }
            
            printf("Return value of lseek: %d\n", offset);
            close(fileDescriptor);
        }
    }
}