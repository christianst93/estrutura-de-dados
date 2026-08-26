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

int main(void) {
    Apartamento ap101 = {"Morada do parque", 133, 1, 3, 2, 780.00, 230};
    Apartamento ap201;

    strcpy(ap201.condominio, "Morada do parque");
    ap201.numAP = 201;
    ap201.andar = 2;
    ap201.numAP = 201;
    ap201.qtd_comodos = 3;
    ap201.v_aluguel = 712.32;
    ap201.v_condominio = 230;

    return 0;
}