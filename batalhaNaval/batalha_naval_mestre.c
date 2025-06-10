#include <stdio.h>

#define TAM_TAB 10     // Tamanho do tabuleiro
#define TAM_HAB 5      // Tamanho das matrizes de habilidade

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Adiciona alguns navios como exemplo (valor 3)
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[6][5] = 3;
}

// Imprime o tabuleiro com a legenda esperada
void imprimirTabuleiro(int tabuleiro[TAM_TAB][TAM_TAB]) {
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

// Cria a matriz de habilidade Cone (triângulo invertido)
void construirHabilidadeCone(int habilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= centro - i && j <= centro + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade Cruz (em formato de "+")
void construirHabilidadeCruz(int habilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == centro || j == centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade Octaedro (em losango)
void construirHabilidadeOctaedro(int habilidade[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if ((i + j >= centro) && (i + j <= centro * 3) && (j - i <= centro) && (i - j <= centro))
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Aplica uma matriz de habilidade no tabuleiro a partir de um ponto de origem
void aplicarHabilidade(int tabuleiro[TAM_TAB][TAM_TAB], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;

                // Garante que estamos dentro do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM_TAB && colunaTab >= 0 && colunaTab < TAM_TAB) {
                    // Se não for navio (3), marca como área afetada (5)
                    if (tabuleiro[linhaTab][colunaTab] != 3) {
                        tabuleiro[linhaTab][colunaTab] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB];
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // ------------------------------
    // Exibe tabuleiro com habilidade Cone
    construirHabilidadeCone(cone);
    aplicarHabilidade(tabuleiro, cone, 2, 2);  // Ponto de origem
    printf("Exemplo de saída de habilidade em cone:\n\n");
    imprimirTabuleiro(tabuleiro);

    // Reinicializa tabuleiro
    inicializarTabuleiro(tabuleiro);

    // ------------------------------
    // Exibe tabuleiro com habilidade Cruz
    construirHabilidadeCruz(cruz);
    aplicarHabilidade(tabuleiro, cruz, 5, 5);  // Ponto de origem
    printf("Exemplo de saída de habilidade em cruz:\n\n");
    imprimirTabuleiro(tabuleiro);

    // Reinicializa tabuleiro
    inicializarTabuleiro(tabuleiro);

    // ------------------------------
    // Exibe tabuleiro com habilidade Octaedro
    construirHabilidadeOctaedro(octaedro);
    aplicarHabilidade(tabuleiro, octaedro, 5, 5);  // Ponto de origem
    printf("Exemplo de saída de habilidade em octaedro:\n\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
