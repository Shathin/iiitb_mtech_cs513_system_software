// Question : Write a program to create a Zombie state of the running program.

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
        printf("Putting parent to sleep!\n");
        sleep(100); // Put the creator process to sleep for 5s
        printf("Parent is now awake!\n");
    } else {
        // Only child process can enter this branch
        printf("Child PID: %d\n", getpid());
        printf("Exiting child!\n");
        exit(0); // Terminate the child process
        // The above exit causes the child to exit while the parent is asleep, hence won't be able to send the exit signal to the parent & ends up becoming a zombie
    }
}