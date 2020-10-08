// Question : Write a program to measure how much time is taken to execute 100 `getppid()` system call. Use time stamp counter.

#include <sys/time.h>  // Import for `gettimeofday` system call
#include <sys/types.h> // Import for `getpid` system call
#include <unistd.h>    // Import for `getpid` system call
#include <stdio.h>     // Import for printf

// Import for __rdtsc()
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

void main()
{
    int start, end, pid;
    struct timeval timestamp;
    int iter = 0;

    start = __rdtsc();
    while(iter < 100) {
        pid = getpid();
        iter++;
    }
    end = __rdtsc();

    printf("PID: %d\n", pid);
    printf("Time taken : %d ns \n",  (int) ((end - start)/2.4));
}