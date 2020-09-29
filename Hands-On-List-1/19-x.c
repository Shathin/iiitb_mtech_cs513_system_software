// Question : Write a program to find out time taken to execute getpid system call. Use time stamp counter.

// Import for `gettimeofday` system call
#include<sys/time.h>
// Import for `getpid` system call
#include<sys/types.h>
#include<unistd.h>
// Import for printf
#include<stdio.h>

void main() {
    int start, end, pid;
    struct timeval timestamp;
    
    gettimeofday(&timestamp, NULL);
    start = timestamp.tv_usec;
    pid = getpid();
    gettimeofday(&timestamp, NULL);
    end = timestamp.tv_usec;

    printf("PID: %d\n", pid);
    printf("Time taken : %d ms\n", (end-start));
}