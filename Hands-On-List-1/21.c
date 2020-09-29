// Question : Write a program, call fork and print the parent and child process id.

// Imports for `fork` & `getpid` system call
#include <sys/types.h>
#include <unistd.h>
// Import for printf function
#include<stdio.h>

void main() {
    int child_pid, pid;
    
    pid = getpid();
    
    printf("Parent PID: %d\n", pid);
    
    child_pid = fork();
    
    if(child_pid != 0)
        printf("Child PID: %d\n", child_pid);
}
