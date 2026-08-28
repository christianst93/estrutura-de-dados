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
    printf("Digite o numero da poltrona (ou 0 para cancelar): ");
    scanf("%d", &num);

    if (num == 0) {
        printf("Cadastro cancelado pelo usuario.\n");
        return;
    }

    if (num < 0 || num > 5)
    {
        printf("Numero de poltrona invalido para fileira\n");
        return;
    }

    printf("Escolha a fileira: ");
    scanf(" %c", &fileira);

    if (fileira < 'a' || fileira > 'c')
    {
        printf("Fileira invalida!\n");
        return;
    }

    p->num = num;
    p->fileira = fileira;
}

void inicializarSala(Sala *s, int numSala) { 
    s->num_sala = numSala;   
    for (int i = 0; i < 15; i++) {
        s->poltronas[i].flag_livre = 1;
        s->poltronas[i].num = i + 1;
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
        for (int j = 0; j < 5; j++)
        {
            printf(" [] ");
        }
        
    }
    
}

void mostrarData(Data d) {
    printf("Data: %02d/%02d/%04d\n", d.dia, d.mes, d.ano);
}

void mostrarSessao(Sessao s) {
    printf("\nFilme: %s\n", s.nomeFilme);
    printf("Data: %d/%d/%d\n", s.dataFilme.dia, s.dataFilme.mes, s.dataFilme.ano);
    printf("Hora: %d\n", s.horaFilme);
    printf("Sala: %d\n", s.salaReservada.num_sala);
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

    inicializarSala(&sala1, 1);
    inicializarSala(&sala2, 2);
    inicializarSala(&sala3, 3);
    inicializarSala(&sala4, 4);

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

                printf("\nSessao escolhida: %s - Sala %d\n",
                    sessoes[numeroSessao - 1].nomeFilme,
                    sessoes[numeroSessao - 1].salaReservada.num_sala);

                printf("Escolha a fileira (a, b ou c): ");
                scanf(" %c", &fileira);

                printf("Escolha a poltrona (1 a 5): ");
                scanf("%d", &numeroPoltrona);

                posPoltrona = (fileira - 'a') * 5 + numeroPoltrona - 1;
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