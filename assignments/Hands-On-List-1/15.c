// Question : Write a program to display the environmental variable of the user (use environ).

#include <stdio.h> // Import for `NULL`, `environ`

extern char **environ;

int isUser(char *var)
{
    return var[0] == 'U' && var[1] == 'S' && var[4] == '=';
}

void main()
{
    int iter = -1;
    while (environ[++iter] != NULL)
        if (isUser(environ[iter]))
            printf("%s\n", environ[iter]);
}
