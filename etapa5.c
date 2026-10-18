#include <stdio.h>

#define MAX 10
#define CIDADES 5
#define PRECO 5.80

struct Veiculo {
    int id;
    char placa[8];
    char modelo[30];
    float consumo;
    float capacidade;
    int status;
};

int main() {

    struct Veiculo veiculos[MAX];

    int quantidade = 0;
    int opcao, i, j;

    float distancias[CIDADES][CIDADES] = {
        {0, 25, 90, 120, 150},
        {25, 0, 75, 105, 130},
        {90, 75, 0, 140, 110},
        {120, 105, 140, 0, 210},
        {150, 130, 110, 210, 0}
    };

    char cidades[CIDADES][20] = {
        "Dourados", "Itapora", "Maracaju", "Ponta_Pora", "Navirai"
    };

    do {
        printf("\n===== SISTEMA DE GESTAO DE FROTA =====\n");
        printf("1 - Cadastrar veiculo\n");
        printf("2 - Listar veiculos\n");
        printf("3 - Ver matriz de distancias\n");
        printf("4 - Simular viagem\n");
        printf("5 - Relatorio da frota\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (quantidade == MAX) {
                printf("Limite de veiculos atingido.\n");
            } else {
                int repetido;

                do {
                    repetido = 0;
                    printf("ID do veiculo: ");
                    scanf("%d", &veiculos[quantidade].id);

                    for (i = 0; i < quantidade; i++) {
                        if (veiculos[i].id == veiculos[quantidade].id) {
                            repetido = 1;
                        }
                    }

                    if (veiculos[quantidade].id <= 0 || repetido == 1) {
                        printf("ID invalido ou ja cadastrado. Tente novamente.\n");
                    }
                } while (veiculos[quantidade].id <= 0 || repetido == 1);

                printf("Placa (sem espacos): ");
                scanf("%7s", veiculos[quantidade].placa);

                printf("Modelo (use _ no lugar de espacos): ");
                scanf("%29s", veiculos[quantidade].modelo);

                do {
                    printf("Consumo em km por litro: ");
                    scanf("%f", &veiculos[quantidade].consumo);
                    if (veiculos[quantidade].consumo <= 0) {
                        printf("O consumo deve ser maior que zero.\n");
                    }
                } while (veiculos[quantidade].consumo <= 0);

                do {
                    printf("Capacidade em toneladas: ");
                    scanf("%f", &veiculos[quantidade].capacidade);
                    if (veiculos[quantidade].capacidade <= 0) {
                        printf("A capacidade deve ser maior que zero.\n");
                    }
                } while (veiculos[quantidade].capacidade <= 0);

                printf("Status (0=Disponivel, 1=Em viagem, 2=Manutencao): ");
                scanf("%d", &veiculos[quantidade].status);

                while (veiculos[quantidade].status < 0 ||
                       veiculos[quantidade].status > 2) {
                    printf("Digite 0, 1 ou 2: ");
                    scanf("%d", &veiculos[quantidade].status);
                }

                quantidade++;
                printf("Veiculo cadastrado!\n");
            }
        }

        else if (opcao == 2) {
            if (quantidade == 0) {
                printf("Nenhum veiculo cadastrado.\n");
            } else {
                printf("\nID   Placa    Modelo          Consumo  Carga  Status\n");
                for (i = 0; i < quantidade; i++) {
                    printf("%-4d %-8s %-15s %-7.2f %-6.2f ",
                           veiculos[i].id, veiculos[i].placa,
                           veiculos[i].modelo, veiculos[i].consumo,
                           veiculos[i].capacidade);

                    if (veiculos[i].status == 0) {
                        printf("Disponivel\n");
                    } else if (veiculos[i].status == 1) {
                        printf("Em viagem\n");
                    } else {
                        printf("Manutencao\n");
                    }
                }
            }
        }

        else if (opcao == 3) {
            printf("\nMatriz de distancias (km)\n");
            printf("     ");
            for (i = 0; i < CIDADES; i++) {
                printf("%-12d", i);
            }
            printf("\n");

            for (i = 0; i < CIDADES; i++) {
                printf("%-3d  ", i);
                for (j = 0; j < CIDADES; j++) {
                    printf("%-12.0f", distancias[i][j]);
                }
                printf("\n");
            }

            printf("Cidades:\n");
            for (i = 0; i < CIDADES; i++) {
                printf("%d - %s\n", i, cidades[i]);
            }

            printf("Deseja alterar uma distancia? (1=Sim, 0=Nao): ");
            scanf("%d", &j);

            if (j == 1) {
                int origem, destino;
                float novaDistancia;

                printf("Indice da origem: ");
                scanf("%d", &origem);
                printf("Indice do destino: ");
                scanf("%d", &destino);

                if (origem >= 0 && origem < CIDADES &&
                    destino >= 0 && destino < CIDADES && origem != destino) {
                    printf("Nova distancia (maior que zero): ");
                    scanf("%f", &novaDistancia);

                    if (novaDistancia > 0) {

                        distancias[origem][destino] = novaDistancia;
                        distancias[destino][origem] = novaDistancia;
                        printf("Distancia alterada!\n");
                    } else {
                        printf("Distancia invalida.\n");
                    }
                } else {
                    printf("Indices invalidos.\n");
                }
            }
        }

        else if (opcao == 4) {
            int id, indice = -1, origem, destino;

            printf("ID do veiculo: ");
            scanf("%d", &id);

            for (i = 0; i < quantidade; i++) {
                if (veiculos[i].id == id) {
                    indice = i;
                }
            }

            if (indice == -1) {
                printf("Veiculo nao encontrado.\n");
            } else if (veiculos[indice].status != 0) {
                printf("O veiculo nao esta disponivel.\n");
            } else {
                printf("Cidade de origem (0 a 4): ");
                scanf("%d", &origem);
                printf("Cidade de destino (0 a 4): ");
                scanf("%d", &destino);

                if (origem < 0 || origem >= CIDADES ||
                    destino < 0 || destino >= CIDADES || origem == destino) {
                    printf("Cidades invalidas.\n");
                } else if (distancias[origem][destino] <= 0) {
                    printf("Nao existe rota direta entre essas cidades.\n");
                } else {
                    printf("Rota valida! Falta calcular o custo.\n");
                }
            }
        }

        else if (opcao == 5) {
            printf("Relatorio em construcao.\n");
        }

        else if (opcao == 6) {
            printf("Programa encerrado.\n");
        }

        else {
            printf("Opcao invalida.\n");
        }

    } while (opcao != 6);

    return 0;
}
