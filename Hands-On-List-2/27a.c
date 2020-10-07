// Question : Write a program to receive messages from the message queue with `0` as a flag 

#include <sys/types.h> // Import for `ftok` `msgget` & `msgrcv`
#include <sys/ipc.h>   // Import for `ftok` `msgget` & `msgrcv`
#include <sys/msg.h>   // Import for `msgget` & `msgrcv`
#include <stdio.h>     // Import for `perror` & `printf`
#include <unistd.h>    // Import for `_exit`

void main()
{
    key_t queueKey;      // IPC (Message Queue) key
    int queueIdentifier; // IPC (Message Queue) identifier
    ssize_t messageSize; // Determines success of `msgsnd` call

    struct msgbuf
    {
        long mtype;      // Used to identify message type - should be > 0
        int  someNumber; // Integer data
    } data;

    queueKey = ftok(".", 1);

    if (queueKey == -1)
    {
        perror("Error while computing key!");
        _exit(0);
    }

    queueIdentifier = msgget(queueKey, IPC_CREAT | 0700);

    if (queueIdentifier == -1)
    {
        perror("Error while creating message queue!");
        _exit(0);
    }

    data.mtype = 1;

    messageSize = msgrcv(queueIdentifier, &data, sizeof(data), data.mtype, 0);

    if(messageSize == -1) {
        perror("Error while sending getting via Message Queue!");
        _exit(0);
    }

    printf("Received number: %d\n", data.someNumber);
}