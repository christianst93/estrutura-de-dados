#include <stdio.h>
#include <stdlib.h>

 void codigoAsc(char *p, int n) {
    for (int i = 0; i < n; i++)
    {
        printf("Caracter: %c   | ASCII: %d\n", p[i], p[i]);
    }
    
 }

int main () {

    int n;

    printf("Digite o tamanho da palavra:");
    scanf("%d", &n);

    char *txt = (char*) malloc ((n + 1) * sizeof(char));

    printf("Digite a palavra:");
    scanf("%s", txt);

    codigoAsc(txt,n);

    free(txt);

    return 0;
}