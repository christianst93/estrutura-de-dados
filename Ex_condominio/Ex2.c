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

void cadastraApartamento(Apartamento *ap) {
    printf("Digite o nome do condominio: ");
    scanf("%s", ap->condominio);

    printf("Digite o numero do apartamento: ");
    scanf("%d", &ap->numAP);

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
    printf("\nNome do condominio: %s\n", ap.condominio);
    printf("\nNumero do apartamento: %d\n", ap.numAP);
    printf("\nAndar: %d\n", ap.andar);
    printf("\nQuantidade comodos: %d\n", ap.qtd_comodos);
    printf("\nBox: %d\n", ap.box);
    printf("\nValor aluguel: %.2lf\n", ap.v_aluguel);
    printf("\nValor condominio: %.2lf\n", ap.v_condominio);
}

void alteraAluguelEm10Porcentos(Apartamento *ap) {
   ap->v_aluguel *= 1.10;
}

int main(void) {
    Apartamento ap101;
    Apartamento ap201;

    cadastraApartamento(&ap101);
    cadastraApartamento(&ap201);

    mostraDadosApartamento(ap101);
    mostraDadosApartamento(ap201);

    alteraAluguelEm10Porcentos(&ap101);
    alteraAluguelEm10Porcentos(&ap201);

    mostraDadosApartamento(ap101);
    mostraDadosApartamento(ap201);

    return 0;
}