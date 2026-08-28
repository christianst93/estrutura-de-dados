#include <stdio.h>
#include <stdlib.h>

void extraiConsoantes(char* str, char *vetorConsoantes) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u')
        {
            vetorConsoantes[j] = str[i];
            j++;
        }
    }
    vetorConsoantes[j] = '\0';    
}


int main() {
    char *palavra = (char*) malloc(100 * sizeof(char));
    char *vetorConsoantes = (char*) malloc(100 * sizeof(char));

    if (palavra == NULL || vetorConsoantes == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    printf("Digite a palavra:");
    scanf("%s", palavra);

    extraiConsoantes(palavra, vetorConsoantes);

    printf("Consoantes: %s", vetorConsoantes);

    free(palavra);
    free(vetorConsoantes);

    return 0;
}