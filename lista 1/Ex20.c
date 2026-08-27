#include <stdio.h>
#include <stdlib.h>

int maiorVetorPonteiro(int *vt, int n, int *menor) {
        *menor = vt[0];    
        for (int i = 0; i < n; i++)
        {
            if (vt[i] < *menor)
            {
                *menor = vt[i];
            }            
        }
        return *menor;
    }

int main() {

    int n;    
    int menor;
    printf("Digite o tamanho do vetor:");
    scanf("%d" , &n);

    int *vt = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Digite o valor do vetor na posicao[%d]" , i);
        scanf("%d", &vt[i]);
    }

    maiorVetorPonteiro(vt, n, &menor);
    
    printf("Endereco do menor vetor: %p" , &menor);
    free(vt);
    
    return 0;
}
