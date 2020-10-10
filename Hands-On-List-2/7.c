// Question : Write a simple program to print the created thread IDs.

#include <pthread.h> // Import for `pthread_create`
#include <stdio.h>   // Import for `perror` & `printf`

void sampleFunction()
{
    printf("Running in thread...\n");
}

void main()
{
    pthread_t threadID;

    // Create three threads
    if(pthread_create(&threadID, NULL, (void *)sampleFunction, NULL))
        perror("Error while creating thread");

    printf("Created thread ID: %lu\n", threadID);

    pthread_exit(NULL);
}
