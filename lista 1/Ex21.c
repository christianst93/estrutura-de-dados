#include <stdio.h>
#include <stdlib.h>

int maiorVetorPonteiro(int *vt, int n, int *maior) {
        *maior = vt[0];    
        for (int i = 0; i < n; i++)
        {
            if (vt[i] > *maior)
            {
                *maior = vt[i];
            }            
        }
        return *maior;
    }

int main() {

    int n;    
    int maior;
    printf("Digite o tamanho do vetor:");
    scanf("%d" , &n);

    int *vt = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Digite o valor do vetor na posicao[%d]" , i);
        scanf("%d", &vt[i]);
    }

    maiorVetorPonteiro(vt, n, &maior);
    
    printf("Endereco do menor vetor: %p" , &maior);
    free(vt);
    
    return 0;
}
