// Question : Write a program to create an orphan process.

// Imports for `fork` system call
#include<sys/types.h>
#include<unistd.h>
// Import for `exit` function
#include<stdlib.h>
// Import for `printf` function
#include<stdio.h>

void main() {
    pid_t cpid;

    cpid = fork();

    if(cpid != 0) {
        // Only creator process can enter this branch
        printf("Parent PID: %d\n", getpid());
        printf("Putting Parent to sleep for 10s\n");
        sleep(10); // Put the process process to sleep for 7s
        printf("Exiting parent!\n");
        exit(0); // Terminate the parent process
        // The above exit causes the parent to exit while the child is asleep
    } else {
        // Only child process can enter this branch
        printf("Child PID: %d\n", getpid());
        printf("Putting child to sleep for 100s!\n");
        sleep(100); // Put the child process to sleep for 12s
        printf("Child is now awake!\n");
    }
}