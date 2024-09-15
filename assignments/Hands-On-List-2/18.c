// Question : Write a program to find out total number of directories on the `pwd`. Execute `ls -l | grep ^d | wc`. Use only `dup2`.

#include <unistd.h>    // Import for `pipe`, `dup2`, `fork`, `exec`
#include <sys/types.h> // Import for `fork`
#include <stdio.h>     // Import for `perror`

void main()
{
    int pipeCmdOneToTwo[2], pipeCmdTwoToThree[2]; // fd[0] -> read, fd[1] -> write
    int pipeOneStatus, pipeTwoStatus;

    pid_t childOne, childTwo;

    pipeOneStatus = pipe(pipeCmdOneToTwo);
    pipeTwoStatus = pipe(pipeCmdTwoToThree);

    if (pipeOneStatus == -1 || pipeTwoStatus)
        perror("Error while creating the pipe!");
    else
    {
        childOne = fork();

        if (childOne == -1)
            perror("Error while creating first child!");
        else if (childOne == 0)
        {
            // Child One will enter this branch
            close(pipeCmdTwoToThree[1]); // Close the write end of the pipe
            close(pipeCmdOneToTwo[0]);
            close(pipeCmdOneToTwo[1]);

            close(STDIN_FILENO);
            dup2(pipeCmdTwoToThree[0], STDIN_FILENO);

            execl("/usr/bin/wc", "wc", NULL);
        }
        else
        {
            // Parent will enter this branch
            childTwo = fork();

            if (childTwo == -1)
                perror("Error while creating second child!");
            else if (childTwo == 0)
            {
                // Child Two will enter this branch

                close(pipeCmdOneToTwo[1]); // Close the write end of the pipe
                close(pipeCmdTwoToThree[0]);

                close(STDIN_FILENO);
                dup2(pipeCmdOneToTwo[0], STDIN_FILENO);
                close(STDOUT_FILENO);
                dup2(pipeCmdTwoToThree[1], STDOUT_FILENO);

                execl("/usr/bin/grep", "grep ^d", "^d", NULL);
            }
            else
            {
                // Parent will enter this branch

                // Parent will execute the `ls -l` command
                close(pipeCmdOneToTwo[0]); // Close the read end of the pipe
                close(pipeCmdTwoToThree[1]);
                close(pipeCmdTwoToThree[0]);

                close(STDOUT_FILENO); // Close the file descriptor to the standard output
                dup2(pipeCmdOneToTwo[1], STDOUT_FILENO); // Reassign standard output to pipe output

                execl("/usr/bin/ls", "ls -l", "-l", NULL);
            }
        }
    }
}