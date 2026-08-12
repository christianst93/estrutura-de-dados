#include <stdio.h>
#include <stdlib.h>

int main () {

    double a, b;
    double *ps, *qs;

    printf("Digite o primeiro peso:");
    scanf("%lf", &a);
    printf("Digite o segundo peso:");
    scanf("%lf", &b);

    ps = (double*) malloc(sizeof(double));

    *ps = a + b;
    qs = ps;
    double c = *ps;
    printf("Valor de c = %.2lf\n", c);

    *qs += 100;

    printf("Valor de *qs = %.2lf\n", *qs);
    printf("Valor de *ps = %.2lf\n", *ps);

    qs = &b;
    *qs -= 10;
    printf("Valor de a = %.2lf\n", a);
    printf("Valor de b = %.2lf\n", b);
    printf("Valor de *ps = %.2lf\n", *ps);
    printf("Valor de *qs = %.2lf\n", *qs);

    free(ps);
}