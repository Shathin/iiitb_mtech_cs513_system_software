/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    4. `execv` 
*/

#include <unistd.h> // Import for `execv` function
#include <stdio.h>  // Import for `printf` function

void main()
{
    char *args[] = {"/bin/ls", "-Rl", "./sample-files", NULL}; // Set the last but one element if you want to execute `ls` command on a particular file

    printf("============OUTPUT USING execv===============\n");
    execv(args[0], args);
    printf("\n");
}