/* Compilar: gcc jogo.c -o jogo
   Executar: ./jogo
   Abrir:    http://127.0.0.1:8080
   Terminal: ./jogo terminal
   O visual esta em estilo.css, na mesma pasta. Sem JavaScript. */

#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define MAX_PILHA 4
#define QTD_PILHAS 4
#define QTD_CORES 4
#define POR_COR 3
#define TOTAL_PINOS 12
#define PORTA 8080

typedef struct {
    char itens[MAX_PILHA];
    int topo;
} Pilha;

typedef struct {
    char *s;
    size_t n, cap;
} Buf;

Pilha pilha[QTD_PILHAS], temp[2];
int ntemps, movimentos, jogando, vitoria;
time_t inicio;
const char *aviso;
char CORES[QTD_CORES] = {'V', 'G', 'A', 'M'};
char css_arquivo[512] = "estilo.css";

int vazia(Pilha *p) { return p->topo == -1; }
int cheia(Pilha *p, int cap) { return p->topo + 1 >= cap; }
void inicializar(Pilha *p) { p->topo = -1; }

int push(Pilha *p, char pino, int cap) {
    if (cheia(p, cap)) return 0;
    p->itens[++p->topo] = pino;
    return 1;
}

int pop(Pilha *p, char *pino) {
    if (vazia(p)) return 0;
    *pino = p->itens[p->topo--];
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
    int i, c, k = 0;

    for (c = 0; c < QTD_CORES; c++)
        for (i = 0; i < POR_COR; i++) pinos[k++] = CORES[c];
    embaralhar(pinos, TOTAL_PINOS);
    for (i = 0; i < QTD_PILHAS; i++) inicializar(&pilha[i]);
    inicializar(&temp[0]);
    inicializar(&temp[1]);
    for (i = 0; i < TOTAL_PINOS; i++)
        push(&pilha[i % QTD_PILHAS], pinos[i], MAX_PILHA);
}

int venceu(void) {
    int i, j;
    char cor;

    if (!vazia(&temp[0]) || !vazia(&temp[1])) return 0;
    for (i = 0; i < QTD_PILHAS; i++) {
        if (pilha[i].topo + 1 != POR_COR) return 0;
        cor = pilha[i].itens[0];
        for (j = 1; j <= pilha[i].topo; j++)
            if (pilha[i].itens[j] != cor) return 0;
        for (j = 0; j < i; j++)
            if (pilha[j].itens[0] == cor) return 0;
    }
    return 1;
}

const char *mover(Pilha *origem, Pilha *destino, int cap) {
    char pino;

    if (origem == destino) return "Origem e destino são a mesma pilha.";
    if (vazia(origem)) return "Não há pino para tirar (POP).";
    if (cheia(destino, cap)) {
        return cap == 1 ? "Temporário ocupado. Ele guarda só 1 pino."
                        : "Pilha cheia. Cabe no máximo 4 pinos.";
    }
    pop(origem, &pino);
    push(destino, pino, cap);
    return NULL;
}

int lugar(const char *nome, Pilha **p, int *cap) {
    int ncap;

    if (nome[0] == 'p' && nome[1] >= '1' && nome[1] <= '4' && nome[2] == 0) {
        *p = &pilha[nome[1] - '1'];
        ncap = MAX_PILHA;
    } else if (nome[0] == 't' && nome[1] >= '1' && nome[1] < '1' + ntemps && nome[2] == 0) {
        *p = &temp[nome[1] - '1'];
        ncap = 1;
    } else {
        return 0;
    }
    if (cap) *cap = ncap;
    return 1;
}

void comecar(int nivel) {
    int n = 0;

    ntemps = nivel == 1 ? 2 : nivel == 2 ? 1 : 0;
    do distribuir();
    while (venceu() && ++n < 30);
    movimentos = 0;
    inicio = time(NULL);
    jogando = 1;
    vitoria = 0;
    aviso = NULL;
}

int campo(const char *body, const char *chave, char *out, int n) {
    size_t k = strlen(chave);
    const char *p = body;

    while (*p) {
        if ((p == body || p[-1] == '&') && strncmp(p, chave, k) == 0 && p[k] == '=') {
            int i = 0;
            p += k + 1;
            while (*p && *p != '&' && i < n - 1) out[i++] = *p++;
            out[i] = 0;
            return 1;
        }
        while (*p && *p != '&') p++;
        if (*p == '&') p++;
    }
    out[0] = 0;
    return 0;
}

