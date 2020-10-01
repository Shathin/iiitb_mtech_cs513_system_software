/* Question : Write a program to print the following information about a given file - 
    1. Inode 
    2. Number of hard links 
    3. UID 
    4. GID 
    5. Size 
    6. Block size 
    7. Number of blocks 
    8. Time of last access 
    9. Time of last modification 
    10. Time of last change
*/

#include <sys/types.h> // Import for using `stat` system call
#include <sys/stat.h>  // Import for using `stat` system call
#include <unistd.h>    // Import for using `stat` system call
#include <stdio.h>     // Import for `printf` & `perror` function
#include <time.h>      // Import for changing epoch timestamp to a more readable format

void main(int argc, char *argv[])
{
    char *filename;
    int status;

    struct stat statbuf;
    if (argc != 2)
        printf("Pass the file name as the argument!\n");
    else
    {
        filename = argv[1];
        status = stat(filename, &statbuf);

        if (status == -1)
            perror("Error while executing the file!");
        else
        {
            printf("Inode -> %ld\n", statbuf.st_ino);
            printf("Number of hardlinks -> %ld\n", statbuf.st_nlink);
            printf("UID -> %d\n", statbuf.st_uid);
            printf("GID -> %d\n", statbuf.st_gid);
            printf("Size -> %ld\n", statbuf.st_size);
            printf("Block Size -> %ld\n", statbuf.st_blksize);
            printf("Number of Blocks -> %ld\n", statbuf.st_blocks);
            // Use the `ctime` function in `time.h` header to convert the timestamp in epoch to a more human readable form
            printf("Time of last access -> %s", ctime(&statbuf.st_atim.tv_sec));
            printf("Time of last modification -> %s", ctime(&statbuf.st_mtim.tv_sec));
            printf("Time of last change -> %s", ctime(&statbuf.st_ctim.tv_sec));
        }
    }
}