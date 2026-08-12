#include <stdio.h>
#include <stdlib.h>

void somaAB(int a, int b, int *pab) {
    *pab = a + b;
}

int main () {
    
    int a, b;
    int *pab;

    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);

    pab = (int*) malloc(sizeof(int));
    somaAB(a, b, pab);
    printf("Valor da soma = %d\n", *pab);
    
    free(pab);

    return 0;
}