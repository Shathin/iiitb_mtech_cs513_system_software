// Question : Write a separate program using signal system call to catch `SIGINT`

#include <signal.h> // Import for `signal`
#include <stdio.h>  // Import for `printf`, `scanf` & `perror`
#include <unistd.h> // Import for `_exit`

void sampleFunction()
{
    printf("\nSignal SIGINT has been caught!\n");
    _exit(0);
}

void main()
{
    char *a;
    __sighandler_t signalStatus; // Determines the success of the `signal` call

    signalStatus = signal(SIGINT, (void *)sampleFunction);
    if (signalStatus == SIG_ERR)
        perror("Error while assigning signal handler!");
    else
        while(1);
}