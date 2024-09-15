// Question : Write a program, call fork and print the parent and child process id.

#include <sys/types.h> // Import for `fork` & `getpid` system call
#include <unistd.h>    // Import for `fork` & `getpid` system call
#include <stdio.h>     // Import for printf function

void main()
{
    int childPid, pid;

    pid = getpid();

    printf("Parent PID: %d\n", pid);

    childPid = fork();

    if (childPid != 0)
        // Only parent will enter this branch
        printf("Child PID: %d\n", childPid);
}
