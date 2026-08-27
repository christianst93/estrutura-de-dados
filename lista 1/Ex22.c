#include <stdio.h>
#include <stdlib.h>

void inverteVetor(int *v, int n) {
    int *inicio = v;
    int *fim = &v[n -1];
    int aux;
    for (int i = 0; i < n/2; i++)
    {
        aux = *inicio;
        *inicio = *fim;
        *fim = aux;

        inicio++;
        fim--;
    }
    
}


int main () {
    int n;

    printf("Digite o tamanho do vetor:");
    scanf("%d" , &n);

    int *vet = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Digite o valor do vetor na posicao[%d]" , i);
        scanf("%d", &vet[i]);
    }

    inverteVetor(vet, n);

    for (int i = 0; i < n; i++)
    {
        printf("Valor na posicao[%d]: %d\n", i, vet[i]);
    }    

    free(vet);

    return 0;
}