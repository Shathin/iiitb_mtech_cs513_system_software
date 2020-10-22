#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main() {
    char s[10] = "Shathin-1";
    char *tokens = strtok(s, "-");
    printf("%s\n", tokens);
    tokens = strtok(NULL, "-");
    printf("%s\n", tokens);
}