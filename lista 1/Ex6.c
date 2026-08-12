#include <stdio.h>
#include <stdlib.h>

int main () {

    int *p = NULL;

    p = (int*) malloc(sizeof(int));
    
    printf("Digite o valor de P:");
    scanf("%d", p);

    printf("Valor de p = %d\n", *p);
    free(p);
    return 0;
}