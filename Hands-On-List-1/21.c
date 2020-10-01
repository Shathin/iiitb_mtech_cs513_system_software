// Question : Write a program, call fork and print the parent and child process id.

// Imports for `fork` & `getpid` system call
#include <sys/types.h>
#include <unistd.h>
// Import for printf function
#include<stdio.h>

void main() {
    int childPid, pid;
    
    pid = getpid();
    
    printf("Parent PID: %d\n", pid);
    
    childPid = fork();
    
    if(childPid != 0)
        // Only parent will enter this branch
        printf("Child PID: %d\n", childPid);
}
