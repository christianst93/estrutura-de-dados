/* Compilar: gcc jogo.c -o jogo    Executar: ./jogo */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char itens[4];
    int topo; 
    int cap;
} Pilha;

Pilha pilha[4]; 
Pilha temp[2];  
int ntemps;
int movimentos;
time_t inicio;

void inicializar(Pilha *p, int cap) {
    p->topo = -1;
    p->cap = cap;
}

int vazia(Pilha *p) {
    return p->topo == -1;
}

int cheia(Pilha *p) {
    return p->topo + 1 >= p->cap;
}

int push(Pilha *p, char pino) {
    if (cheia(p)) {
        return 0;
    }
    p->topo = p->topo + 1;
    p->itens[p->topo] = pino;
    return 1;
}

int pop(Pilha *p, char *pino) {
    if (vazia(p)) {
        return 0;
    }
    *pino = p->itens[p->topo];
    p->topo = p->topo - 1;
    return 1;
}

void distribuir(void) {
    char pinos[12] = {'V', 'V', 'V', 'G', 'G', 'G', 'A', 'A', 'A', 'M', 'M', 'M'};
    int i, j;
    char aux;

    for (i = 11; i > 0; i--) {
        j = rand() % (i + 1);
        aux = pinos[i];
        pinos[i] = pinos[j];
        pinos[j] = aux;
    }

    for (i = 0; i < 4; i++) {
        inicializar(&pilha[i], 4);
    }
    inicializar(&temp[0], 1);
    inicializar(&temp[1], 1);

    /* 3 pinos em cada pilha. O 4o lugar fica livre. */
    for (i = 0; i < 12; i++) {
        push(&pilha[i % 4], pinos[i]);
    }
}

int venceu(void) {
    int i, j;
    char cor;

    if (!vazia(&temp[0]) || !vazia(&temp[1])) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (pilha[i].topo + 1 != 3) {
            return 0;
        }
        cor = pilha[i].itens[0];
        for (j = 1; j <= pilha[i].topo; j++) {
            if (pilha[i].itens[j] != cor) {
                return 0;
            }
        }
    }
    return 1;
}

void mostrar(void) {
    int linha, i;
    long s;
    char *nivel;

    s = (long)(time(NULL) - inicio);
    if (ntemps == 2) {
        nivel = "Facil";
    } else if (ntemps == 1) {
        nivel = "Medio";
    } else {
        nivel = "Dificil";
    }

    printf("\n%s | Tempo %02ld:%02ld | Movimentos %d\n", nivel, s / 60, s % 60, movimentos);
    printf(" P1    P2    P3    P4\n");
    for (linha = 3; linha >= 0; linha--) {
        for (i = 0; i < 4; i++) {
            if (linha == pilha[i].topo) {
                printf(" (%c)  ", pilha[i].itens[linha]);
            } else if (linha < pilha[i].topo) {
                printf("  %c   ", pilha[i].itens[linha]);
            } else {
                printf("  .   ");
            }
        }
        printf("\n");
    }

    if (ntemps >= 1) {
        printf("Temp1: %c", vazia(&temp[0]) ? '.' : temp[0].itens[0]);
    }
    if (ntemps == 2) {
        printf("    Temp2: %c", vazia(&temp[1]) ? '.' : temp[1].itens[0]);
    }
    if (ntemps == 0) {
        printf("Sem temporario neste nivel");
    }
    printf("\n( ) = topo    . = vazio    V G A M\n");
}

int ler(char *texto, int max) {
    int n;

    printf("%s (1 a %d)? ", texto, max);
    fflush(stdout);
    if (scanf("%d", &n) != 1) {
        while (getchar() != '\n' && !feof(stdin)) {
        }
        return -1;
    }
    if (n < 1 || n > max) {
        return -1;
    }
    return n - 1;
}

int mover(Pilha *origem, Pilha *destino) {
    char pino;

    if (origem == destino) {
        printf("Origem e destino sao a mesma pilha.\n");
        return 0;
    }
    if (vazia(origem)) {
        printf("Nao ha pino para tirar.\n");
        return 0;
    }
    if (cheia(destino)) {
        printf("Destino cheio.\n");
        return 0;
    }
    pop(origem, &pino);
    push(destino, pino);
    return 1;
}

int main(void) {
    int op, a, b, ok;
    long s;

    printf("1 Facil (Temp1 e Temp2)\n");
    printf("2 Medio (somente Temp1)\n");
    printf("3 Dificil (sem temporario)\n");
    printf("Nivel: ");
    if (scanf("%d", &op) != 1 || op < 1 || op > 3) {
        return 0;
    }
    ntemps = 3 - op;

    srand((unsigned)time(NULL));
    distribuir();
    movimentos = 0;
    inicio = time(NULL);

    while (1) {
        mostrar();
        printf("1 PUSH pilha e POP pilha\n");
        printf("2 POP pilha e PUSH temporario\n");
        printf("3 POP temporario e PUSH pilha\n");
        printf("0 Sair\nOpcao: ");
        if (scanf("%d", &op) != 1) {
            break;
        }

        ok = 0;
        if (op == 0) {
            break;
        } else if (op == 1) {
            b = ler("PUSH em qual pilha", 4);
            a = ler("POP de qual pilha", 4);
            if (a >= 0 && b >= 0) {
                ok = mover(&pilha[a], &pilha[b]);
            }
        } else if ((op == 2 || op == 3) && ntemps == 0) {
            printf("Nivel dificil nao usa temporario.\n");
        } else if (op == 2) {
            a = ler("POP de qual pilha", 4);
            b = ler("PUSH em qual temporario", ntemps);
            if (a >= 0 && b >= 0) {
                ok = mover(&pilha[a], &temp[b]);
            }
        } else if (op == 3) {
            a = ler("POP de qual temporario", ntemps);
            b = ler("PUSH em qual pilha", 4);
            if (a >= 0 && b >= 0) {
                ok = mover(&temp[a], &pilha[b]);
            }
        }

        if (ok) {
            movimentos = movimentos + 1;
            if (venceu()) {
                mostrar();
                printf("Parabens! Cada pilha ficou com uma cor.\n");
                break;
            }
        }
    }

    s = (long)(time(NULL) - inicio);
    printf("Tempo: %02ld:%02ld\nMovimentos: %d\n", s / 60, s % 60, movimentos);
    return 0;
}
