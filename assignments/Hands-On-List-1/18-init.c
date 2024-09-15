/*
    Question: Write a program to perform Record locking. 
    1. Implement write lock 
    2. Implement read lock
    Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `fcntl` & `open`
#include <unistd.h>    // Import for `write`, `lseek` & `fcntl`
#include <stdio.h>     // Import for `perror` & `printf`

#include "./18-record.h" // Header containing the record structure & file name where the records are stored

void main()
{
    struct flock lock;
    int fcntlStatus;
    int fileDescriptor;
    ssize_t readBytes, writeBytes;

    // Lock entire file
    lock.l_type = F_WRLCK;
    lock.l_len = 0;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_pid = getpid();

    struct record records[3];

    fileDescriptor = open(filename, O_CREAT | O_RDWR, S_IRWXU);

    if (fileDescriptor == -1)
        perror("Error while opening the file!");
    else
    {
        fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);
        if (fcntlStatus == -1)
            perror("Error while locking file!");
        else
        {
            readBytes = read(fileDescriptor, &records, sizeof(struct record) * 3);

            if (readBytes == -1)
                perror("Error while reading the file");
            else
            {
                // No contents in the file
                records[0].recordNumber = 1;
                records[0].someNumber = 0;

                records[1].recordNumber = 2;
                records[1].someNumber = 0;

                records[2].recordNumber = 3;
                records[2].someNumber = 0;

                writeBytes = write(fileDescriptor, &records, sizeof(struct record) * 3);

                if (writeBytes == -1)
                    perror("Error while writing to file!");
            }
            lock.l_type = F_UNLCK;
            fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);

            if (fcntlStatus == -1)
                perror("Error while unlocking file!");
        }
    }
}