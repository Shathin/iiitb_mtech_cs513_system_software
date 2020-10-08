// Question : Write a program to set (any one) system resource limit. Use `setrlimit` system call.

#include <sys/time.h>     // Import for `getrlimit` & `setrlimit`
#include <sys/resource.h> // Import for `getrlimit` & `setrlimit`
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

    // RLIMIT_CORE -> Max size of a core file
    status = getrlimit(RLIMIT_CORE, &resourceLimits);
    if (status == -1)
        perror("Error while getting RLIMIT_CORE!");
    else
        print("Max size of a core file", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");

    // New soft limit
    resourceLimits.rlim_cur = 4096; // bytes

    status = setrlimit(RLIMIT_CORE, &resourceLimits);
    if (status == -1)
        perror("Error while setting RLIMIT_CORE!");
    else
    {
        status = getrlimit(RLIMIT_CORE, &resourceLimits);
        if (status == -1)
            perror("Error while getting RLIMIT_CORE!");
        else
            print("Max size of a core file", resourceLimits.rlim_cur, resourceLimits.rlim_max, "bytes");
    }
}