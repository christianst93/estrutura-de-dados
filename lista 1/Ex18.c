#include <stdio.h>
#include <stdlib.h>

void maiorVetor(int *vt, int n, int *maior) {
    *maior = vt[0];
    for (int i = 0; i < n; i++)
    {
        if (vt[i] > *maior)
        {
            *maior = vt[i];
        }
        
    }
    
}

int main() {

    int n;

    printf("Digite o valor de n:");
    scanf("%d", &n);

    int *vet = (int*) malloc(n * sizeof(int));
    int maior;

    for (int i = 0; i < n; i++)
    {
        printf("Digite o valor do vetor na posicao[%d]: ", i);
        scanf("%d", &vet[i]);
    }

    maiorVetor(vet, n, &maior);

    printf("O maior valor eh: %d", maior);

    free(vet);

    return 0;
    
}