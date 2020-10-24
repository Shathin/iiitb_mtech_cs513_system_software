#include<stdio.h>
#include<unistd.h>

void main() {
    printf("%s", getpass("Enter the password!"));
}