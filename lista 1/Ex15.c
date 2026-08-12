#include <stdio.h>
#include <stdlib.h>

void operacoes(int a, int b, int *soma, int * diff, int *prod) {
    *soma = a + b;
    *diff = a - b;
    *prod = a * b;
}

int main () {

    int a, b, *soma, *diff, *prod;

    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);

    soma = (int*) malloc(sizeof(int));
    diff = (int*) malloc(sizeof(int));
    prod = (int*) malloc(sizeof(int));

    operacoes(a, b, soma, diff, prod);
    printf("Soma = %d | Diferenca = %d | Produto = %d\n", *soma, *diff, *prod);

    free(soma);
    free(diff);
    free(prod);

    return 0;
}