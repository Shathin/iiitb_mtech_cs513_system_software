// Question : Write a program to print the system resource limits. Use `getrlimit` system call.

#include <sys/time.h>     // Import for `getrlimit`
#include <sys/resource.h> // Import for `getrlimit`
#include <stdio.h>        // Import for `printf` & `perror`

void print(char *text, rlim_t soft, rlim_t hard, char *unit)
{
    printf("%s - \n", text);

    printf("\tSoft Limit: ");
    if (soft == RLIM_INFINITY)
        printf("Infinite\n");
    else
        printf("%ld %s\n", soft, unit);

    printf("\tHard Limit: ");
    if (hard == RLIM_INFINITY)
        printf("Infinite\n");
    else
        printf("%ld %s\n", hard, unit);

    printf("====================\n");
}

void main()
{
    int status;                   // Determines the success of the `getrlimit` call
    struct rlimit resourceLimits; // Holds the hard & soft limits for a resource


    // RLIMIT_AS -> This  is  the maximum size of the process's virtual memory (address space).
    status = getrlimit(RLIMIT_AS, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_AS!");
    else
        print("Max size of process's virtual memory", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_CORE -> Max size of a core file
    status = getrlimit(RLIMIT_CORE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_CORE!");
    else
        print("Max size of a core file", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_CPU -> Amount of CPU time that the process can consume
    status = getrlimit(RLIMIT_CPU, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_CPU!");
    else
        print("Max CPU time that the process can consume", resourceLimits.rlim_cur, resourceLimits.rlim_max, "seconds");

    // RLIMIT_DATA -> Maximum size of the process's data segment
    status = getrlimit(RLIMIT_DATA, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_DATA!");
    else
        print("Max size of process's data segement", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_FSIZE -> Maximum size of files that  the  process  may  create
    status = getrlimit(RLIMIT_FSIZE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_FSIZE!");
    else
        print("Max size of files that  the  process  may  create", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_LOCKS -> Maximum number of locks that a process may establish
    status = getrlimit(RLIMIT_LOCKS, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_LOCKS!");
    else
        print("Max number of locks that a process may establish", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_MEMLOCK -> Maximum number of bytes of memory that may be locked into RAM
    status = getrlimit(RLIMIT_MEMLOCK, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_MEMLOCK!");
    else
        print("Max number of bytes of memory that may be locked into RAM", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_MSGQUEUE -> Maximum number of bytes that can be allocated for POSIX message queues
    status = getrlimit(RLIMIT_MSGQUEUE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_MSGQUEUE!");
    else
        print("Max number of bytes of that can be allocated for POSIX message queues", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_NICE -> Ceiling of the process's nice value
    status = getrlimit(RLIMIT_NICE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_NICE!");
    else
        print("Ceiling of the process's nice value", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_NOFILE -> specifies a value one greater than the maximum file descriptor number that can be opened by this process
    status = getrlimit(RLIMIT_NOFILE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_NOFILE!");
    else
        print("Max file descriptor", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_NPROC -> Limit on the number of threads
    status = getrlimit(RLIMIT_NPROC, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_NPROC!");
    else
        print("Limit on the number of threads", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_RSS -> Limit on the number of virtual pages resident in the RAM
    status = getrlimit(RLIMIT_RSS, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_RSS!");
    else
        print("Limit on the  number of virtual pages resident in the RAM", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // RLIMIT_RTPRIO -> a ceiling on the real-time priority
    status = getrlimit(RLIMIT_RTPRIO, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_RTPRIO!");
    else
        print("Ceiling on the real-time priority", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_RTTIME -> Amount of CPU time that a  process scheduled  under a real-time scheduling policy may consume without making a blocking system call.
    status = getrlimit(RLIMIT_RTTIME, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_RTTIME!");
    else
        print("Amount of CPU time that a  process scheduled  under a real-time scheduling policy", resourceLimits.rlim_cur, resourceLimits.rlim_max, "ms");

    // RLIMIT_SIGPENDING ->The number of signals that may be queued
    status = getrlimit(RLIMIT_SIGPENDING, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_SIGPENDING!");
    else
        print("The number of signals that may be queued", resourceLimits.rlim_cur, resourceLimits.rlim_max, "");

    // RLIMIT_STACK -> Maximum  size of the process stack
    status = getrlimit(RLIMIT_SIGPENDING, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_STACK!");
    else
        print("Maximum  size of the process stack", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");
}