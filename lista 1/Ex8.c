#include <stdio.h>
#include <stdlib.h>

int main () {

    double a, b;
    double *ps;

    printf("Digite o primeiro peso:");
    scanf("%lf", &a);
    printf("Digite o segundo peso:");
    scanf("%lf", &b);

    ps = (double*) malloc(sizeof(double));

    *ps = a + b;
    double c = *ps;
    printf("Valor de c = %.2lf\n", c);

    free(ps);
}