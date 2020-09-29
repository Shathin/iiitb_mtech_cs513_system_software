// Question : Find out the priority of your running program. Modify the priority with nice command.

// Import for `nice` system call
#include<unistd.h>
// // Import for `getpriority` system call
// #include<sys/time.h>
// #include<sys/resource.h>
// Import for `printf` function
#include<stdio.h>

void main() {
    int priority;
    
    priority = nice(0); // Get the priorty by adding 0 to current priorty

    printf("Current priority: %d\n", priority);

    priority = nice(-2); // Adds 1 to the current priority

    printf("New priority: %d\n", priority);

}