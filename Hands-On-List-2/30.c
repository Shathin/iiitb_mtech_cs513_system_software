/* Question : Write a program to create a shared memory. 
    1. Write some data to the shared memory
    2. Attach with `O_RDONLY` and check whether you are able to overwrite. 
    3. Detach the shared memory 
    4. Remove the shared memory
*/

#include <sys/types.h> // Import for `ftok`, `shmget`, `shmat`
#include <sys/ipc.h>   // Import for `ftok`, `shmget`
#include <sys/shm.h>   // Import for `shmget`, `shmat`
#include <unistd.h>    // Import for `_exit`
#include <stdio.h>     // Import for `perror` & `printf`

void main()
{
    key_t shmKey;         // Key used to create / access Shared Memory
    int shmIdentifier;    // Identifier for the Shared Memory
    ssize_t shmSize = 20; // Size of the Shared Memory
    char *shmPointer;

    shmKey = ftok(".", 1);

    if (shmKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    shmIdentifier = shmget(shmKey, shmSize, IPC_CREAT | 0700); // Create the shared memory if it doesn't exist; if it exists use the existing one

    if (shmIdentifier == -1)
    {
        perror("Error while getting Shared Memory!");
        _exit(0);
    }

    shmPointer = shmat(shmIdentifier, (void *)0, 0);

    if (*shmPointer == -1)
    {
        perror("Error while attaching address space!");
        _exit(0);
    }

    printf("Press enter to write to the shared memory!\n");
    getchar();

    sprintf(shmPointer, "Yolo"); // Writing to the shared memory

    printf("Press enter to read from the shared memory!\n");
    getchar();

    printf("Data from shared memory: %s\n", shmPointer); // Reading from the shared memory

    printf("Detaching pointer to shared memory!\n");
    shmdt(shmPointer); // Dettach pointer to Shared Memory

    printf("Press enter to delete the shared memory!\n");
    getchar();

    // Delete Shared Memory
    shmctl(shmIdentifier, IPC_RMID, NULL);
}