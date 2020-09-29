/*
Question:  Write a program to execute `ls -Rl` by the following system calls 
    1. `execl` 
*/

// Import for `exec` family of functions
#include<unistd.h>
// Import for `printf` function
#include<stdio.h>

void main() {
    char *command_path = "/bin/ls";
    char *options = "-Rl";
    char *file_arg = "./sample-files"; // Set if you want to execute `ls` command on a particular file
    
    printf("============OUTPUT USING execl===============\n");
    execl(command_path, command_path, options, file_arg, NULL);
    printf("\n");
}