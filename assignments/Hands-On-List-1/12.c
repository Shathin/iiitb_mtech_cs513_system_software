// Question: Write a program to find out the opening mode of a file. Use `fcntl`

#include <sys/types.h> // Import for `open` system call
#include <sys/stat.h>  // Import for `open` system call
#include <fcntl.h>     // Import for `open`, `fcntl` system call
#include <unistd.h>    // Import for `fcntl` system call
#include <stdio.h>     // Import required for `perror` & `printf` function

void main(int argc, char *argv[])
{
    char *filename;     // File name of the source file
    int fileDescriptor; // File descriptor of the source file
    int status;         // Holds the result of the fcntl call. -1 -> Error

    if (argc != 2)
        printf("Pass the file to be opened as the argument!\n");
    else
    {
        filename = argv[1];

        fileDescriptor = open(filename, O_RDONLY);

        if (fileDescriptor == -1)
            perror("Error while opening the file");
        else
        {
            status = fcntl(fileDescriptor, F_GETFL);

            if (status == -1)
                perror("Error on executing fcntl!");
            else
            {
                /*
                    0    = O_RDONLY
                    1    = O_WRONLY
                    2    = O_RDWR
                    64   = O_CREAT
                    512  = O_TRUNC
                    1024 = O_APPEND
                    577  = O_WRONLY | O_CREAT | O_TRUNC
                    1089 = O_WRONLY | O_CREAT | O_APPEND
                    578  = O_RDWR   | O_CREAT | O_TRUNC
                    1090 = O_RDWR   | O_CREAT | O_APPEND
                */
                switch (O_ACCMODE & status)
                {
                case 0:
                    printf("The file has been opened with the flags : O_RDONLY\n");
                    break;
                case 1:
                    printf("The file has been opened with the flags : O_WRONLY\n");
                    break;
                case 2:
                    printf("The file has been opened with the flags : O_RDWR\n");
                    break;
                // Any of the below cases will never be invoked
                case 64:
                    printf("The file has been opened with the flags : O_CREAT\n");
                    break;
                case 512:
                    printf("The file has been opened with the flags : O_TRUNC\n");
                    break;
                case 1024:
                    printf("The file has been opened with the flags : O_APPEND\n");
                    break;
                case 577:
                    printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_TRUNC\n");
                    break;
                case 1089:
                    printf("The file has been opened with the flags : O_WRONLY | O_CREAT | O_APPEND\n");
                    break;
                case 578:
                    printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_TRUNC\n");
                    break;
                case 1090:
                    printf("The file has been opened with the flags : O_RDWR   | O_CREAT | O_APPEND\n");
                    break;
                default:
                    printf("Error!");
                }
            }
            close(fileDescriptor);
        }
    }
}