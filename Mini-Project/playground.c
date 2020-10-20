#include <stdio.h>

struct A {
    int a;
};

struct A someFunction() {
    return;
}

int main()
{
    struct A a = someFunction();
    printf("Val : %d\n", a.a);
    return 0;
}