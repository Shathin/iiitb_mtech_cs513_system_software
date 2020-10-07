// Question : Write two programs so that both can communicate by FIFO - Use two way communications.

#include <sys/types.h> // Import for `mkfifo`
#include <sys/stat.h>  // Import for `mkfifo`
#include <stdio.h>     // Import for `perror`

#include "./21-global.h" // Import for FIFO file name

void main()
{
    int fifoOneStatus, fifoTwoStatus; // Determines the success of the `mkfifo` call

    fifoOneStatus = mkfifo(fifoOneName, S_IRWXU);
    if (fifoOneStatus == -1)
        perror("Error while creating FIFO file fifoOne");

    fifoTwoStatus = mkfifo(fifoTwoName, S_IRWXU);
    if (fifoTwoStatus == -1)
        perror("Error while creating FIFO file fifoTwo");
}
