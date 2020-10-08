// Question : Write a simple program to create three threads.

#include <pthread.h> // Import for `pthread_create`, `pthread_self`
#include <stdio.h>   // Import for `perror` & `printf`

void sampleFunction()
{
    printf("Running in thread: %lu\n", pthread_self());
}

void main()
{
    pthread_t threadOne, threadTwo, threadThree;

    // Create three threads
    if (pthread_create(&threadOne, NULL, (void *)sampleFunction, NULL))
        perror("Error while creating thread one");
    if (pthread_create(&threadTwo, NULL, (void *)sampleFunction, NULL))
        perror("Error while creating thread two");
    if (pthread_create(&threadThree, NULL, (void *)sampleFunction, NULL))
        perror("Error while creating thread three");

    // Wait for the threads to terminate and then terminate the main process
    if (pthread_join(threadOne, NULL))
        perror("Error while waiting for thread one");
    if (pthread_join(threadTwo, NULL))
        perror("Error while waiting for thread two");
    if (pthread_join(threadThree, NULL))
        perror("Error while waiting for thread three");
}
