#include <stdio.h>     // Import for `printf`  & `perror`
#include <sys/types.h> // Import for `open`
#include <sys/stat.h>  // Import for `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`
#include <string.h>    // Import for string functions

#include "./db-schema/admin.h"

void main()
{
    struct admin admin[2];
    struct admin readAdmin;

    admin[0].adminID = 0;
    strcpy(admin[0].adminName, "Spooks");
    strcpy(admin[0].loginID, "Spooks-0");
    strcpy(admin[0].password, "SirSpooks");

    admin[1].adminID = 1;
    strcpy(admin[1].adminName, "Ryuu");
    strcpy(admin[1].loginID, "Ryuu-1");
    strcpy(admin[1].password, "ironmaiden");

    int fileDescriptor = open("./db/admin", O_CREAT | O_APPEND | O_RDWR | S_IRWXU);
    if (fileDescriptor == -1)
    {
        perror("Error while opening / creating file!");
        _exit(0);
    }

    ssize_t writeBytes;

    writeBytes = write(fileDescriptor, &admin[0], sizeof(struct admin));
    if (writeBytes == -1)
    {
        perror("Error while writing structure into file");
        _exit(0);
    }
    writeBytes = write(fileDescriptor, &admin[1], sizeof(struct admin));
    if (writeBytes == -1)
    {
        perror("Error while writing structure into file");
        _exit(0);
    }

    lseek(fileDescriptor, SEEK_SET, 0);

    ssize_t readBytes;
    readBytes = read(fileDescriptor, &readAdmin, sizeof(struct admin));
    if (readBytes == -1)
    {
        perror("Error while reading structure");
        _exit(0);
    }

    printf("adminID: %d\n", readAdmin.adminID);
    printf("adminName: %s\n", readAdmin.adminName);
    printf("loginID: %s\n", readAdmin.loginID);
    printf("password: %s\n", readAdmin.password);

    readBytes = read(fileDescriptor, &readAdmin, sizeof(struct admin));
    if (readBytes == -1)
    {
        perror("Error while reading structure");
        _exit(0);
    }

    printf("adminID: %d\n", readAdmin.adminID);
    printf("adminName: %s\n", readAdmin.adminName);
    printf("loginID: %s\n", readAdmin.loginID);
    printf("password: %s\n", readAdmin.password);
}