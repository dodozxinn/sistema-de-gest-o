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

        if (scanf("%d", &opcao) != 1) {
            opcao = 0;
            while (getchar() != '\n' && !feof(stdin));
        }

        if (opcao == 1) {
            if (quantidade == MAX) {
                printf("Limite de veiculos atingido.\n");
            } else {
                int repetido;

                do {
                    repetido = 0;
                    printf("ID do veiculo: ");

                    if (scanf("%d", &veiculos[quantidade].id) != 1) {
                        veiculos[quantidade].id = 0;
                        while (getchar() != '\n' && !feof(stdin));
                    }

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

                    if (scanf("%f", &veiculos[quantidade].consumo) != 1) {
                        veiculos[quantidade].consumo = 0;
                        while (getchar() != '\n' && !feof(stdin));
                    }
                    if (veiculos[quantidade].consumo <= 0) {
                        printf("O consumo deve ser maior que zero.\n");
                    }
                } while (veiculos[quantidade].consumo <= 0);

                do {
                    printf("Capacidade em toneladas: ");

                    if (scanf("%f", &veiculos[quantidade].capacidade) != 1) {
                        veiculos[quantidade].capacidade = 0;
                        while (getchar() != '\n' && !feof(stdin));
                    }
                    if (veiculos[quantidade].capacidade <= 0) {
                        printf("A capacidade deve ser maior que zero.\n");
                    }
                } while (veiculos[quantidade].capacidade <= 0);

                printf("Status (0=Disponivel, 1=Em viagem, 2=Manutencao): ");
                if (scanf("%d", &veiculos[quantidade].status) != 1) {
                    veiculos[quantidade].status = -1;
                    while (getchar() != '\n' && !feof(stdin));
                }

                while (veiculos[quantidade].status < 0 ||
                       veiculos[quantidade].status > 2) {
                    printf("Digite 0, 1 ou 2: ");
                    if (scanf("%d", &veiculos[quantidade].status) != 1) {
                        veiculos[quantidade].status = -1;
                        while (getchar() != '\n' && !feof(stdin));
                    }
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
            int id, indice = -1, origem, destino, confirmar;
            float distancia, litros, custo;

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

                    distancia = distancias[origem][destino];
                    litros = distancia / veiculos[indice].consumo;
                    custo = litros * PRECO;

                    printf("\nDistancia: %.2f km\n", distancia);
                    printf("Consumo estimado: %.2f litros\n", litros);
                    printf("Custo estimado: R$ %.2f\n", custo);
                    printf("Confirmar viagem? (1=Sim, 0=Nao): ");
                    scanf("%d", &confirmar);

                    if (confirmar == 1) {
                        veiculos[indice].status = 1;
                        printf("Viagem confirmada!\n");
                    } else {
                        printf("Viagem nao confirmada.\n");
                    }
                }
            }
        }

        else if (opcao == 5) {
            int disponiveis = 0, emViagem = 0, manutencao = 0;
            int maisEficiente = 0;
            float somaCarga = 0;

            if (quantidade == 0) {
                printf("Nenhum veiculo cadastrado.\n");
            } else {

                for (i = 0; i < quantidade; i++) {
                    somaCarga = somaCarga + veiculos[i].capacidade;

                    if (veiculos[i].status == 0) {
                        disponiveis++;
                    } else if (veiculos[i].status == 1) {
                        emViagem++;
                    } else {
                        manutencao++;
                    }

                    if (veiculos[i].consumo > veiculos[maisEficiente].consumo) {
                        maisEficiente = i;
                    }
                }

                printf("\nVeiculo mais eficiente: ID %d, %s (%.2f km/L)\n",
                       veiculos[maisEficiente].id,
                       veiculos[maisEficiente].modelo,
                       veiculos[maisEficiente].consumo);

                printf("Disponiveis: %d (%.1f%%)\n", disponiveis,
                       disponiveis * 100.0 / quantidade);
                printf("Em viagem: %d (%.1f%%)\n", emViagem,
                       emViagem * 100.0 / quantidade);
                printf("Em manutencao: %d (%.1f%%)\n", manutencao,
                       manutencao * 100.0 / quantidade);
                printf("Media da capacidade: %.2f toneladas\n",
                       somaCarga / quantidade);
            }
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
