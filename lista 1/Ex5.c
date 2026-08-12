#include <stdio.h>
#include <stdlib.h>

int main () {

    int num1, num2,soma, produto;
    int *p1, *p2;

    printf("Digite o valor de num1\n");
    scanf("%d", &num1);
    printf("Digite o valor de num2\n");
    scanf("%d", &num2);

    p1 = &num1;
    p2 = &num2;

    soma = *p1 + *p2;
    produto = (*p1 * *p1) - (*p2 * *p2);
    printf("Valor da soma = %d\n", soma);
    printf("Valor da diferença do produto = %d\n", produto);
}