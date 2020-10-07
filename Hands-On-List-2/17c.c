// Question : Write a program to execute `ls -l | wc`. Use `dup`

#include <unistd.h>    // Import for `pipe``, `fork`, `execl` & `fcntl`
#include <sys/types.h> // Import `fork`
#include <fcntl.h>     // Import for `fcntl`
#include <stdio.h>     // Import for `perror` 

void main()
{
    // File descriptor used for pipe operations
    int pipefd[2];  // pipefd[0] -> read, pipefd[1] -> write
    int pipeStatus; // // Variable used to determine success of `pipe` call
    pid_t childPid;

    pipeStatus = pipe(pipefd);

    if (pipeStatus == -1)
        perror("Error while creating the file!");
    else
    {
        childPid = fork();

        if (childPid == -1)
            perror("Error while forking child!");
        else if (childPid == 0)
        {
            // Child will enter this branch
            close(STDIN_FILENO);
            fcntl(pipefd[0], F_DUPFD, STDIN_FILENO); // STDIN will be reassigned to pipefdp[0]
            close(pipefd[1]);
            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            // Parent will enter this branch
            close(STDOUT_FILENO);
            fcntl(pipefd[1], F_DUPFD, STDOUT_FILENO); // STDOUT will be reassigned to pipefd[1]
            close(pipefd[0]);
            execl("/usr/bin/ls", "ls -l", "-l", NULL);
        }
    }
}