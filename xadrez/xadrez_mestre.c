#include <stdio.h>

// Função recursiva para o movimento da Torre (direita)
void moverTorre(int casasRestantes) {
    if (casasRestantes <= 0) return;
    printf("Direita\n");
    moverTorre(casasRestantes - 1);
}

// Função recursiva para o movimento da Rainha (esquerda)
void moverRainha(int casasRestantes) {
    if (casasRestantes <= 0) return;
    printf("Esquerda\n");
    moverRainha(casasRestantes - 1);
}

// Função recursiva para o movimento do Bispo (diagonal cima-direita)
void moverBispoRecursivo(int casasRestantes) {
    if (casasRestantes <= 0) return;
    printf("Cima Direita\n");
    moverBispoRecursivo(casasRestantes - 1);
}

// Movimento do Bispo com loops aninhados (horizontal e vertical)
void moverBispoComLoops(int casas) {
    printf("\nMovimento do Bispo (com loops aninhados):\n");
    for (int i = 1; i <= casas; i++) { // movimento vertical (cima)
        for (int j = 1; j <= 1; j++) { // movimento horizontal (direita)
            printf("Cima Direita\n");
        }
    }
}

// Movimento complexo do Cavalo (2 para cima, 1 para direita)
void moverCavalo() {
    int movimentosVerticais = 2;
    int movimentosHorizontais = 1;

    printf("\nMovimento do Cavalo (em 'L': 2 para Cima, 1 para Direita):\n");

    // Primeiro loop: 2 movimentos para cima
    for (int i = 0; i < movimentosVerticais; i++) {
        printf("Cima\n");
    }

    // Segundo movimento: 1 para a direita
    for (int j = 0; j < movimentosHorizontais; j++) {
        printf("Direita\n");
    }
}

int main() {
    int casasTorre = 5;
    int casasBispo = 5;
    int casasRainha = 8;

    // TORRE com recursividade
    printf("Movimento da Torre (recursivo - 5 casas para a Direita):\n");
    moverTorre(casasTorre);

    // BISPO com recursividade
    printf("\nMovimento do Bispo (recursivo - 5 casas na Diagonal Cima Direita):\n");
    moverBispoRecursivo(casasBispo);

    // BISPO com loops aninhados
    moverBispoComLoops(casasBispo);

    // RAINHA com recursividade
    printf("\nMovimento da Rainha (recursivo - 8 casas para a Esquerda):\n");
    moverRainha(casasRainha);

    // CAVALO com loops aninhados e condições
    moverCavalo();

    return 0;
}
