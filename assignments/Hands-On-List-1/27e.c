/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    5. `execvp`
*/

#include <unistd.h> // Import for `execvp` function
#include <stdio.h>  // Import for `printf` function

void main()
{
    // Command name, options, file name,
    char *args[] = {"/bin/ls", "-Rl", "./sample-files", NULL}; // Set the last but one argument if you want to execute `ls` command on a particular file

    printf("============OUTPUT USING execvp===============\n");
    execvp(args[0], args);
    printf("\n");
}