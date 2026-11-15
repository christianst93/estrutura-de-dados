
// Compilar: gcc jogo.c -o jogo
//Executar: ./jogo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PILHA 4
#define QTD_PILHAS 4
#define QTD_CORES 4
#define POR_COR 3
#define TOTAL_PINOS 12

typedef struct {
    char itens[MAX_PILHA];
    int topo; /* -1 = vazia. POP so tira este pino. */
    int cap;
} Pilha;

Pilha pilha[QTD_PILHAS];
Pilha temp[2];
int ntemps;
int movimentos;
time_t inicio;

char CORES[QTD_CORES] = {'V', 'G', 'A', 'M'};

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

void embaralhar(char v[], int n) {
    int i, j;
    char aux;

    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

void distribuir(void) {
    char pinos[TOTAL_PINOS];
    int i, c, k;

    k = 0;
    for (c = 0; c < QTD_CORES; c++) {
        for (i = 0; i < POR_COR; i++) {
            pinos[k] = CORES[c];
            k = k + 1;
        }
    }
    embaralhar(pinos, TOTAL_PINOS);

    for (i = 0; i < QTD_PILHAS; i++) {
        inicializar(&pilha[i], MAX_PILHA);
    }
    inicializar(&temp[0], 1);
    inicializar(&temp[1], 1);

    /* 3 pinos em cada pilha. O 4o lugar fica livre. */
    for (i = 0; i < TOTAL_PINOS; i++) {
        push(&pilha[i % QTD_PILHAS], pinos[i]);
    }
}

int venceu(void) {
    int i, j;
    char cor;

    if (!vazia(&temp[0]) || !vazia(&temp[1])) {
        return 0;
    }

    for (i = 0; i < QTD_PILHAS; i++) {
        if (pilha[i].topo + 1 != POR_COR) {
            return 0;
        }
        cor = pilha[i].itens[0];
        for (j = 1; j <= pilha[i].topo; j++) {
            if (pilha[i].itens[j] != cor) {
                return 0;
            }
        }
        for (j = 0; j < i; j++) {
            if (pilha[j].itens[0] == cor) {
                return 0;
            }
        }
    }
    return 1;
}

long segundos(void) {
    return (long)(time(NULL) - inicio);
}

const char *nome_nivel(void) {
    if (ntemps == 2) {
        return "Facil";
    }
    if (ntemps == 1) {
        return "Medio";
    }
    return "Dificil";
}

void mostrar_temp(Pilha *p) {
    if (vazia(p)) {
        printf("[ vazio ]");
    } else {
        printf("[ %c ]", p->itens[p->topo]);
    }
}

void mostrar(void) {
    int linha, i;
    long s;

    s = segundos();
    printf("\n");
    printf("=============================================\n");
    printf(" JOGO DOS PINOS\n");
    printf(" Nivel: %-8s Tempo: %02ld:%02ld  Movimentos: %d\n",
           nome_nivel(), s / 60, s % 60, movimentos);
    printf("=============================================\n");
    printf("                  TOPO\n");

    printf("    ");
    for (i = 0; i < QTD_PILHAS; i++) {
        printf("  P%d   ", i + 1);
    }
    printf("\n");

    for (linha = MAX_PILHA - 1; linha >= 0; linha--) {
        printf("    ");
        for (i = 0; i < QTD_PILHAS; i++) {
            if (linha == pilha[i].topo) {
                printf(" (%c)   ", pilha[i].itens[linha]);
            } else if (linha < pilha[i].topo) {
                printf("  %c    ", pilha[i].itens[linha]);
            } else {
                printf("  .    ");
            }
        }
        printf("\n");
    }

    printf("    ");
    for (i = 0; i < QTD_PILHAS; i++) {
        printf(" ===   ");
    }
    printf("\n");
    printf("    ");
    for (i = 0; i < QTD_PILHAS; i++) {
        printf(" %d/4   ", pilha[i].topo + 1);
    }
    printf("\n");
    printf("                  BASE\n\n");

    if (ntemps == 0) {
        printf("  Temporarios: nenhum neste nivel\n");
    } else {
        printf("  Temp1 ");
        mostrar_temp(&temp[0]);
        if (ntemps == 2) {
            printf("      Temp2 ");
            mostrar_temp(&temp[1]);
        }
        printf("\n");
    }

    printf("\n");
    printf("  ( ) marca o TOPO, o unico pino que o POP tira.\n");
    printf("  . e lugar vazio. Cada pilha cabe 4.\n");
    printf("  V vermelho   G verde   A azul   M amarelo\n");
    fflush(stdout);
}

int ler_int(int *valor) {
    int c;

    if (scanf("%d", valor) == 1) {
        return 1;
    }
    if (feof(stdin)) {
        return 0;
    }
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    printf("Entrada invalida. Digite um numero.\n");
    return 0;
}

int indice_pilha(int n) {
    if (n < 1 || n > QTD_PILHAS) {
        printf("Pilha invalida. Escolha de 1 a 4.\n");
        return -1;
    }
    return n - 1;
}

int indice_temp(int n) {
    if (n < 1 || n > ntemps) {
        if (ntemps == 1) {
            printf("Nivel medio so tem o Temp1.\n");
        } else {
            printf("Temporario invalido. Escolha 1 ou 2.\n");
        }
        return -1;
    }
    return n - 1;
}

int mover(Pilha *origem, Pilha *destino) {
    char pino;

    if (origem == destino) {
        printf("\nOrigem e destino sao a mesma pilha.\n");
        return 0;
    }
    if (vazia(origem)) {
        printf("\nNao ha pino para tirar (POP).\n");
        return 0;
    }
    /* Confere antes do POP. Se o destino estiver cheio, o pino se perde. */
    if (cheia(destino)) {
        if (destino->cap == 1) {
            printf("\nTemporario ocupado. Ele guarda so 1 pino.\n");
        } else {
            printf("\nPilha cheia. Cabe no maximo 4 pinos.\n");
        }
        return 0;
    }

    pop(origem, &pino);
    push(destino, pino);
    return 1;
}

int jogada_entre_pilhas(void) {
    int destino, origem, id, io;

    printf("PUSH em qual pilha (1 a 4)? ");
    fflush(stdout);
    if (!ler_int(&destino)) {
        return 0;
    }
    id = indice_pilha(destino);
    if (id < 0) {
        return 0;
    }

    printf("POP de qual pilha (1 a 4)? ");
    fflush(stdout);
    if (!ler_int(&origem)) {
        return 0;
    }
    io = indice_pilha(origem);
    if (io < 0) {
        return 0;
    }

    return mover(&pilha[io], &pilha[id]);
}

int jogada_pilha_temp(void) {
    int origem, canto, io, it;

    if (ntemps == 0) {
        printf("\nNivel dificil nao usa temporario.\n");
        return 0;
    }

    printf("POP de qual pilha (1 a 4)? ");
    fflush(stdout);
    if (!ler_int(&origem)) {
        return 0;
    }
    io = indice_pilha(origem);
    if (io < 0) {
        return 0;
    }

    printf("PUSH em qual temporario (1 a %d)? ", ntemps);
    fflush(stdout);
    if (!ler_int(&canto)) {
        return 0;
    }
    it = indice_temp(canto);
    if (it < 0) {
        return 0;
    }

    return mover(&pilha[io], &temp[it]);
}

int jogada_temp_pilha(void) {
    int canto, destino, it, id;

    if (ntemps == 0) {
        printf("\nNivel dificil nao usa temporario.\n");
        return 0;
    }

    printf("POP de qual temporario (1 a %d)? ", ntemps);
    fflush(stdout);
    if (!ler_int(&canto)) {
        return 0;
    }
    it = indice_temp(canto);
    if (it < 0) {
        return 0;
    }

    printf("PUSH em qual pilha (1 a 4)? ");
    fflush(stdout);
    if (!ler_int(&destino)) {
        return 0;
    }
    id = indice_pilha(destino);
    if (id < 0) {
        return 0;
    }

    return mover(&temp[it], &pilha[id]);
}

void escolher_nivel(void) {
    int op;

    printf("\n");
    printf("TADS - Estrutura de Dados\n");
    printf("Jogo de pinos coloridos\n\n");
    printf("4 pilhas e 12 pinos: V, G, A e M, 3 de cada cor.\n");
    printf("Cada pilha cabe 4 pinos de qualquer cor.\n");
    printf("Mova um pino por vez, sempre pelo topo.\n");
    printf("Vence quando cada pilha tiver uma unica cor.\n\n");
    printf("Nivel:\n");
    printf("  1 - Facil   (Temp1 e Temp2)\n");
    printf("  2 - Medio   (somente Temp1)\n");
    printf("  3 - Dificil (sem temporario)\n");

    while (1) {
        printf("Escolha: ");
        fflush(stdout);
        if (!ler_int(&op)) {
            if (feof(stdin)) {
                ntemps = -1;
                return;
            }
            continue;
        }
        if (op == 1) {
            ntemps = 2;
            return;
        }
        if (op == 2) {
            ntemps = 1;
            return;
        }
        if (op == 3) {
            ntemps = 0;
            return;
        }
        printf("Escolha 1, 2 ou 3.\n");
    }
}

void mostrar_desempenho(void) {
    long s;

    s = segundos();
    printf("Tempo: %02ld:%02ld\n", s / 60, s % 60);
    printf("Movimentos: %d\n", movimentos);
}

int main(void) {
    int op, mudou, tentativas;

    escolher_nivel();
    if (ntemps < 0) {
        return 0;
    }

    /* srand uma vez. Sem isso, rand() repete a mesma partida. */
    srand((unsigned)time(NULL));
    tentativas = 0;
    do {
        distribuir();
        tentativas = tentativas + 1;
    } while (venceu() && tentativas < 30);

    movimentos = 0;
    inicio = time(NULL);

    while (1) {
        mostrar();
        printf("\n");
        printf("  1 - PUSH em uma pilha e POP de outra\n");
        printf("  2 - POP de uma pilha e PUSH no temporario\n");
        printf("  3 - POP do temporario e PUSH em uma pilha\n");
        printf("  0 - Sair\n");
        printf("Opcao: ");
        fflush(stdout);

        if (!ler_int(&op)) {
            if (feof(stdin)) {
                break;
            }
            continue;
        }

        mudou = 0;
        if (op == 0) {
            break;
        } else if (op == 1) {
            mudou = jogada_entre_pilhas();
        } else if (op == 2) {
            mudou = jogada_pilha_temp();
        } else if (op == 3) {
            mudou = jogada_temp_pilha();
        } else {
            printf("\nOpcao invalida. Use 1, 2, 3 ou 0.\n");
        }

        if (mudou) {
            movimentos = movimentos + 1;
            if (venceu()) {
                mostrar();
                printf("\n");
                printf("PARABENS! Fim de jogo.\n");
                printf("Cada pilha ficou com uma unica cor.\n");
                mostrar_desempenho();
                return 0;
            }
        }
    }

    printf("\nJogo encerrado antes de terminar.\n");
    mostrar_desempenho();
    return 0;
}
