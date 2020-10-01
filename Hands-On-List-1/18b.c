/*
    Question: Write a program to perform Record locking.
    2. Implement read lock

    Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include <sys/types.h> // Import for `open`, `lseek`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `fcntl` & `open`
#include <unistd.h>    // Import for `lseek` & `fcntl`
#include <stdio.h>     // Import for `perror` & `printf`

#include "./18-record.h" // Header containing the record structure & file name where the records are stored

void main(int argc, char *argv[])
{
    int fileDescriptor, fcntlStatus, recordNumber;
    ssize_t readBytes, writeBytes;
    off_t lseekOffset;
    struct flock lock;
    struct record record;

    if (argc != 2)
    {
        printf("Pass the record number to be read as the argument program\n");
        _exit(0);
    }

    recordNumber = (int)*argv[1] - 48;

    if (recordNumber > 0 && recordNumber < 4)
    {
        fileDescriptor = open(filename, O_RDONLY);

        if (fileDescriptor == -1)
            perror("Error while opening the file");
        else
        {
            lock.l_type = F_RDLCK;
            lock.l_start = sizeof(struct record) * (recordNumber - 1);
            lock.l_len = sizeof(struct record);
            lock.l_whence = SEEK_SET;
            lock.l_pid = getpid();

            fcntlStatus = fcntl(fileDescriptor, F_GETLK, &lock);
            if (fcntlStatus == -1)
                perror("Error while checking lock status");
            else
            {
                switch (lock.l_type)
                {
                case F_WRLCK:
                    // Record already has write lock
                    printf("Record already has write lock!\n");
                    break;
                default:
                    // Record is unlocked / is locked for reading
                    lock.l_type = F_RDLCK;
                    fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);
                    if (fcntlStatus == -1)
                        perror("Error while getting read lock on the record");
                    else
                    {
                        lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
                        printf("Reading record %d...\n", recordNumber);
                        readBytes = read(fileDescriptor, &record, sizeof(record));

                        if (readBytes == -1)
                            perror("Error while reading record!");
                        else
                        {
                            lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
                            if (lseekOffset == -1)
                                perror("Error while seeking!");
                            else
                                printf("The record %d has the value %d\n", record.recordNumber, record.someNumber);
                        }
                        // sleep(10); //Uncomment for to delay the releasing of the read lock
                        fcntlStatus = fcntl(fileDescriptor, F_UNLCK, &lock);
                        if (fcntlStatus == -1)
                            perror("Error while unlocking!");
                    }
                }
                close(fileDescriptor);
            }
        }
    }
    else
        printf("Record with %d doesn't exist!\n", recordNumber);
}