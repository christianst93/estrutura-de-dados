#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao das Estruturas
typedef struct poltrona
{
    int num;
    char fileira;
    int flag_livre; // 1 = Livre, 0 = Ocupada
} Poltrona;

typedef struct sala
{
    Poltrona poltronas[15];
    int num_sala;
} Sala;

typedef struct data
{
    int dia, mes, ano;
} Data;

typedef struct sessao
{
    char nomeFilme[30];
    Data dataFilme;
    int horaFilme;
    Sala salaReservada;
} Sessao;

// PROTÓTIPOS DAS FUNÇÕES

// Passagem por REFERÊNCIA (Modificam os dados)
void cadastrarPoltrona(Poltrona *p, int num, char fileira) {     

    if (num < 1 || num > 5)
    {
        printf("Numero de poltrona invalido para fileira\n");
        return;
    }
    
    if (fileira < 'a' || fileira > 'c')
    {
        printf("Fileira invalida!\n");
        return;
    }

    p->num = num;
    p->fileira = fileira;
    p->flag_livre = 1;
}

void inicializarSala(Sala *s, int numSala) { 
    s->num_sala = numSala;   
    for (int i = 0; i < 15; i++) {
        s->poltronas[i].flag_livre = 1;
        s->poltronas[i].num = (i % 5) + 1;
        s->poltronas[i].fileira = 'a' + (i / 5);
    }
}

void cadastrarData(Data *d, int dia, int mes, int ano) {
    if (dia < 1 || dia > 31) {
        printf("Dia invalido!\n");
        return;
    }
    if (mes < 1 || mes > 12) {
        printf("Mes invalido!\n");
        return;
    }
    if (mes == 2 && dia > 29) {
        printf("Invalido, fevereiro so pode ter no maximo 29 dias!\n");
        return;
    }
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31) {
        printf("Invalido, este mes so tem 30 dias!\n");
        return;
    }
    if (ano < 0) {
        printf("Ano invalido!\n");
        return;
    }

    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
}

void cadastrarSessao(Sessao *s, char *filme, Data d, int hora, Sala sala) {
    strcpy(s->nomeFilme, filme);
    s->dataFilme = d;
    s->horaFilme = hora;
    s->salaReservada = sala;    
}

void comprarPoltrona(Sessao *s, int posPoltrona) {
    if (posPoltrona < 0 || posPoltrona >= 15)
    {
        printf("\nPoltrona invalida.\n");
        return;
    }
    if (!s->salaReservada.poltronas[posPoltrona].flag_livre)
    {
        printf("\nPoltrona ocupada, escolha outra poltrona.");
        return;
    }
    s->salaReservada.poltronas[posPoltrona].flag_livre = 0;
    printf("\nCompra confirmada!");
}

void cancelarCompra(Sessao *s, int posPoltrona){
    if (posPoltrona < 0 || posPoltrona >= 15)
    {
        printf("\nPoltrona invalida.\n");
        return;
    }
    if (s->salaReservada.poltronas[posPoltrona].flag_livre)
    {
        printf("\nA poltrona ja esta livre.\n");
        return;
    }
    s->salaReservada.poltronas[posPoltrona].flag_livre = 1;
    printf("\nCompra cancelada com sucesso!\n");
}

// Passagem por VALOR (Apenas exibição)
void mostrarPoltrona(Poltrona p) {
    printf("Poltrona [%d] | Fileira [%c] | Livre? [%s]\n", p.num, p.fileira, p.flag_livre ? "Sim" : "Nao");
}

void mostrarMapaSala(Sala s) {
    printf("Sala [%d]\n", s.num_sala);
    for (int i = 0; i < 3; i++)
    {
        printf("Fileira %c: ", 'a' + i);
        for (int j = 0; j < 5; j++)
        {
            Poltrona pol = s.poltronas[i * 5 + j];
            printf("%s", pol.flag_livre ? " [ ] " : " [X] ");
        }
        printf("\n");
    }
}

void mostrarData(Data d) {
    printf("Data: %02d/%02d/%04d\n", d.dia, d.mes, d.ano);
}

void mostrarSessao(Sessao s) {
    printf("\nFilme: %s\n", s.nomeFilme);
    mostrarData(s.dataFilme);
    printf("Hora: %d\n", s.horaFilme);
    printf("Sala: %d\n", s.salaReservada.num_sala);

    mostrarMapaSala(s.salaReservada);
}

