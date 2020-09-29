// Question: Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls

// Import for `read` & `write` system call
#include<unistd.h>
// Import for `perror` function
#include<stdio.h>

void main() {
    char *buffer[100];
    int readByteCount, writeByteCount;
    while(1) {
        readByteCount = read(STDIN_FILENO, buffer, 1);
        writeByteCount = write(STDOUT_FILENO, buffer, 1);
    
        if(readByteCount == -1 || writeByteCount == -1) {
            perror("Error while reading from STDIN / writing to STDOUT");
            break;
        }
    }
}
