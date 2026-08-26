#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
}Data;


typedef struct proprietario
{
    char nome[30];
    char cpf[15];
}Proprietario;

typedef struct apartamento
{
    char condominio [30];
    int numAP;
    int andar;
    int qtd_comodos;
    int box;
    double v_aluguel;
    double v_condominio;
    Proprietario *proprietario;
    Data dataCompra;
}Apartamento;

void venderApartamento(Apartamento *ap, Proprietario *proprietario, Data data) {
    ap->proprietario = proprietario;
}

void mostraDadosProprietario(Proprietario proprietario) {
    printf("\nProperietario: %s", proprietario.nome);
    printf("\nCPF: %s" , proprietario.cpf);
}

void cadastraApartamento(Apartamento *ap, int numero, Proprietario *proprietario, Data data) {
    printf("Digite o nome do condominio: ");
    scanf("%s", ap->condominio);

    ap-> numAP = numero;

    printf("Digite o andar: ");
    scanf("%d", &ap->andar);

    printf("Digite a quantidade de comodos: ");
    scanf("%d", &ap->qtd_comodos);

    printf("Digite a quantidade de boxes: ");
    scanf("%d", &ap->box);

    printf("Digite o valor do aluguel: ");
    scanf("%lf", &ap->v_aluguel);

    printf("Digite o valor do condominio: ");
    scanf("%lf", &ap->v_condominio);

    ap->proprietario = proprietario;
    ap->dataCompra = data;
    
}

void mostraDadosApartamento(Apartamento ap) {
    printf("\nNome do condominio: %s", ap.condominio);
    printf("\nNumero do apartamento: %d", ap.numAP);
    printf("\nAndar: %d", ap.andar);
    printf("\nQuantidade comodos: %d", ap.qtd_comodos);
    printf("\nBox: %d", ap.box);
    printf("\nValor aluguel: %.2lf", ap.v_aluguel);
    printf("\nValor condominio: %.2lf", ap.v_condominio);
    printf("\nProprietario: %s\n", ap.proprietario->nome);
}

void trocaValorAluguel(Apartamento *ap, double valor) {
    ap->v_aluguel = valor;
}

void aumentaAluguelEm10Porcentos(Apartamento *ap) {
   ap->v_aluguel *= 1.10;
}

int retornaBoxApartamento(Apartamento *ap) {
    return ap->box;
}

Apartamento criarNovoApartamento(char *condominio, int numAp, int andar,int qtdComodos, int Box, double valorAluguel, double valorCondominio, Proprietario proprietario, Data data) {
    Apartamento apartamento;

    strcpy(apartamento.condominio, condominio);
    apartamento.numAP = numAp;
    apartamento.andar = andar;
    apartamento.qtd_comodos = qtdComodos;
    apartamento.box = Box;
    apartamento.v_aluguel = valorAluguel;
    apartamento.v_condominio = valorCondominio;

    apartamento.proprietario = (Proprietario *) malloc(sizeof(Proprietario));
    *(apartamento.proprietario) = proprietario; 
    apartamento.dataCompra = data;

    return apartamento;
}

int main(void) {   

    Proprietario proprietario = {"Christian Torres", "000.000.000-07"};
    Data data = {25, 8, 2026};
    Proprietario *proprietario1 = (Proprietario*)malloc(sizeof(proprietario));

    Apartamento ap101 = {"Morada do parque", 101, 1, 3, 2, 780.00, 230, &proprietario, data};
    Apartamento ap201;

    strcpy(proprietario1->nome, "Igor Avila");
    strcpy(proprietario1->cpf, "000.000.000-09");
    
    strcpy(ap201.condominio, "Morada do parque");
    ap201.numAP = 201;
    ap201.andar = 2;
    ap201.box = 1;
    ap201.qtd_comodos = 3;
    ap201.v_aluguel = 712.32;
    ap201.v_condominio = 230;
    ap201.proprietario = &proprietario;
    ap201.dataCompra = data;

    Apartamento ap301;
    
    Apartamento ap401;

    ap401 = criarNovoApartamento("Bragança", 401, 4, 5, 1, 534.00, 157, *proprietario1, data);

    cadastraApartamento(&ap301, 301, &proprietario, data);

    mostraDadosApartamento(ap101);
    trocaValorAluguel(&ap101, 700);
    mostraDadosApartamento(ap201);

    aumentaAluguelEm10Porcentos(&ap101);
    aumentaAluguelEm10Porcentos(&ap201);
    aumentaAluguelEm10Porcentos(&ap301);
    aumentaAluguelEm10Porcentos(&ap401);    

    mostraDadosApartamento(ap101);
    mostraDadosApartamento(ap201);
    mostraDadosApartamento(ap301);
    mostraDadosApartamento(ap401);

    printf("\nNumerdo do box: %d", retornaBoxApartamento(&ap201));
    printf("\nNumerdo do box: %d", retornaBoxApartamento(&ap301));

    
    mostraDadosProprietario(proprietario);
    venderApartamento(&ap101, proprietario1, data);
    mostraDadosApartamento(ap101);

    free(ap401.proprietario);
    free(proprietario1);
    return 0;
}