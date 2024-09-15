// Question: Create a soft link file using the `symlink` system call

#include <unistd.h> // Import for `symlink` & `write` system calls
#include <stdio.h>  // Import for `perror` & `printf` functions

// argv[1] -> File path
// argv[2] -> Soft Link File path
void main(int argc, char *argv[])
{

    char *filepath;     // File name of the source file
    char *softLinkPath; // File name of the symbolic link file

    int status; // 0 -> Success, -1 -> Error

    if (argc != 3)
        printf("Enter File path and Symbolic Link File path as the arguments to the program\n");
    else
    {
        filepath = argv[1];
        softLinkPath = argv[2];

        status = symlink(filepath, softLinkPath);

        if (status == -1)
            perror("Error while creating hard link!");
        else
            printf("Successfully created a hard link. Check with the `ll` or `ls -l` command.\n");
    }
}