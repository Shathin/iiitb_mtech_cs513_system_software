// Question : Write a separate program using sigaction system call to catch `SIGSEGV` signal

#include <signal.h> // Import for `sigaction`
#include <stdio.h>  // Import for `perror` & `printf`
#include <unistd.h> // Import for `_exit(0)`

void signalHandler(int signalNumber)
{
    printf("Caught signal SIGSEGV (%d)\n", signalNumber);
    _exit(0);
}

void main()
{
    int status; // Determines success of `sigaction` call
    struct sigaction action;
    char *a;

    action.sa_handler = signalHandler;
    action.sa_flags = 0;

    status = sigaction(SIGSEGV, &action, NULL);
    if (status == -1)
        perror("Error while setting signal handler!");
    else
    {
        // Following line generates a segmentation fault
        a[100] = '1';
    }
}