/*
    Question: Write a program to perform Record locking. 
    1. Implement write lock 

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

    printf("Trial : %d", record.someNumber);

    if (argc != 2)
    {
        printf("Pass the record number to be written as the argument program");
        _exit(0);
    }

    recordNumber = (int) *argv[1] - 48;
    printf("RECORD NUMBER: %d\n",recordNumber);

    fileDescriptor = open(filename, O_RDWR, S_IRWXU);

    if (fileDescriptor == -1)
        perror("Error while opening / creating the file");
    else
    {
        printf("Here...1\n");
        lock.l_type = F_WRLCK;
        lock.l_start = sizeof(struct record) * (recordNumber - 1);
        printf("START: %ld\n", lock.l_start);
        lock.l_len = sizeof(struct record);
        printf("LEN: %ld\n", lock.l_len);
        lock.l_whence = SEEK_SET;
        lock.l_pid = getpid();

        fcntlStatus = fcntl(fileDescriptor, F_GETLK, &lock);
        if (fcntlStatus == -1)
            perror("Error while checking lock status");
        else
        {
            printf("Here...2\n");
            switch (lock.l_type)
            {
            case F_WRLCK:
                // Record already has write lock
                printf("Record already has write lock!\n");
                break;
            case F_RDLCK:
                // Record already has read lock
                printf("Record already has read lock!\n");
                break;
            default:
                printf("Here...3\n");
                // Record is unlocked
                lock.l_type = F_WRLCK;
                fcntlStatus = fcntl(fileDescriptor, F_SETLKW, &lock);
                if (fcntlStatus == -1)
                    perror("Error while getting write lock on the record");
                else
                {
                    printf("Here...4\n");
                    lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
                    readBytes = read(fileDescriptor, &record, sizeof(record));
                    // printf("%s\n",record.recordName);
                    if (readBytes == -1)
                        perror("Error while reading record!");
                    else
                    {
                        printf("Here...5\n");
                        lseekOffset = lseek(fileDescriptor, lock.l_start, SEEK_SET);
                        if (lseekOffset == -1)
                            perror("Error while seeking!");
                        else
                        {
                            printf("Here...6: %ld\n", readBytes);
                            printf("Current record: %d", record.someNumber);
                            record.someNumber += 1;
                            writeBytes = write(fileDescriptor, &record, sizeof(struct record));
                            printf("Altered record: %d", record.someNumber);
                        }
                    }
                    printf("Here...7\n");
                    fcntlStatus = fcntl(fileDescriptor, F_UNLCK, &lock);
                    if (fcntlStatus == -1)
                        perror("Error while unlocking!");
                }
            }
            printf("Here...8\n");
            close(fileDescriptor);
        }
    }
}