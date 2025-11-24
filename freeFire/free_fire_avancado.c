#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// Struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ---------------- FUNÇÕES DE APOIO ----------------

// Remove o '\n' deixado pelo fgets
void limparNovaLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Mostra vetor de componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// -------------- BUBBLE SORT (por nome) --------------

long long bubbleSortNome(Componente v[], int n) {
    long long comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
    return comparacoes;
}

// ----------- INSERTION SORT (por tipo) --------------

long long insertionSortTipo(Componente v[], int n) {
    long long comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;

            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
    return comparacoes;
}

// ---------- SELECTION SORT (por prioridade) ----------

long long selectionSortPrioridade(Componente v[], int n) {
    long long comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;

            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            Componente aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }

    return comparacoes;
}

// ---------------- BUSCA BINÁRIA (por nome) ----------------

int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }

    return -1;
}

// ---------------------- MAIN ----------------------

int main() {
    Componente comp[MAX];
    int n, opcao;
    int ordenadoPorNome = 0;  // controle p/ permitir busca binária

    printf("Quantos componentes deseja cadastrar? (max 20): ");
    scanf("%d", &n);
    getchar();  // consome o '\n'

    for (int i = 0; i < n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);

        printf("Nome: ");
        fgets(comp[i].nome, sizeof(comp[i].nome), stdin);
        limparNovaLinha(comp[i].nome);

        printf("Tipo: ");
        fgets(comp[i].tipo, sizeof(comp[i].tipo), stdin);
        limparNovaLinha(comp[i].tipo);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &comp[i].prioridade);
        getchar();
    }

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort por Nome\n");
        printf("2 - Insertion Sort por Tipo\n");
        printf("3 - Selection Sort por Prioridade\n");
        printf("4 - Busca Binária por Nome (apenas após ordenação por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            clock_t inicio = clock();
            long long compCount = bubbleSortNome(comp, n);
            clock_t fim = clock();

            ordenadoPorNome = 1;

            printf("\nOrdenado por NOME!\n");
            mostrarComponentes(comp, n);
            printf("\nComparações: %lld\n", compCount);
            printf("Tempo: %.6f segundos\n",
                   (double)(fim - inicio) / CLOCKS_PER_SEC);
        }

        else if (opcao == 2) {
            clock_t inicio = clock();
            long long compCount = insertionSortTipo(comp, n);
            clock_t fim = clock();

            ordenadoPorNome = 0;

            printf("\nOrdenado por TIPO!\n");
            mostrarComponentes(comp, n);
            printf("\nComparações: %lld\n", compCount);
            printf("Tempo: %.6f segundos\n",
                   (double)(fim - inicio) / CLOCKS_PER_SEC);
        }

        else if (opcao == 3) {
            clock_t inicio = clock();
            long long compCount = selectionSortPrioridade(comp, n);
            clock_t fim = clock();

            ordenadoPorNome = 0;

            printf("\nOrdenado por PRIORIDADE!\n");
            mostrarComponentes(comp, n);
            printf("\nComparações: %lld\n", compCount);
            printf("Tempo: %.6f segundos\n",
                   (double)(fim - inicio) / CLOCKS_PER_SEC);
        }

        else if (opcao == 4) {
            if (!ordenadoPorNome) {
                printf("\nVocê deve ordenar por NOME antes da busca binária!\n");
            } else {
                char chave[30];
                printf("\nDigite o nome a buscar: ");
                fgets(chave, sizeof(chave), stdin);
                limparNovaLinha(chave);

                int pos = buscaBinariaPorNome(comp, n, chave);

                if (pos >= 0) {
                    printf("\nComponente encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                           comp[pos].nome, comp[pos].tipo, comp[pos].prioridade);
                } else {
                    printf("\nComponente NÃO encontrado.\n");
                }
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando...\n");
    return 0;
}
