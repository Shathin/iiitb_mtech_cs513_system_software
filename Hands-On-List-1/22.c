// Question : Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file

#include <unistd.h>    // Import for `fork` system call
#include <sys/types.h> // Import for `open`, `fork` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open` system call

void main()
{
    char *filename = "./sample-files/pgm-22-sample.txt";
    int childPid, fileDescriptor;
    fileDescriptor = open(filename, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

    if ((childPid = fork()) != 0) // Only parent can enter this branch
        write(fileDescriptor, "Parent\n!", 7);
    else // Only child can enter this branch
        write(fileDescriptor, "Child\n!", 6);
    close(fileDescriptor);
}
