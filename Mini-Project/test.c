#include <stdio.h>
#include <time.h>
#include <string.h>

void printArray(int *ptrToArray)
{
    int iter;
    for (iter = 0; iter < 10; iter++)
    {
        printf("%d\t", ptrToArray[iter]);
    }
    printf("\n");
}

void changeToNewArray(int *ptrToArray)
{
    int newArray[10];

    int iter = 0;
    for (iter = 1; iter < 10; iter++)
    {
        ptrToArray[iter - 1] = ptrToArray[iter];
    }
    ptrToArray[iter - 1] = ptrToArray[iter - 2] + 1;
}

void main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printArray(array);
    changeToNewArray(array);
    printArray(array);
}