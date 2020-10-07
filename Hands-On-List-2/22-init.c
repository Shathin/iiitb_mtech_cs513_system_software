// Question : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.

#include<sys/types.h> // Import for `mkfifo`
#include<sys/stat.h> // Import for `mkfifo`
#include<stdio.h> // Import for `perror`

#include "./22-global.h" // Import for FIFO file name

void main() {
    int fifoStatus;

    fifoStatus = mkfifo(fifoName, S_IRWXU);

    if(fifoStatus == -1)
        perror("Error creating the FIFO file \n");
}