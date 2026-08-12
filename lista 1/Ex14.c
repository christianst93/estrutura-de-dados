#include <stdio.h>
#include <stdlib.h>

void converte(int mnts, int *h, int *m) {
    *h = mnts / 60;
    *m = mnts % 60;     
}

int main() {
    
    int mnts, *h, *m;

    h = (int*) malloc(sizeof(int));
    m = (int*) malloc(sizeof(int));

    printf("Digite a quantidade de minutos:");
    scanf("%d", &mnts);

    converte(mnts, h, m);
    printf("%d horas e %d minutos.", *h, *m);

    free(h);
    free(m);

    return 0;
}