void processar(const char *body) {
    char a[8], b[8];
    Pilha *origem, *destino;
    int cap;

    if (campo(body, "novo", a, sizeof a)) {
        jogando = 0;
        vitoria = 0;
        aviso = NULL;
        return;
    }
    if (!jogando) {
        if (campo(body, "nivel", a, sizeof a) && a[1] == 0 && a[0] >= '1' && a[0] <= '3')
            comecar(a[0] - '0');
        return;
    }
    if (vitoria) return;
    if (!campo(body, "origem", a, sizeof a) || !campo(body, "destino", b, sizeof b))
        return;
    if (!lugar(a, &origem, NULL) || !lugar(b, &destino, &cap)) {
        aviso = "Escolha uma pilha ou um temporário deste nível.";
        return;
    }
    aviso = mover(origem, destino, cap);
    if (!aviso) {
        movimentos++;
        if (venceu()) vitoria = 1;
    }
}

void add(Buf *b, const char *t) {
    size_t m = strlen(t);
    if (b->n + m + 1 > b->cap) {
        size_t nc = b->cap ? b->cap : 4096;
        char *p;
        while (nc < b->n + m + 1) nc *= 2;
        p = realloc(b->s, nc);
        if (!p) exit(1);
        b->s = p;
        b->cap = nc;
    }
    memcpy(b->s + b->n, t, m + 1);
    b->n += m;
}

