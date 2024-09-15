/* Question : 8. Write a program to execute an executable program. 
    1. Use some executable program 
    2. Pass some input to an executable program. (for example execute an executable of `$./a.out name`) */

#include <unistd.h> // Import for `execl` library function

void main()
{
    char *executable_path = "./.out-files/14.out";
    char *arg = "14.c";

    execl(executable_path, executable_path, arg, NULL);
}