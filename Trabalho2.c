#include <stdio.h>
#include <stdlib.h> 

typedef struct Numero {
    int num;
    struct Numero *proximo;
}Numero;

typedef struct LSE {
    Numero *primeiro;
    int qtd;
}LSE;

void inserirInicio(LSE *lista, int numero) {
    Numero *novo = (Numero*) malloc(sizeof(Numero)); 
    if (novo == NULL) {
        return;
    }

    novo->num = numero;
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->qtd++;
}

void insereFim(LSE *lista, int numero) {
    Numero *novo = (Numero*) malloc(sizeof(Numero));
    if (novo == NULL) {
        return;
    }

    novo->num = numero;
    novo->proximo = NULL;

    if (lista->primeiro == NULL) 
    {
        lista->primeiro = novo;
    } else {
        Numero *ultimo = lista->primeiro;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo;
    }
    lista->qtd++;
}
int main () {

}