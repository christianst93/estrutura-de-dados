#include <stdio.h>
#include <stdlib.h>

int main () {

    int x;
    float y;
    char z;

    x = 10;
    y = 2.50;
    z = 'A';

    printf("Valor de x = %d | Endereco de x = %p\n", x, &x);
    printf("Valor de y = %.2f | Endereco de y = %p\n", y, &y);
    printf("Valor de z = %c | Endereco de z = %p\n", z, &z);


}