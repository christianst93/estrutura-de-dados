#include <stdio.h>
#include <stdlib.h>

int main () {

    int a, b;
    int *ps;

    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);

    ps = (int*) malloc(sizeof(int));

    *ps = a + b;

    printf("Soma = %d\n", *ps);
    printf("Endereco armazenado em ps %p | endereco de ps = %p", ps, &ps);
    printf("Endereco de a = %p |Endereco de b = %p\n", &a, &b);
}