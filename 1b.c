// Question: Create a hard link file using the `link` system call

// Import required for using `link` & `write` system call
#include <unistd.h>
// Import required for using `perror`
#include <stdio.h>

// argv[1] -> File path
// argv[2] -> Hard Link File path
void main(int argc, char *argv[])
{

    char *filePath; // File name of the source file
    char *hardlinkPath; // File name of the hardlink file file

    int status; // 0 -> Success, -1 -> Error

    if (argc != 3)
        printf("Enter File path and Hardlink File path as the arguments to the program\n");
    else
    {
        filePath = argv[1];
        hardlinkPath = argv[2];

        status = link(filePath, hardlinkPath);

        if (status == -1)
            perror("Error while creating hard link!");
        else
            printf("Successfully created a hard link. Check with the `ll` or `ls -l` command.\n");
    }
}