#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct numero
{
    int num;
    struct numero *proximo;
} Numero;

typedef struct lse
{
    Numero *primeiro;
    int qtd;
    int menor, maior;
} LSE;

void inicializaListaLSE(LSE *ls)
{
    ls->primeiro = NULL;
    ls->qtd = 0;
    ls->menor = 1000;
    ls->maior = -1;
}

void insereInicio(LSE *lista, Numero *pn)
{
    pn->proximo = NULL;
    if(lista->menor >= pn->num){
        pn->proximo = lista->primeiro;
        lista->primeiro = pn;
        lista->qtd++;
        lista->menor = pn->num;
        if(pn->num > lista->maior)
            lista->maior = pn->num;
    }else{
        printf("\nO valor inserido no inicio não é menor que o primeiro da lista!!\n");
    }
}

void insereFim(LSE *lista, Numero *pn) {
    pn->proximo = NULL;
    if(lista->maior <= pn->num){
        if (lista->primeiro == NULL) {
            insereInicio(lista, pn);
            return;
        } else {
            Numero *aux = lista->primeiro;
            while (aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = pn;
        }
        lista->qtd++;
        lista->maior = pn->num;
        if(pn->num < lista->menor)
            lista->menor = pn->num;
    }else{
        printf("\nO valor inserido no fim não é maior que o último da lista!!\n");
    }
}

void insereOrdenado(LSE *lista, Numero *pn) {
    if (lista->primeiro == NULL || pn->num < lista->menor) {
        insereInicio(lista, pn);
    } else if (pn->num > lista->maior) {
        insereFim(lista, pn);
    } else {
        Numero *aux = lista->primeiro;
        while (aux->proximo != NULL && aux->proximo->num < pn->num) {
            aux = aux->proximo;
        }
        pn->proximo = aux->proximo;
        aux->proximo = pn;
        lista->qtd++;
    }
}

void removeInicio(LSE *lista) {
    if (lista->primeiro == NULL) {
        printf("\nA lista está vazia, não é possível remover o primeiro elemento.\n");
        return;
    }
    Numero *aux = lista->primeiro;
    lista->primeiro = aux->proximo;
    free(aux);
    lista->qtd--;
    if (lista->primeiro == NULL) {
        lista->menor = 1000;
        lista->maior = -1;
    } else {
        lista->menor = lista->primeiro->num;
    }
}

void removeFim(LSE *lista) {
    if (lista->primeiro == NULL) {
        printf("\nA lista está vazia, não é possível remover o último elemento.\n");
        return;
    }
    if (lista->primeiro->proximo == NULL) {
        removeInicio(lista);
        return;
    }
    Numero *aux = lista->primeiro;
    while (aux->proximo->proximo != NULL) {
        aux = aux->proximo;
    }
    free(aux->proximo);
    aux->proximo = NULL;
    lista->qtd--;
    lista->maior = aux->num;
}

void removeOrdenado(LSE *lista, int valor) {
    if (lista->primeiro == NULL) {
        printf("\nA lista está vazia, não é possível remover o elemento.\n");
        return;
    }
    if (lista->primeiro->num == valor) {
        removeInicio(lista);
        return;
    }
    Numero *aux = lista->primeiro;
    while (aux->proximo != NULL && aux->proximo->num != valor) {
        aux = aux->proximo;
    }
    if (aux->proximo == NULL) {
        printf("\nO valor %d não foi encontrado na lista.\n", valor);
        return;
    }
    Numero *temp = aux->proximo;
    aux->proximo = temp->proximo;
    free(temp);
    lista->qtd--;
}

void mostraLista(LSE *lista)
{
    Numero *aux = lista->primeiro;
    if (aux == NULL)
    {
        printf("\n =>> LISTA VAZIA <<=");
        return;
    }
    int ct = 0;
    printf("\n => Inicio da Lista <=");
    while (aux != NULL)
    {
        printf("\n E%d ", ct++);
        printf("  %d  ", aux->num);
        aux = aux->proximo;
    }
    printf("\n => Fim da Lista <=\n");
}

void mostraMatriz(LSE *lista)
{
    Numero *aux = lista->primeiro;

    printf("\nMatriz da lista (50 x 20):\n");
    for (int linha = 0; linha < 50; linha++)
    {
        for (int coluna = 0; coluna < 20; coluna++)
        {
            if (aux != NULL)
            {
                printf("%4d ", aux->num);
                aux = aux->proximo;
            }
        }
        printf("\n");
    }
}

void mostrarMenorValor(LSE *lista)
{
    if (lista->primeiro == NULL)
    {
        printf("\nA lista está vazia, não há menor valor.\n");
        return;
    }
    printf("\nMenor valor da lista: %d\n", lista->menor);
}

void mostrarMaiorValor(LSE *lista)
{
    if (lista->primeiro == NULL)
    {
        printf("\nA lista está vazia, não há maior valor.\n");
        return;
    }
    printf("\nMaior valor da lista: %d\n", lista->maior);
}

void mediaAritimetica(LSE *lista)
{
    if (lista->primeiro == NULL)
    {
        printf("\nA lista está vazia, não é possível calcular a média.\n");
        return;
    }
    Numero *aux = lista->primeiro;
    int soma = 0;
    while (aux != NULL)
    {
        soma += aux->num;
        aux = aux->proximo;
    }
    float media = (float)soma / lista->qtd;
    printf("\nMédia aritmética dos valores da lista: %.2f\n", media);
}

void desvioPadrao(LSE *lista)
{
    if (lista->primeiro == NULL)
    {
        printf("\nA lista está vazia, não é possível calcular o desvio padrão.\n");
        return;
    }
    Numero *aux = lista->primeiro;
    int soma = 0;
    while (aux != NULL)
    {
        soma += aux->num;
        aux = aux->proximo;
    }
    float media = (float)soma / lista->qtd;

    aux = lista->primeiro;
    float somaQuadrados = 0;
    while (aux != NULL)
    {
        somaQuadrados += (aux->num - media) * (aux->num - media);
        aux = aux->proximo;
    }
    float desvioPadrao = sqrt(somaQuadrados / lista->qtd);
    printf("\nDesvio padrão dos valores da lista: %.2f\n", desvioPadrao);
}

void quantiadadeRepetidos(LSE *lista) {
    if (lista->primeiro == NULL) {
        printf("\nA lista está vazia, não há elementos repetidos.\n");
        return;
    }
    Numero *aux = lista->primeiro;
    int count = 0;
    while (aux != NULL) {
        Numero *temp = aux->proximo;
        while (temp != NULL) {
            if (aux->num == temp->num) {
                count++;
                break;
            }
            temp = temp->proximo;
        }
        aux = aux->proximo;
    }
    printf("\nQuantidade de elementos repetidos na lista: %d\n", count);
}

void liberarLista(LSE *lista) {
    Numero *aux = lista->primeiro;
    while (aux != NULL) {
        Numero *temp = aux;
        aux = aux->proximo;
        free(temp);
    }
    free(lista);
}

int main()
{
    LSE *ListaNumeros = (LSE *)malloc(sizeof(LSE));
    inicializaListaLSE(ListaNumeros);

    Numero *aux = NULL;

    for (int i = 0; i < 1000; i++)
    {
        aux = (Numero *)malloc(sizeof(Numero));
        aux->num = rand() % 1001;

        insereOrdenado(ListaNumeros, aux);
    }

    mostraMatriz(ListaNumeros);
    mostrarMenorValor(ListaNumeros);
    mostrarMaiorValor(ListaNumeros);
    mediaAritimetica(ListaNumeros);
    desvioPadrao(ListaNumeros);
    quantiadadeRepetidos(ListaNumeros);

    // Demonstração das funções de remoção
    printf("\n\n===== Demonstração das operações de remoção =====\n");

    printf("\n--- Antes das remoções ---");
    printf("\nQuantidade de elementos: %d", ListaNumeros->qtd);
    mostrarMenorValor(ListaNumeros);
    mostrarMaiorValor(ListaNumeros);

    removeInicio(ListaNumeros);
    printf("\nApós removeInicio -> qtd: %d, menor: %d\n", ListaNumeros->qtd, ListaNumeros->menor);

    removeFim(ListaNumeros);
    printf("Após removeFim    -> qtd: %d, maior: %d\n", ListaNumeros->qtd, ListaNumeros->maior);

    int valorParaRemover = ListaNumeros->primeiro->proximo->num;
    printf("Removendo o valor %d com removeOrdenado...\n", valorParaRemover);
    removeOrdenado(ListaNumeros, valorParaRemover);
    printf("Após removeOrdenado(%d) -> qtd: %d\n", valorParaRemover, ListaNumeros->qtd);

    printf("\n--- Depois das remoções ---");
    printf("\nQuantidade de elementos: %d\n", ListaNumeros->qtd);

    liberarLista(ListaNumeros);

    return 0;
}
