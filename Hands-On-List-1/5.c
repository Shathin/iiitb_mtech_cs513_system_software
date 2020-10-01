// Question : Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.

#include <sys/types.h> // Import for `creat` system call
#include <sys/stat.h>  // Import for `creat` system call
#include <fcntl.h>     // Import for `creat` system call

void main()
{
    while (1)
    {
        creat("./sample-files/file_1", O_CREAT);
        creat("./sample-files/file_2", O_CREAT);
        creat("./sample-files/file_3", O_CREAT);
        creat("./sample-files/file_4", O_CREAT);
        creat("./sample-files/file_5", O_CREAT);
    }
}
