#include <stdio.h>
#include <stdlib.h>

void troca(int *a, int *b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main () {
    int a, b;

    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);

    troca(&a,&b);
    printf("Valor de a = %d\n", a);
    printf("Valor de b = %d\n", b);
}