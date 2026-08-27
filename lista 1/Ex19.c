#include <stdio.h>
#include <stdlib.h>

void menorVetor(int *vet, int n, int *menor) {
    *menor = vet[0];
    for (int i = 0; i < n; i++)
    {
        if (vet[i] < *menor)
        {
            *menor = vet[i];
        }        
    }
    
}

void maiorVetor(int *vet, int n, int *maior) {
    *maior = vet[0];
    for (int i = 0; i < n; i++)
    {
        if (vet[i] > *maior)
        {
            *maior = vet[i];
        }        
    }
    
}

void menorMaiorVetor(int *vt, int n, int *menor, int *maior) {
    menorVetor(vt, n, menor);
    maiorVetor(vt, n, maior);
}

int main () {

    int n, maior, menor;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *vet = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor do vetor na posicao[%d]", i);
        scanf("%d", &vet[i]);
    }
    
    menorMaiorVetor(vet, n, &menor, &maior);

    printf("Maior valor: %d\n", maior);
    printf("Menor valor: %d", menor);

    free(vet); 
    
    return 0;
}