void addf(Buf *b, const char *fmt, ...) {
    char tmp[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    add(b, tmp);
}

void html_pino(Buf *b, char cor, int eh_topo) {
    const char *cls = cor == 'V' ? "v" : cor == 'G' ? "g" : cor == 'A' ? "a" : "m";
    addf(b, "<div class=\"pino %s%s\">%c</div>", cls, eh_topo ? " topo" : "", cor);
}

void html_opcoes(Buf *b, const char *nome) {
    int i;
    addf(b, "<select name=\"%s\" id=\"%s\">", nome, nome);
    for (i = 0; i < QTD_PILHAS; i++)
        addf(b, "<option value=\"p%d\">Pilha %d</option>", i + 1, i + 1);
    for (i = 0; i < ntemps; i++)
        addf(b, "<option value=\"t%d\">Temp %d</option>", i + 1, i + 1);
    add(b, "</select>");
}

void pagina(Buf *b) {
    int i, linha;
    long s = jogando ? (long)(time(NULL) - inicio) : 0;
    const char *nivel = ntemps == 2 ? "Fácil" : ntemps == 1 ? "Médio" : "Difícil";

    add(b, "<!DOCTYPE html><html lang=\"pt-BR\"><head><meta charset=\"utf-8\">");
    add(b, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    add(b, "<title>Jogo dos pinos</title><link rel=\"stylesheet\" href=\"/estilo.css\">");
    add(b, "</head><body><main>");
    add(b, "<p class=\"curso\">TADS - Estrutura de Dados</p><h1>Jogo dos pinos</h1>");
    add(b, "<ul class=\"legenda\">");
    add(b, "<li><i class=\"cor v\"></i> V vermelho</li>");
    add(b, "<li><i class=\"cor g\"></i> G verde</li>");
    add(b, "<li><i class=\"cor a\"></i> A azul</li>");
    add(b, "<li><i class=\"cor m\"></i> M amarelo</li></ul>");

    if (!jogando) {
        add(b, "<p class=\"regras\">4 pilhas e 12 pinos, 3 de cada cor. ");
        add(b, "Cada pilha cabe 4. O POP tira o pino do topo e o PUSH coloca no topo. ");
        add(b, "Vence quando cada pilha tiver uma única cor.</p>");
        add(b, "<form method=\"post\" action=\"/\" class=\"niveis\">");
        add(b, "<button class=\"nivel\" name=\"nivel\" value=\"1\"><strong>Fácil</strong><span>Temp 1 e Temp 2</span></button>");
        add(b, "<button class=\"nivel\" name=\"nivel\" value=\"2\"><strong>Médio</strong><span>somente Temp 1</span></button>");
        add(b, "<button class=\"nivel\" name=\"nivel\" value=\"3\"><strong>Difícil</strong><span>sem temporário</span></button>");
        add(b, "</form></main></body></html>");
        return;
    }

    addf(b, "<p class=\"status\"><span>%s</span><span>Tempo %02ld:%02ld</span><span>%d %s</span></p>",
         nivel, s / 60, s % 60, movimentos, movimentos == 1 ? "movimento" : "movimentos");
    add(b, "<div class=\"mesa\">");
    for (i = 0; i < QTD_PILHAS; i++) {
        addf(b, "<section class=\"pilha\"><h2>P%d</h2><div class=\"slots\">", i + 1);
        for (linha = MAX_PILHA - 1; linha >= 0; linha--) {
            if (linha <= pilha[i].topo)
                html_pino(b, pilha[i].itens[linha], linha == pilha[i].topo);
            else
                add(b, "<div class=\"vazio\"></div>");
        }
        addf(b, "</div><p class=\"conta\">%d/4</p></section>", pilha[i].topo + 1);
    }
    add(b, "</div>");

    if (ntemps == 0) {
        add(b, "<p class=\"nota\">Nível difícil: sem temporário.</p>");
    } else {
        add(b, "<div class=\"temps\">");
        for (i = 0; i < ntemps; i++) {
            addf(b, "<section class=\"temp\"><h2>Temp %d</h2><div class=\"slots\">", i + 1);
            if (vazia(&temp[i])) add(b, "<div class=\"vazio\"></div>");
            else html_pino(b, temp[i].itens[temp[i].topo], 1);
            add(b, "</div></section>");
        }
        add(b, "</div>");
    }

    if (vitoria) {
        add(b, "<p class=\"vitoria\">Parabéns! Cada pilha ficou com uma única cor.</p>");
    } else if (aviso) {
        addf(b, "<p class=\"aviso\">%s</p>", aviso);
    }

    if (!vitoria) {
        add(b, "<form method=\"post\" action=\"/\" class=\"jogada\">");
        add(b, "<label>POP de ");
        html_opcoes(b, "origem");
        add(b, "</label><label>PUSH em ");
        html_opcoes(b, "destino");
        add(b, "</label><button type=\"submit\">Mover</button></form>");
    }
    add(b, "<form method=\"post\" action=\"/\"><button class=\"secundario\" name=\"novo\" value=\"1\">Novo jogo</button></form>");
    add(b, "</main></body></html>");
}

void enviar_tudo(int fd, const char *p, size_t n) {
    size_t off = 0;
    while (off < n) {
        ssize_t r = send(fd, p + off, n - off, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            return;
        }
        off += (size_t)r;
    }
}

void responder(int fd, const char *status, const char *tipo, const char *corpo, size_t n) {
    char head[320];
    int h = snprintf(head, sizeof head,
                     "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %zu\r\n"
                     "Connection: close\r\nCache-Control: no-store\r\n\r\n",
                     status, tipo, n);
    enviar_tudo(fd, head, (size_t)h);
    enviar_tudo(fd, corpo, n);
}

void definir_css(const char *argv0) {
    FILE *f = fopen("estilo.css", "rb");
    const char *barra;

    if (f) {
        fclose(f);
        return;
    }
    if (!argv0) return;
    barra = strrchr(argv0, '/');
    if (!barra) return;
    snprintf(css_arquivo, sizeof css_arquivo, "%.*s/estilo.css", (int)(barra - argv0), argv0);
}

void responder_css(int fd) {
    FILE *arq = fopen(css_arquivo, "rb");
    char *texto;
    long n;

    if (!arq) {
        responder(fd, "404 Not Found", "text/plain; charset=utf-8",
                  "estilo.css nao encontrado\n", strlen("estilo.css nao encontrado\n"));
        return;
    }
    fseek(arq, 0, SEEK_END);
    n = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    texto = malloc((size_t)n);
    if (!texto || fread(texto, 1, (size_t)n, arq) != (size_t)n) {
        free(texto);
        fclose(arq);
        responder(fd, "500 Internal Server Error", "text/plain; charset=utf-8",
                  "erro ao ler css\n", strlen("erro ao ler css\n"));
        return;
    }
    fclose(arq);
    responder(fd, "200 OK", "text/css; charset=utf-8", texto, (size_t)n);
    free(texto);
}

void responder_pagina(int fd) {
    Buf b = {0};
    pagina(&b);
    responder(fd, "200 OK", "text/html; charset=utf-8", b.s, b.n);
    free(b.s);
}

void atender(int fd) {
    char buf[8192], metodo[8], caminho[64];
    int lido = 0, head = 0, need = -1;

    while (lido < (int)sizeof buf - 1) {
        int r = recv(fd, buf + lido, sizeof buf - 1 - lido, 0);
        char *fim;
        if (r == 0) break;
        if (r < 0) {
            if (errno == EINTR) continue;
            return;
        }
        lido += r;
        buf[lido] = 0;
        fim = strstr(buf, "\r\n\r\n");
        if (!fim) continue;
        head = (int)(fim - buf) + 4;
        if (need < 0) {
            char *p = buf;
            need = 0;
            while (p < fim) {
                if (strncasecmp(p, "Content-Length:", 15) == 0) {
                    need = atoi(p + 15);
                    if (need < 0) need = 0;
                    if (need > (int)sizeof buf - head - 1) need = (int)sizeof buf - head - 1;
                    break;
                }
                p = strstr(p, "\r\n");
                if (!p || p >= fim) break;
                p += 2;
            }
        }
        if (lido >= head + need) break;
    }
    buf[lido] = 0;
    if (sscanf(buf, "%7s %63s", metodo, caminho) != 2) {
        responder(fd, "400 Bad Request", "text/plain; charset=utf-8", "pedido invalido\n", 16);
        return;
    }
    if (strcmp(metodo, "GET") == 0 && strcmp(caminho, "/estilo.css") == 0) {
        responder_css(fd);
        return;
    }
    if (strcmp(metodo, "POST") == 0 && strcmp(caminho, "/") == 0) {
        const char *red =
            "HTTP/1.1 303 See Other\r\nLocation: /\r\nContent-Length: 0\r\nConnection: close\r\n\r\n";
        if (head > 0 && head <= lido) {
            buf[head + (need > 0 ? need : 0)] = 0;
            processar(buf + head);
        }
        enviar_tudo(fd, red, strlen(red));
        return;
    }
    if (strcmp(metodo, "GET") == 0 && (strcmp(caminho, "/") == 0 || strcmp(caminho, "/index.html") == 0)) {
        responder_pagina(fd);
        return;
    }
    responder(fd, "404 Not Found", "text/plain; charset=utf-8", "nao encontrado\n", strlen("nao encontrado\n"));
}

int ler_int(int *valor) {
    int c;

    if (scanf("%d", valor) == 1) return 1;
    if (feof(stdin)) return 0;
    while ((c = getchar()) != '\n' && c != EOF) ;
    printf("Entrada invalida. Digite um numero.\n");
    return 0;
}

int ler_indice(const char *msg, int eh_temp) {
    int n, lim = eh_temp ? ntemps : QTD_PILHAS;

    printf(msg, lim);
    fflush(stdout);
    if (!ler_int(&n)) return -1;
    if (n >= 1 && n <= lim) return n - 1;
    printf("%s", eh_temp
           ? (ntemps == 1 ? "Nivel medio so tem o Temp1.\n"
                          : "Temporario invalido. Escolha 1 ou 2.\n")
           : "Pilha invalida. Escolha de 1 a 4.\n");
    return -1;
}

int aplicar(Pilha *origem, Pilha *destino, int cap) {
    const char *msg = mover(origem, destino, cap);
    if (!msg) return 1;
    printf("\n%s\n", msg);
    return 0;
}

int jogada(int op) {
    int origem, destino;

    if (op != 1 && ntemps == 0) {
        printf("\nNivel dificil nao usa temporario.\n");
        return 0;
    }
    if (op == 1) {
        destino = ler_indice("PUSH em qual pilha (1 a 4)? ", 0);
        if (destino < 0) return 0;
        origem = ler_indice("POP de qual pilha (1 a 4)? ", 0);
        if (origem < 0) return 0;
        return aplicar(&pilha[origem], &pilha[destino], MAX_PILHA);
    }
    if (op == 2) {
        origem = ler_indice("POP de qual pilha (1 a 4)? ", 0);
        if (origem < 0) return 0;
        destino = ler_indice("PUSH em qual temporario (1 a %d)? ", 1);
        if (destino < 0) return 0;
        return aplicar(&pilha[origem], &temp[destino], 1);
    }
    origem = ler_indice("POP de qual temporario (1 a %d)? ", 1);
    if (origem < 0) return 0;
    destino = ler_indice("PUSH em qual pilha (1 a 4)? ", 0);
    if (destino < 0) return 0;
    return aplicar(&temp[origem], &pilha[destino], MAX_PILHA);
}

void escolher_nivel(void) {
    int op;

    printf("\nTADS - Estrutura de Dados\n"
           "4 pilhas, 12 pinos: V G A M, 3 de cada. Cada pilha cabe 4.\n"
           "Mova pelo topo. ( ) e o pino que o POP tira.\n"
           "Vence quando cada pilha tiver uma unica cor.\n"
           "1 Facil (Temp1 e Temp2)\n"
           "2 Medio (somente Temp1)\n"
           "3 Dificil (sem temporario)\n");
    while (1) {
        printf("Escolha: ");
        fflush(stdout);
        if (!ler_int(&op)) {
            if (feof(stdin)) { ntemps = -1; return; }
            continue;
        }
        if (op == 1) { ntemps = 2; return; }
        if (op == 2) { ntemps = 1; return; }
        if (op == 3) { ntemps = 0; return; }
        printf("Escolha 1, 2 ou 3.\n");
    }
}

void mostrar(void) {
    int linha, i;
    long s = (long)(time(NULL) - inicio);
    const char *nivel = ntemps == 2 ? "Facil" : ntemps == 1 ? "Medio" : "Dificil";

    printf("\n%s  Tempo %02ld:%02ld  Movimentos %d\n",
           nivel, s / 60, s % 60, movimentos);
    for (i = 0; i < QTD_PILHAS; i++) printf("  P%d   ", i + 1);
    printf("\n");
    for (linha = MAX_PILHA - 1; linha >= 0; linha--) {
        for (i = 0; i < QTD_PILHAS; i++) {
            if (linha == pilha[i].topo) printf(" (%c)   ", pilha[i].itens[linha]);
            else if (linha < pilha[i].topo) printf("  %c    ", pilha[i].itens[linha]);
            else printf("  .    ");
        }
        printf("\n");
    }
    for (i = 0; i < QTD_PILHAS; i++) printf(" %d/4   ", pilha[i].topo + 1);
    printf("\n");

    if (ntemps == 0) {
        printf("Temporario: nenhum\n");
    } else {
        for (i = 0; i < ntemps; i++) {
            printf("%sTemp%d ", i ? "  " : "", i + 1);
            if (vazia(&temp[i])) printf("[ vazio ]");
            else printf("[ %c ]", temp[i].itens[temp[i].topo]);
        }
        printf("\n");
    }
    fflush(stdout);
}

void desempenho(void) {
    long s = (long)(time(NULL) - inicio);
    printf("Tempo: %02ld:%02ld\nMovimentos: %d\n", s / 60, s % 60, movimentos);
}

int terminal(void) {
    int op, n = 0;

    escolher_nivel();
    if (ntemps < 0) return 0;

    srand((unsigned)time(NULL));
    do distribuir();
    while (venceu() && ++n < 30);

    movimentos = 0;
    inicio = time(NULL);
    while (1) {
        mostrar();
        printf("\n1 pilha->pilha  2 pilha->temp  3 temp->pilha  0 sair\nOpcao: ");
        fflush(stdout);
        if (!ler_int(&op)) {
            if (feof(stdin)) break;
            continue;
        }
        if (op == 0) break;
        if (op < 1 || op > 3) {
            printf("\nOpcao invalida. Use 1, 2, 3 ou 0.\n");
            continue;
        }
        if (jogada(op)) {
            movimentos++;
            if (venceu()) {
                mostrar();
                printf("\nPARABENS! Fim de jogo.\n"
                       "Cada pilha ficou com uma unica cor.\n");
                desempenho();
                return 0;
            }
        }
    }
    printf("\nJogo encerrado antes de terminar.\n");
    desempenho();
    return 0;
}

int servir(const char *argv0) {
    int servidor, sim = 1;
    struct sockaddr_in end;

    definir_css(argv0);
    signal(SIGPIPE, SIG_IGN);
    srand((unsigned)time(NULL));
    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor < 0) return 1;
    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &sim, sizeof sim);
    memset(&end, 0, sizeof end);
    end.sin_family = AF_INET;
    end.sin_port = htons(PORTA);
    end.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(servidor, (struct sockaddr *)&end, sizeof end) < 0) {
        perror("bind");
        return 1;
    }
    listen(servidor, 16);
    printf("Jogo em http://127.0.0.1:%d\n", PORTA);
    fflush(stdout);
    while (1) {
        int cliente = accept(servidor, NULL, NULL);
        if (cliente < 0) continue;
        atender(cliente);
        close(cliente);
    }
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "terminal") == 0) return terminal();
    return servir(argv[0]);
}
