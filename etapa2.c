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

    float distancias[CIDADES][CIDADES] = {
        {0, 25, 90, 120, 150},
        {25, 0, 75, 105, 130},
        {90, 75, 0, 140, 110},
        {120, 105, 140, 0, 210},
        {150, 130, 110, 210, 0}
    };

    return 0;
}
