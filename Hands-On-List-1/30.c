// Question : Write a program to run a script at a specific time using a Daemon process.

#include <time.h>      // Import for time related stuff
#include <stdio.h>     // Import for `printf`
#include <stdlib.h>    // Import for `itoa`
#include <sys/types.h> // Import for `fork`, `setsid`
#include <unistd.h>    // Import for `fork`, `setsid`
#include <sys/stat.h>  // Import for `umask`

// Argument to be passed as hour minute second
// hour is mandatory
void main(int argc, char *argv[])
{

    time_t currentEpoch, deadlineEpoch; // Current system time & deadline time in epoch
    struct tm *deadline;                // Deadline in user readable format

    pid_t child;

    if (argc < 2)
        printf("Pass at least one argument\n");
    else
    {
        time(&currentEpoch); // Get current time
        deadline = localtime(&currentEpoch);

        deadline->tm_hour = atoi(argv[1]);
        deadline->tm_min = argv[2] == NULL ? 0 : atoi(argv[2]);
        deadline->tm_sec = argv[3] == NULL ? 0 : atoi(argv[3]);

        deadlineEpoch = mktime(deadline); // Convert dealine to epoch

        if ((child = fork()) == 0)
        {
            // child will enter here
            setsid();
            chdir("/");
            umask(0);
            do
            {
                time(&currentEpoch);
            } while (difftime(deadlineEpoch, currentEpoch) > 0);
            printf("Boo! Got ya!\n");
            exit(0);
        }
        exit(0);
    }
}
