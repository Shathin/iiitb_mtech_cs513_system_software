// Question : Write a program to implement semaphore to protect any critical section - Protect multiple pseudo resources (may be two) using counting semaphore 

#include <sys/ipc.h>   // Import for `ftok`, `semget`, `semctl`
#include <sys/sem.h>   // Import for `semget`, `semctl`
#include <sys/types.h> // Import for `open`, `lseek`, `ftok`, `semget`, `semctl`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`, `lseek`, `_exit`
#include <stdio.h>     // Import for `perror` & `printf`

void main()
{
    char *filename = "./sample-files/lorem-ipsum.txt"; // File name of the sample file

    int fileDescriptor;            // File descriptor of the sample file
    ssize_t readBytes; // Number of bytes read from s
    off_t lseekOffset;
    char data[1000]; // Sample data

    key_t semKey;      // Semaphore Key
    int semIdentifier; // Semaphore Identifier
    int semctlStatus;  // Determines success of `semctl` call
    int semopStatus;   // Determines success of `semop` call

    // Create a new ticket file / open an exisiting one
    fileDescriptor = open(filename, O_RDONLY);
    if (fileDescriptor == -1)
    {
        perror("Error while creating / opening the ticket file!");
        _exit(0);
    }

    // Defines a semaphore's structure
    union semun
    {
        int val;               // Value of the semaphore
    } semSet;

    semKey = ftok(".", 331);
    if (semKey == -1)
    {
        perror("Error while computing key!");
        _exit(1);
    }

    semIdentifier = semget(semKey, 1, 0); // Get the semaphore if it exists
    if (semIdentifier == -1)
    {
        semIdentifier = semget(semKey, 1, IPC_CREAT | 0700); // Create a new semaphore 
        if (semIdentifier == -1)
        {
            perror("Error while creating semaphore!");
            _exit(1);
        }

        semSet.val = 2; // Set a counting semaphore
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; // Defines the operation on the semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = IPC_NOWAIT;

    printf("Press enter to obtain lock for the critical section!\n");
    getchar();

    // Use semaphore to lock the critical section
    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    printf("Obtained lock on critical section!");

    printf("Now entering critical section!");

    // =========== Start of Critical Section ===========

    readBytes = read(fileDescriptor, &data, 1000);
    if (readBytes == -1)
    {
        perror("Error while reading from sample file!");
        _exit(0);
    }
    else if (readBytes == 0) // Sample file has no data
        printf("No data exists!\n");
    else
        printf("Sample data: \n %s", data);

    printf("\n\nPress enter key to exit critical section!\n");
    getchar();

    // =========== End of Critical Section =============

    // Use semaphore to unlock the critical section
    semOp.sem_op = 1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }

    close(fileDescriptor);
}