// Question : Write a separate program using signal system call to catch `SIGFPE`

#include <signal.h> // Import for `signal`, `raise`
#include <stdio.h>  // Import for `printf`, `scanf` & `perror`
#include <unistd.h> // Import for `_exit`

void sampleFunction()
{
    printf("Signal SIGFPE has been caught!\n");
    _exit(0);
}

void main()
{
    int a;
    __sighandler_t signalStatus; // Determines the success of the `signal` call

    signalStatus = signal(SIGFPE, (void *)sampleFunction);
    if (signalStatus == SIG_ERR)
        perror("Error while assigning signal handler!");
    else
        raise(SIGFPE); // Send a signal associated with floating point error
}