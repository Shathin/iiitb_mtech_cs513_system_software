// Question : Write a program to implement semaphore to protect any critical section - Rewrite the ticket number creation program using semaphore

#include <sys/ipc.h>   // Import for `ftok`, `semget`, `semctl`
#include <sys/sem.h>   // Import for `semget`, `semctl`
#include <sys/types.h> // Import for `open`, `lseek`, `ftok`, `semget`, `semctl`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`, `lseek`, `_exit`
#include <stdio.h>     // Import for `perror` & `printf`

void main()
{
    char *ticketFile = "./sample-files/ticket-file.txt"; // Name of the file used for storing the ticker number

    int fileDescriptor;            // File descriptor of the ticket file
    ssize_t readBytes, writeBytes; // Number of bytes read from / written to the ticket file
    off_t lseekOffset;
    int data; // Ticket data

    key_t semKey;      // Semaphore Key
    int semIdentifier; // Semaphore Identifier
    int semctlStatus;  // Determines success of `semctl` call
    int semopStatus;   // Determines success of `semop` call

    // Create a new ticket file / open an exisiting one
    fileDescriptor = open(ticketFile, O_CREAT | O_RDWR, S_IRWXU);
    if (fileDescriptor == -1)
    {
        perror("Error while creating / opening the ticket file!");
        _exit(0);
    }

    // Defines a semaphore's structure
    union semun
    {
        int val;               // Value of the semaphore
        struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
        unsigned short *array; /* Array for GETALL, SETALL */
        struct seminfo *__buf; /* Buffer for IPC_INFO (Linux-specific) */
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

        semSet.val = 1; // Set a binary semaphore
        semctlStatus = semctl(semIdentifier, 0, SETVAL, semSet);
        if (semctlStatus == -1)
        {
            perror("Error while initializing a binary sempahore!");
            _exit(1);
        }
    }

    struct sembuf semOp; // Defines the operation on the semaphore
    semOp.sem_num = 0;
    semOp.sem_flg = 0;

    printf("Press enter to obtain lock on the critical section\n");
    getchar();
    // Use semaphore to lock the critical section
    semOp.sem_op = -1;
    semopStatus = semop(semIdentifier, &semOp, 1);
    if (semopStatus == -1)
    {
        perror("Error while operating on semaphore!");
        _exit(1);
    }
    
    printf("Obtained lock on critical section!\n");
    printf("Now entering critical section!\n");
    // =========== Start of Critical Section ===========

    readBytes = read(fileDescriptor, &data, sizeof(data));
    if (readBytes == -1)
    {
        perror("Error while reading from ticket file!");
        _exit(0);
    }
    else if (readBytes == 0) // Ticket file has no data
        data = 1;
    else
    {
        data += 1;
        lseekOffset = lseek(fileDescriptor, 0, SEEK_SET);
        if (lseekOffset == -1)
        {
            perror("Error while seeking!");
            _exit(0);
        }
    }

    writeBytes = write(fileDescriptor, &data, sizeof(data));
    if (writeBytes == -1)
    {
        perror("Error while writing to ticket file!");
        _exit(1);
    }

    printf("Your ticker number is - %d\n", data);

    printf("Press enter to exit from critical section!\n");
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