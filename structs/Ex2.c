#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct apartamento
{
    char condominio [30];
    int numAP;
    int andar;
    int qtd_comodos;
    int box;
    double v_aluguel;
    double v_condominio;
}Apartamento;

typedef struct proprietario
{
    char nome[30];
    char cpf[14];
}Proprietario;

void mostraDadosProprietario(Proprietario proprietario) {
    printf("\nProperietario: %s", proprietario.nome);
    printf("\nCPF: %s" , proprietario.cpf);
}

void cadastraApartamento(Apartamento *ap, int numero) {
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
}

void mostraDadosApartamento(Apartamento ap) {
    printf("\nNome do condominio: %s", ap.condominio);
    printf("\nNumero do apartamento: %d", ap.numAP);
    printf("\nAndar: %d", ap.andar);
    printf("\nQuantidade comodos: %d", ap.qtd_comodos);
    printf("\nBox: %d", ap.box);
    printf("\nValor aluguel: %.2lf", ap.v_aluguel);
    printf("\nValor condominio: %.2lf", ap.v_condominio);
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

Apartamento criarNovoApartamento(char *condominio, int numAp, int andar,int qtdComodos, int Box, double valorAluguel, double valorCondominio) {
    Apartamento apartamento;

    strcpy(apartamento.condominio, condominio);
    apartamento.numAP = numAp;
    apartamento.andar = andar;
    apartamento.qtd_comodos = qtdComodos;
    apartamento.box = Box;
    apartamento.v_aluguel = valorAluguel;
    apartamento.v_condominio = valorCondominio;

    return apartamento;
}

int main(void) {
    Apartamento ap101 = {"Morada do parque", 101, 1, 3, 2, 780.00, 230};
    Apartamento ap201;
    
    strcpy(ap201.condominio, "Morada do parque");
    ap201.numAP = 201;
    ap201.andar = 2;
    ap201.box = 1;
    ap201.qtd_comodos = 3;
    ap201.v_aluguel = 712.32;
    ap201.v_condominio = 230;

    Apartamento ap301;
    
    Apartamento ap401;
    ap401 = criarNovoApartamento("Bragança", 401, 4, 5, 1, 534.00, 157);

    cadastraApartamento(&ap301, 301);

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

    Proprietario proprietario = {"Christian Torres", "000.000.000-07"};
    mostraDadosProprietario(proprietario);
    
    return 0;
}