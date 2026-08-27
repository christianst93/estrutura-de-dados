#include <stdio.h>
#include <stdlib.h>

void menorVetor(int *vt, int n, int *menor) {
        *menor = vt[0];    
        for (int i = 0; i < n; i++)
        {
            if (vt[i] < *menor)
            {
                *menor = vt[i];
            }            
        }
        printf("O menor valor: %d", *menor);
        
    }

int main() {

    int n;    
    int *menor = (int *) malloc(sizeof(int));
    printf("Digite o tamanho do vetor:");
    scanf("%d" , &n);

    int *vt = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Digite o valor do vetor na posicao[%d]" , i);
        scanf("%d", &vt[i]);
    }

    menorVetor(vt, n, menor);
    
    free(vt);
    free(menor);
    
    return 0;
}
