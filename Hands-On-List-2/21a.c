// Question : Write two programs so that both can communicate by FIFO - Use two way communications.

#include <sys/types.h> // Import for & `open`
#include <sys/stat.h>  // Import for & `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`
#include <stdio.h>     // Import for `perror`

void main()
{
    char *fifoOneName = "./fifoOne", *fifoTwoName = "./fifoTwo";
    int readBytes, writeBytes;
    int fifoOneFD, fifoTwoFD;
    char data[100];

    fifoOneFD = open(fifoOneName, O_WRONLY);
    if (fifoOneFD == -1)
    {
        perror("Error while opening fifoOne");
        _exit(0);
    }

    fifoTwoFD = open(fifoTwoName, O_RDONLY);
    if (fifoOneFD == -1)
    {
        perror("Error while opening fifoTwo");
        _exit(0);
    }

    writeBytes = write(fifoOneFD, "From 21a to 21b", 15);

    if (writeBytes == -1)
        perror("Error while writing to FIFO fifoOne!");
    
    close(fifoOneFD);

    readBytes = read(fifoTwoFD, &data, 100);

    if (readBytes == -1)
    {
        perror("Error while reading from FIFO fifoTwo!");
        _exit(0);
    }

    printf("Data from FIFO: %s\n", data);
    
    close(fifoTwoFD);
}