// Question : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.

// Imports for `creat` system call
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void main() {
    while(1) {
        creat("./sample-output/file_1", O_CREAT);
        creat("./sample-output/file_2", O_CREAT);
        creat("./sample-output/file_3", O_CREAT);
        creat("./sample-output/file_4", O_CREAT);
        creat("./sample-output/file_5", O_CREAT);
    }
}

