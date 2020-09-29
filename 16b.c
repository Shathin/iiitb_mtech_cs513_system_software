/*
Question: Write a program to perform mandatory locking. 
    - Implement read lock 
*/

// Imports for `fcntl`
#include <unistd.h>
#include <fcntl.h>
// Additional imports for `open`
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char *argv[])
{

    char *filename;
    struct flock lock, lockStatus;
    int fileDescriptor;

    if (argc != 2)
        printf("Pass the file name to be locked as the argument!");
    else
    {
        filename = argv[1];

        // Defining lock paramaters
        lock.l_type = F_RDLCK;    // Write lock
        lock.l_whence = SEEK_SET; // Start of the file
        lock.l_start = 0;
        lock.l_len = 0; // When set to 0, it locks the entire file
        lock.l_pid = getpid();

        // Copying lock contents, used for checking if a lock has already been placed on the file
        lockStatus = lock;

        // Opening the file
        fileDescriptor = open(filename, O_RDONLY);

        // Checking file lock status
        fcntl(fileDescriptor, F_GETLK, &lockStatus);

        if (lockStatus.l_type == F_WRLCK)
            printf("File already locked for writing\n");
        else if (lockStatus.l_type == F_RDLCK)
            printf("File already locked for reading\n");
        else
        {
            // Applying lock
            fcntl(fileDescriptor, F_SETLK, &lock);
            printf("File is now locked for reading\n");
        }

        // pause(); // Used for testing purposes, prevents the program from terminating
    }
}