// Question : Write a program to create an orphan process.

#include <sys/types.h> // Import for `fork` system call
#include <unistd.h>    // Import for `fork` system call
#include <stdio.h>     // Import for `printf` function

void main()
{
    pid_t childPid;

    if ((childPid = fork()) != 0)
    {
        // Only creator process can enter this branch
        printf("Parent PID: %d\n", getpid());
        printf("Putting Parent to sleep for 10s\n");
        sleep(10); // Put the process process to sleep for 10s
        printf("Exiting parent!\n");
        _exit(0); // Terminate the parent process
        // The above exit causes the parent to exit while the child is asleep
    }
    else
    {
        // Only child process can enter this branch
        printf("Child PID: %d\n", getpid());
        printf("Putting child to sleep for 100s!\n");
        sleep(100); // Put the child process to sleep for 12s
        printf("Child is now awake!\n");
    }
}