#include <stdio.h>
#include <stdlib.h>

void extraiVogais(char *str, char* vetorVogais) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            vetorVogais[j] = str[i];
            j++;
        }
    }
    vetorVogais[j] = '\0';
    
}


int main () {

    char *palavra = (char*) malloc (sizeof(char));
    char *vetVogais = (char*) malloc(sizeof(char));

    if (palavra == NULL || vetVogais == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    printf("Digite a palavra: ");
    scanf("%s", palavra);

    extraiVogais(palavra, vetVogais);
    
    printf("Vogais extraidas: %s\n", vetVogais);

    free(palavra);
    free(vetVogais);
}