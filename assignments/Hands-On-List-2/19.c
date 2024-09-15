// Question: Create a FIFO file by `mkfifo` library function and `mknod` system call

#include <sys/types.h> // Import for `mkfifo` library function & `mknod` system call
#include <sys/stat.h>  // Import for `mkfifo` library function & `mknod` system call
#include <fcntl.h>     // Import for `mknod` system call
#include <unistd.h>    // Import for `mknod` system call
#include <stdio.h>     // Import for using `printf` & `perror` function

void main()
{
    char *mkfifoName = "./mymkfifo";    // File name of FIFO file created using `mkfifo`
    char *mknodName = "./mymknod-fifo"; // File name of FIFO file created using `mknod`

    int mkfifo_status, mknod_status; // 0 -> Success, -1 -> Error

    // Using `mkfifo` library function
    mkfifo_status = mkfifo(mkfifoName, S_IRWXU);

    if (mkfifo_status == -1)
        perror("Error while creating FIFO file!");
    else
        printf("Succesfully created FIFO file. Check using `ll` or `ls -l` command!\n");

    // Using `mknod` system call
    mkfifo_status = mknod(mknodName, __S_IFIFO | S_IRWXU, 0);

    if (mknod_status == -1)
        perror("Error while creating FIFO file!");
    else
        printf("Succesfully created FIFO file. Check using `ll` or `ls -l` command!\n");
}