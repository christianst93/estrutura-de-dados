#include <stdio.h>
#include <stdlib.h>

int main () {

    int a = 15;
    int *pa;

    pa = &a;
    *pa = 50;

    printf("Valor de a = %d\n", a);

}