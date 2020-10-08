// Question : Write a simple program to create three threads.

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

    // Wait for the threads to terminate and then terminate the main process
    if(pthread_join(threadID, NULL))
        perror("Error while waiting for thread");
}
