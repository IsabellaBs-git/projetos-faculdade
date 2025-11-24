#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------
// STRUCT DO TERRITÓRIO
// -------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -------------------------------------------
// ATRIBUI UMA MISSÃO ALEATÓRIA AO JOGADOR
// -------------------------------------------
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;          // Sorteia uma missão
    strcpy(destino, missoes[indice]);            // Copia para o destino
}

// -------------------------------------------
// EXIBE A MISSÃO (passagem por valor)
// -------------------------------------------
void exibirMissao(char* missao) {
    printf("Sua missão é:\n-> %s\n\n", missao);
}

// -------------------------------------------
// FUNÇÃO DE ATAQUE
// -------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Você não pode atacar um território da mesma cor!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nAtaque de %s (%s) contra %s (%s)\n", 
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    printf("Dado atacante: %d\n", dadoAtacante);
    printf("Dado defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu! Tropas transferidas.\n");

        defensor->tropas = atacante->tropas / 2;     // Metade das tropas
        strcpy(defensor->cor, atacante->cor);        // Conquista
    } else {
        printf("Defensor venceu! Atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

// -------------------------------------------
// VERIFICA SE UMA MISSÃO FOI CUMPRIDA
// (Regra simples para demonstração)
// -------------------------------------------
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // MISSÃO 1: conquistar 1 território AZUL
    if (strcmp(missao, "Conquistar um territorio azul") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                return 1;
        }
    }

    // MISSÃO 2: eliminar todas as tropas VERMELHAS
    if (strcmp(missao, "Eliminar tropas vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }

    // MISSÃO 3: ter um território com 10 tropas
    if (strcmp(missao, "Acumular 10 tropas em um territorio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10)
                return 1;
        }
    }

    // Regra padrão
    return 0;
}

// -------------------------------------------
// EXIBE MAPA
// -------------------------------------------
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n----- MAPA -----\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio: %-12s Cor: %-8s Tropas: %d\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("----------------\n\n");
}

// -------------------------------------------
// FUNÇÃO PARA LIBERAR MEMÓRIA
// -------------------------------------------
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

// -------------------------------------------
// MAIN
// -------------------------------------------
int main() {
    srand(time(NULL));

    // ---------------------------
    // VETOR DE MISSÕES
    // ---------------------------
    char* missoes[] = {
        "Conquistar um territorio azul",
        "Eliminar tropas vermelhas",
        "Acumular 10 tropas em um territorio",
        "Ter mais tropas que todos os inimigos",
        "Conquistar 3 territorios diferentes"
    };
    int totalMissoes = 5;

    // ---------------------------
    // ALOCAÇÃO DO MAPA
    // ---------------------------
    Territorio* mapa = malloc(3 * sizeof(Territorio));

    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "vermelho");
    mapa[0].tropas = 5;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "azul");
    mapa[1].tropas = 3;

    strcpy(mapa[2].nome, "Chile");
    strcpy(mapa[2].cor, "amarelo");
    mapa[2].tropas = 4;

    // ---------------------------
    // MISSÃO DO JOGADOR (malloc)
    // ---------------------------
    char* missaoJogador = malloc(200 * sizeof(char));

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    printf("\n=== BEM-VINDO AO WAR COM MISSÕES ===\n\n");
    exibirMissao(missaoJogador);

    // ---------------------------
    // SIMULAÇÃO DO JOGO
    // ---------------------------
    int rodada = 1;
    while (1) {
        printf("\n==== RODADA %d ====\n", rodada);

        exibirMapa(mapa, 3);

        printf("Simulando ataque...\n");
        atacar(&mapa[0], &mapa[1]);  // ataque de exemplo

        if (verificarMissao(missaoJogador, mapa, 3)) {
            printf("\n****************************************\n");
            printf(" PARABÉNS! VOCÊ CUMPRIU SUA MISSÃO!\n");
            printf(" MISSÃO: %s\n", missaoJogador);
            printf("****************************************\n");
            break;
        }

        rodada++;
        if (rodada > 10) break; // limite para não rodar infinito
    }

    // ---------------------------
    // LIBERA MEMÓRIA
    // ---------------------------
    liberarMemoria(mapa, missaoJogador);

    return 0;
}
