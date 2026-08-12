#include <stdio.h>
#include <stdlib.h>

int main () {
    int n;

    printf("Digite o numero de posicoes do vetor:");
    scanf("%d", &n);

    int *vet = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor do vetor na posicao[%d]\n", i);
        scanf("%d", &vet[i]);
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("Valor na posicao [%d] = %d\n", i, vet[i]);
    }
    
    free(vet);
}