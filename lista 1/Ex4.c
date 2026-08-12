#include <stdio.h>
#include <stdlib.h>

int main () {

    int a;
    int b;

    if (&a > &b)
    {
        printf("Endereco de a = %p\n", &a);
    } else {
        printf("Endereco de b = %p\n", &b);
    }    

}