#include <stdio.h>
#include <stdlib.h>

void dividaAB(int *pa, int *pb, double *pab) {
    *pab = *pa / *pb;
}

int main () {

    int a,b;
    double *pab;

    printf("Digite o valor de a:");
    scanf("%d", &a);
    printf("Digite o valor de b:");
    scanf("%d", &b);

    pab = (double*) malloc(sizeof(double));

    dividaAB(&a, &b, pab);
    printf("Valor da divisao de A/B = %.2lf\n", *pab);

    free(pab);

    return 0;
}