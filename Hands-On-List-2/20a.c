// Question : Write two programs so that both can communicate by FIFO - Use one way communication.

#include <sys/types.h> // Import for `mkfifo` & `open`
#include <sys/stat.h>  // Import for `mkfifo` & `open`
#include <fcntl.h>     // Import for `open`
#include <unistd.h>    // Import for `write`
#include <stdio.h>     // Import for `perror`

void main()
{
    int fifoStatus;                              // Used to determine success of `mkfifo` call
    char data[] = "Sending data at warp speed!"; // Data to be sent through the buffer
    int fileDescriptor;                          // File descriptor of the FIFO file
    char *fifoFile = "./20-fifo";                // Path name of the FIFO file
    int writeBytes;                              // Number of bytes written to the FIFO file

    fifoStatus = mkfifo(fifoFile, S_IRWXU);

    if (fifoStatus == -1)
        perror("Error while creating FIFO file!");
    else
    {
        fileDescriptor = open(fifoFile, O_WRONLY);
        if (fileDescriptor == -1)
            perror("Error while opening FIFO file for writing");
        else
        {
            writeBytes = write(fileDescriptor, &data, sizeof(data));
            if (writeBytes == -1)
                perror("Error while writing to the file!");
            close(fileDescriptor);
        }
    }
}