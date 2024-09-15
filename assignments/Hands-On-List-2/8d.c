// Question : Write a separate program using signal system call to catch `SIGALRM` (use `alarm` system call)

#include <signal.h>   // Import for `signal`
#include <unistd.h>   // Import for `_exit`, `alarm`
#include <stdio.h>    // Import `perror` & `printf`

void callback()
{
    printf("Signal SIGALRM has been caught!\n");
    _exit(0);
}

void main()
{
    __sighandler_t signalStatus; // Determines status of `signal` call

    alarm(1); // Set an alarm for 1s

    // Catch the SIGALRM signal
    signalStatus = signal(SIGALRM, (void *)callback);
    if (signalStatus == SIG_ERR)
        perror("Error while catching signal!");
    else
        while (1);
}