#include <stdio.h>
#include <stdlib.h>

int contaVogais(char *str) {
    int num = 0;
    for (int i = 0; i < str[i] != '\0'; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            num++;       
        }        
    }
    return num;
}


int main() {

    char *palavra = (char*) malloc (sizeof(char));

    printf("Digite uma palavra: ");
    scanf("%s", palavra);

    printf("Numero de vogais: %d", contaVogais(palavra));

    free(palavra);

    return 0;
    
}