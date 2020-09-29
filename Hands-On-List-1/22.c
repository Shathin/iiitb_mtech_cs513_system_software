// Question : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.

// Import for `fork` system call
#include<sys/types.h>
#include<unistd.h>
// Additional imports for `open` system call
#include<sys/stat.h>
#include<fcntl.h>

void main() {
    char *file_name = "./sample-files/pgm-22-sample.txt";

    int cpid;

    int file_descriptor;

    cpid = fork();

    if(cpid != 0) {
        // Only creator process (parent) can enter this branch 
        file_descriptor = open(file_name, O_WRONLY | O_APPEND);
        write(file_descriptor, "Parent\n!", 7);
        close(file_descriptor);
    } else {
        // Child will enter this branch
        file_descriptor = open(file_name, O_WRONLY | O_APPEND);
        write(file_descriptor, "Child\n!", 6);
        close(file_descriptor);
    }
}
