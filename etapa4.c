#include <stdio.h>

#define MAX 10
#define CIDADES 5

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
    int opcao, i;

    float distancias[CIDADES][CIDADES] = {
        {0, 25, 90, 120, 150},
        {25, 0, 75, 105, 130},
        {90, 75, 0, 140, 110},
        {120, 105, 140, 0, 210},
        {150, 130, 110, 210, 0}
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
            printf("Listagem em construcao.\n");
        }

        else if (opcao == 3) {
            printf("Matriz em construcao.\n");
        }

        else if (opcao == 4) {
            printf("Simulacao em construcao.\n");
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
