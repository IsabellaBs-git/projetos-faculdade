#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

int main() {
    // Declaração e inicialização do tabuleiro
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa todas as posições com 0 (água)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Declaração dos navios (valor 3 representa parte do navio)
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO]   = {3, 3, 3};
    int navioDiagonalDesc[TAM_NAVIO] = {3, 3, 3};
    int navioDiagonalAsc[TAM_NAVIO]  = {3, 3, 3};

    // Coordenadas iniciais dos navios (sem input do usuário)
    int linhaH = 1, colunaH = 2;  // navio horizontal
    int linhaV = 4, colunaV = 7;  // navio vertical
    int linhaDDesc = 5, colunaDDesc = 1; // navio diagonal descendente
    int linhaDAsc = 2, colunaDAsc = 8;   // navio diagonal ascendente

    // Variável para controle de sobreposição
    int sobreposicao = 0;

    // Verificação de limites e sobreposição para navio horizontal
    if (colunaH + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio horizontal fora dos limites.\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaH][colunaH + i] != 0) {
            sobreposicao = 1;
            break;
        }
    }
    if (!sobreposicao) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
        }
    } else {
        printf("Erro: sobreposição no navio horizontal.\n");
        return 1;
    }

    // Verificação de limites e sobreposição para navio vertical
    sobreposicao = 0;
    if (linhaV + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio vertical fora dos limites.\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaV + i][colunaV] != 0) {
            sobreposicao = 1;
            break;
        }
    }
    if (!sobreposicao) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaV + i][colunaV] = navioVertical[i];
        }
    } else {
        printf("Erro: sobreposição no navio vertical.\n");
        return 1;
    }

    // Verificação de limites e sobreposição para navio diagonal descendente (linha e coluna aumentam)
    sobreposicao = 0;
    if (linhaDDesc + TAM_NAVIO > TAM_TABULEIRO || colunaDDesc + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio diagonal descendente fora dos limites.\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaDDesc + i][colunaDDesc + i] != 0) {
            sobreposicao = 1;
            break;
        }
    }
    if (!sobreposicao) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaDDesc + i][colunaDDesc + i] = navioDiagonalDesc[i];
        }
    } else {
        printf("Erro: sobreposição no navio diagonal descendente.\n");
        return 1;
    }

    // Verificação de limites e sobreposição para navio diagonal ascendente (linha aumenta, coluna diminui)
    sobreposicao = 0;
    if (linhaDAsc + TAM_NAVIO > TAM_TABULEIRO || colunaDAsc - (TAM_NAVIO - 1) < 0) {
        printf("Erro: navio diagonal ascendente fora dos limites.\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaDAsc + i][colunaDAsc - i] != 0) {
            sobreposicao = 1;
            break;
        }
    }
    if (!sobreposicao) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaDAsc + i][colunaDAsc - i] = navioDiagonalAsc[i];
        }
    } else {
        printf("Erro: sobreposição no navio diagonal ascendente.\n");
        return 1;
    }

    // Impressão do tabuleiro
    printf("Tabuleiro com os navios posicionados:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
