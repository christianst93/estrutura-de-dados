#include <stdio.h>
#include <stdlib.h>

void imprimeVetorPonteiro(int *p, int n) {
    for(int i = 0; i < n; i++)
    {
        printf("Valor na posicao [%d]: %d\n", i, *(p +i));
    }
    
}

int main () {

    int n;   

    printf("Digite o tamanho do vetor:");
    scanf("%d", &n);

    int *vet = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor do vetor na posicao[%d]: ", i);
        scanf("%d", &vet[i]);
    }
    
    imprimeVetorPonteiro(vet, n);

    free(vet);

    return 0;
}