int mostrarMenu()
{
    int opcao;
    printf("\n========================================\n");
    printf("     SISTEMA DE CONTROLE DE CINEMA      \n");
    printf("========================================\n");
    printf("1. Listar todas as sessoes\n");
    printf("2. Comprar poltrona (Opcao 7.a)\n");
    printf("3. Cancelar compra de poltrona (Opcao 7.b)\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    while (getchar() != '\n'); 
    return opcao;
}
// Implemente o main() montando o menu interativo com switch-case

int main()
{
    int opcao;
    // 1. Reserva do vetor de 4 sessões no cinema
    Sessao sessoes[4];

    Sessao sessao1, sessao2, sessao3, sessao4;
    Sala sala1, sala2, sala3, sala4;
    Data ontem, hoje, amanha;
    
    Poltrona p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;

    cadastrarPoltrona(&p1, 1, 'a');
    cadastrarPoltrona(&p2, 2, 'a');
    cadastrarPoltrona(&p3, 3, 'a');
    cadastrarPoltrona(&p4, 4, 'a');
    cadastrarPoltrona(&p5, 5, 'a');

    cadastrarPoltrona(&p6, 1, 'b');
    cadastrarPoltrona(&p7, 2, 'b');
    cadastrarPoltrona(&p8, 3, 'b');
    cadastrarPoltrona(&p9, 4, 'b');
    cadastrarPoltrona(&p10, 5, 'b');

    cadastrarPoltrona(&p11, 1, 'c');
    cadastrarPoltrona(&p12, 2, 'c');
    cadastrarPoltrona(&p13, 3, 'c');
    cadastrarPoltrona(&p14, 4, 'c');
    cadastrarPoltrona(&p15, 5, 'c');
    
    inicializarSala(&sala1, 1);
    inicializarSala(&sala2, 2);
    inicializarSala(&sala3, 3);
    inicializarSala(&sala4, 4);

    
    sala1.poltronas[0] = p1;
    sala1.poltronas[1] = p2;
    sala1.poltronas[2] = p3;
    sala1.poltronas[3] = p4;
    sala1.poltronas[4] = p5;
    sala1.poltronas[5] = p6;
    sala1.poltronas[6] = p7;
    sala1.poltronas[7] = p8;
    sala1.poltronas[8] = p9;
    sala1.poltronas[9] = p10;
    sala1.poltronas[10] = p11;
    sala1.poltronas[11] = p12;
    sala1.poltronas[12] = p13;
    sala1.poltronas[13] = p14;
    sala1.poltronas[14] = p15;

    cadastrarData(&ontem, 27, 8, 2026);
    cadastrarData(&hoje, 28, 8, 2026);
    cadastrarData(&amanha, 29, 8, 2026);

    cadastrarSessao(&sessao1, "Batman", ontem, 15, sala1);
    cadastrarSessao(&sessao2, "Vingadores", hoje, 20, sala2);
    cadastrarSessao(&sessao3, "Avatar", amanha, 22, sala3);
    cadastrarSessao(&sessao4, "Corra", amanha, 22, sala4);

    sessoes[0] = sessao1;
    sessoes[1] = sessao2;
    sessoes[2] = sessao3;
    sessoes[3] = sessao4;
    

    do
    {
        opcao = mostrarMenu();
        
        switch (opcao)
        {
            case 1:
                for (int i = 0; i < 4; i++)
                {
                    mostrarSessao(sessoes[i]);
                }                
                break;
            case 2:
                {
                    int numeroSessao, numeroPoltrona, posPoltrona;
                    char fileira;

                    printf("Escolha a sessao (1 a 4): ");
                    scanf("%d", &numeroSessao);
                    
                    if (numeroSessao < 1 || numeroSessao > 4)
                    {
                        printf("Sessao invalida!\n");
                        break;
                    }

                    printf("\nSessao escolhida: %s - Sala %d\n",
                        sessoes[numeroSessao - 1].nomeFilme,
                        sessoes[numeroSessao - 1].salaReservada.num_sala);

                    printf("Escolha a fileira (a, b ou c): ");
                    scanf(" %c", &fileira);

                    if (fileira < 'a' || fileira > 'c')
                    {
                        printf("Fileira invalida! Escolha entre a, b ou c.\n");
                        break;
                    }

                    printf("Escolha a poltrona (1 a 5): ");
                    scanf("%d", &numeroPoltrona);

                    if (numeroPoltrona < 1 || numeroPoltrona > 5)
                    {
                        printf("Poltrona invalida! Escolha entre 1 e 5.\n");
                        break;
                    }

                    posPoltrona = (fileira - 'a') * 5 + numeroPoltrona - 1;
                    mostrarPoltrona(sessoes[numeroSessao - 1].salaReservada.poltronas[posPoltrona]);
                    comprarPoltrona(&sessoes[numeroSessao - 1], posPoltrona);
                    break;
                }
            case 3:
            {
                int numeroSessao, numeroPoltrona;

                printf("Escolha a sessao (1 a 4): ");
                scanf("%d", &numeroSessao);
                if (numeroSessao < 1 || numeroSessao > 4)
                {
                    printf("Sessao invalida!\n");
                    break;
                }

                printf("Escolha a poltrona (1 a 15): ");
                scanf("%d", &numeroPoltrona);
                cancelarCompra(&sessoes[numeroSessao - 1], numeroPoltrona - 1);
                break;
            }
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        
    } while (opcao != 4);
}