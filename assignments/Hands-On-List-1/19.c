// Question : Write a program to find out time taken to execute getpid system call. Use time stamp counter.

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

    start = __rdtsc();
    pid = getpid();
    end = __rdtsc();

    printf("PID: %d\n", pid);
    printf("Time taken : %d \n", (end - start));
}