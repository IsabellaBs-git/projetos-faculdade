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

    // Declaração dos navios (valores representando partes do navio)
    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO] = {3, 3, 3};

    // Coordenadas iniciais dos navios (sem input do usuário)
    int linhaH = 2, colunaH = 4;  // início do navio horizontal
    int linhaV = 5, colunaV = 7;  // início do navio vertical

    // Verificação de limites do tabuleiro
    if (colunaH + TAM_NAVIO <= TAM_TABULEIRO && linhaV + TAM_NAVIO <= TAM_TABULEIRO) {
        // Verificação de sobreposição antes de posicionar
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] != 0 || tabuleiro[linhaV + i][colunaV] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            // Posicionamento do navio horizontal
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
            }

            // Posicionamento do navio vertical
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = navioVertical[i];
            }

            // Impressão do tabuleiro
            printf("Tabuleiro com os navios posicionados:\n\n");
            for (int i = 0; i < TAM_TABULEIRO; i++) {
                for (int j = 0; j < TAM_TABULEIRO; j++) {
                    printf("%d ", tabuleiro[i][j]);
                }
                printf("\n");
            }
        } else {
            printf("Erro: os navios se sobrepõem. Altere as coordenadas.\n");
        }
    } else {
        printf("Erro: coordenadas inválidas para o tamanho dos navios.\n");
    }

    return 0;
}
