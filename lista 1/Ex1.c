#include <stdio.h>
#include <stdlib.h>

int main () {

    char letra;
    short st;
    int valor;
    long int valorMaior;
    long double dobro;
    float flutuante;

    printf("Tamanho de um char: %zu byte(s) | Endereco da variavel: %p\n", sizeof(letra), &letra);
    printf("Tamanho de um short: %zu byte(s) | Endereco da variavel: %p\n", sizeof(st), &st);
    printf("Tamanho de um int: %zu byte(s) | Endereco da variavel: %p\n", sizeof(valor), &valor); 
    printf("Tamanho de um long int: %zu byte(s) | Endereco da variavel: %p\n", sizeof(valorMaior), &valorMaior);
    printf("Tamanho de um float: %zu byte(s) | Endereco da variavel: %p\n", sizeof(flutuante), &flutuante);
    printf("Tamanho de um long double: %zu byte(s) | Endereco da variavel: %p\n", sizeof(dobro), &dobro);

    return 0;
}