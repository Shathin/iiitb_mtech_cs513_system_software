// Question : Find out the priority of your running program. Modify the priority with nice command.

#include <unistd.h> // Import for `nice` system call
#include <stdio.h>  // Import for `printf` function
#include <stdlib.h> // `atoi` conversion from string to int

void main(int argc, char *argv[])
{
    int priority, newp;
    if (argc != 2)
        printf("Please pass the integer value to be added to the current nice value\n");
    else
    {
        newp = atoi(argv[1]);
        priority = nice(0); // Get the priorty by adding 0 to current priorty
        printf("Current priority: %d\n", priority);
        priority = nice(newp); // Adds `newp` to the current priority
        printf("New priority: %d\n", priority);
    }
}