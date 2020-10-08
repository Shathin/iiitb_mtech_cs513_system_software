// Question - Write a separate program (for each time domain) to set a interval timer in 10s and 10ms - `ITIMER_VIRTUAL`

#include <sys/time.h> // Import `setitimer`
#include <signal.h>   // Import for `signal`
#include <unistd.h>   // Import for `pause`
#include <stdio.h>    // Import `perror` & `printf`

void sampleFunction()
{
    printf("Hello there...\n");
}

void main(int argc, char *argv[])
{
    int statusTimer10s, statusTimer10ms; // Determines success of `setitimer` call
    __sighandler_t signalStatus;         // Determines status of `signal` call

    struct itimerval timer10s, timer10ms;

    if (argc != 2)
    {
        printf("Pass 1 for 10s timer or 2 for 10ms timer\n");
        _exit(0);
    }

    if ((int)(*argv[1] - 48) == 1)
    {
        // Setting a interval timer for 10s
        timer10s.it_interval.tv_sec = 10;
        timer10s.it_interval.tv_usec = 0;
        timer10s.it_value.tv_sec = 10;
        timer10s.it_value.tv_usec = 0;

        statusTimer10s = setitimer(ITIMER_VIRTUAL, &timer10s, 0);
        if (statusTimer10s == -1)
            perror("Error while setting a 10s interval timer!");
    }
    else if ((int)(*argv[1] - 48) == 2)
    {
        // Setting a interval timer for 10ms
        timer10ms.it_interval.tv_sec = 0;
        timer10ms.it_interval.tv_usec = 10000;
        timer10ms.it_value.tv_sec = 0;
        timer10ms.it_value.tv_usec = 10000;

        statusTimer10ms = setitimer(ITIMER_VIRTUAL, &timer10ms, 0);
        if (statusTimer10ms == -1)
            perror("Error while setting a 10ms interval timer!");
    }

    // Catch the SIGALRM signal
    signalStatus = signal(SIGVTALRM, (void *)sampleFunction);
    if (signalStatus == SIG_ERR)
        perror("Error while catching signal!");
    else
    {
        while(1);
    }
}