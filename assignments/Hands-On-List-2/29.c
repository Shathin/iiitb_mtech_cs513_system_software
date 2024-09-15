// Question : Write a program to remove the message queue.

#include <sys/types.h> // Import for `ftok` `msgget` & `msgctl`
#include <sys/ipc.h>   // Import for `ftok` `msgget` & `msgctl`
#include <sys/msg.h>   // Import for `msgget` & `msgctl`
#include <stdio.h>     // Import for `perror` & `printf`
#include <unistd.h>    // Import for `_exit`

void main()
{
    key_t queueKey;      // IPC (Message Queue) key
    int queueIdentifier; // IPC (Message Queue) identifier
    int msgctlStatus;    // Determines success of `msgctl` call

    queueKey = ftok(".", 1);

    if (queueKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT | 0700);
    if (queueIdentifier == -1)
    {
        perror("Error while creating Message Queue!");
        _exit(0);
    }

    printf("Key: %d\n", queueKey);
    printf("Message Queue Identifier: %d\n\n", queueIdentifier);

    msgctlStatus = msgctl(queueIdentifier, IPC_RMID, NULL);

    if (msgctlStatus == -1)
    {
        perror("Error while removing Message Queue");
        _exit(0);
    }
}
