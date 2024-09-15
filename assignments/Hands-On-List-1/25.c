// Question : Write a program to create three child processes. The parent should wait for a particular child (use `waitpid` system call).

#include <unistd.h>    // Import for `fork`
#include <sys/types.h> // Import for `fork`, `waitpid`
#include <sys/wait.h>  // Import for `waitpid`
#include <stdio.h>     // Import for `printf`

void main()
{
    pid_t childA, childB, childC, terminatedChild;
    int waitStatus;

    if ((childA = fork()) == 0)
    {
        // Child A will enter this branch
        printf("Child A created...\n");
        printf("Putting child A to sleep for 5 sec\n");
        sleep(5);
        printf("Child A is now awake!\n");
        _exit(0);
    }
    else
    {
        // Parent will enter this branch
        if ((childB = fork()) == 0)
        {
            // Child B will enter this branch
            printf("Child B created...\n");
            printf("Putting child B to sleep for 10 sec\n");
            sleep(10);
            printf("Child B is now awake!\n");
            _exit(0);
        }
        else
        {
            // Parent will enter this branch

            if ((childC = fork()) == 0)
            {
                // Child C will enter this branch
                printf("Child C created...\n");
                printf("Putting child C to sleep for 15 sec\n");
                sleep(15);
                printf("Child C is now awake!\n");
                _exit(0);
            }
            else
            {
                // Parent will enter this branch
                terminatedChild = waitpid(childC, &waitStatus, 0);

                if (terminatedChild == childC)
                {
                    if (waitStatus == 0)
                        printf("Child C has terminated with exit status = 0\n");
                    else
                        printf("Child has exited with exit status : %d\n", waitStatus);
                }
            }
        }
    }
}
