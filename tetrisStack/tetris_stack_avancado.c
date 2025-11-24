/*
  Gerenciador de Peças
  - Fila circular com capacidade 5 (mantém-se cheia quando possível)
  - Pilha com capacidade 3 (reserva)
  - Peças geradas automaticamente por gerarPeca()
  - Operações:
      1 - Jogar peça da frente da fila (dequeue)
      2 - Enviar peça da frente da fila para a pilha de reserva (push)
      3 - Usar peça da pilha de reserva (pop)
      4 - Trocar peça da frente da fila com o topo da pilha
      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha (se ambos tiverem >= 3)
      6 - Exibir estado atual
      0 - Sair
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* --- Configurações --- */
#define FILA_CAP 5
#define PILHA_CAP 3

/* --- Struct Peça --- */
typedef struct {
    char tipo;   // 'I', 'O', 'T', 'L'
    int id;      // id único
} Peca;

/* --- Fila circular --- */
typedef struct {
    Peca dados[FILA_CAP];
    int head;   // índice do primeiro elemento
    int cnt;    // quantidade atual
} Fila;

/* --- Pilha --- */
typedef struct {
    Peca dados[PILHA_CAP];
    int top;    // índice do topo: -1 quando vazia
} Pilha;

/* --- Protótipos --- */
Peca gerarPeca();
void inicializarFila(Fila *f);
void inicializarPilha(Pilha *p);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
int enqueue(Fila *f, Peca pc);
int dequeue(Fila *f, Peca *pc);
int push(Pilha *p, Peca pc);
int pop(Pilha *p, Peca *pc);
void exibirEstado(Fila *f, Pilha *p);
void trocarFrenteComTopo(Fila *f, Pilha *p);
void trocaTriple(Fila *f, Pilha *p);
void gerarEEnfileirarSePossivel(Fila *f);

/* --- Contador global de IDs --- */
int contadorID = 0;

/* --- Gera peça aleatória com id único --- */
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int idx = rand() % 4;
    p.tipo = tipos[idx];
    p.id = contadorID++;
    return p;
}

/* --- Inicializações --- */
void inicializarFila(Fila *f) {
    f->head = 0;
    f->cnt = 0;
}

void inicializarPilha(Pilha *p) {
    p->top = -1;
}

/* --- Status fila/pilha --- */
int filaVazia(Fila *f) {
    return f->cnt == 0;
}
int filaCheia(Fila *f) {
    return f->cnt == FILA_CAP;
}
int pilhaVazia(Pilha *p) {
    return p->top == -1;
}
int pilhaCheia(Pilha *p) {
    return p->top == PILHA_CAP - 1;
}

/* --- Enfileirar (circular) --- */
int enqueue(Fila *f, Peca pc) {
    if (filaCheia(f)) return 0;
    int tailIndex = (f->head + f->cnt) % FILA_CAP;
    f->dados[tailIndex] = pc;
    f->cnt++;
    return 1;
}

/* --- Desenfileirar (devolve peça removida por ponteiro) --- */
int dequeue(Fila *f, Peca *pc) {
    if (filaVazia(f)) return 0;
    *pc = f->dados[f->head];
    f->head = (f->head + 1) % FILA_CAP;
    f->cnt--;
    return 1;
}

/* --- Push na pilha --- */
int push(Pilha *p, Peca pc) {
    if (pilhaCheia(p)) return 0;
    p->top++;
    p->dados[p->top] = pc;
    return 1;
}

/* --- Pop da pilha --- */
int pop(Pilha *p, Peca *pc) {
    if (pilhaVazia(p)) return 0;
    *pc = p->dados[p->top];
    p->top--;
    return 1;
}

/* --- Exibir estado (formato amigável) --- */
void exibirEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n\n");

    // Fila (mostrando do front para o final)
    printf("Fila de peças:\n[ ");
    for (int i = 0; i < f->cnt; i++) {
        int idx = (f->head + i) % FILA_CAP;
        printf("[%c %d] ", f->dados[idx].tipo, f->dados[idx].id);
    }
    printf("]\n");

    // Pilha (topo -> base)
    printf("Pilha de reserva (Topo -> base):\n( ");
    for (int i = p->top; i >= 0; i--) {
        printf("[%c %d] ", p->dados[i].tipo, p->dados[i].id);
    }
    printf(")\n\n");
}

/* --- Trocar peça da frente da fila com topo da pilha --- */
void trocarFrenteComTopo(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Nada para trocar.\n");
        return;
    }
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nada para trocar.\n");
        return;
    }
    int frenteIdx = f->head;
    Peca tmp = f->dados[frenteIdx];
    f->dados[frenteIdx] = p->dados[p->top];
    p->dados[p->top] = tmp;
    printf("Troca realizada entre frente da fila e topo da pilha.\n");
}

/* --- Troca múltipla: alterna as 3 primeiras da fila com as 3 da pilha
       Condição: fila deve ter >=3 e pilha >=3 */
void trocaTriple(Fila *f, Pilha *p) {
    if (f->cnt < 3 || (p->top + 1) < 3) {
        printf("Operação inválida: é necessário que ambas tenham ao menos 3 peças.\n");
        return;
    }

    // Implementação que preserva ordem conforme exemplo:
    // Trocar os 3 primeiros da fila (f0,f1,f2) com as 3 da pilha (top->base: s2,s1,s0)
    // Desejamos que após a troca a fila tenha [s2, s1, s0, ...] e a pilha tenha top->base [f2, f1, f0]

    // Fazemos as trocas começando pelo elemento da fila de índice 2 (terceiro),
    // trocando com o topo da pilha, depois fila idx1 com pilha top-1, etc.
    for (int i = 0; i < 3; i++) {
        int filaIdx = (f->head + (2 - i)) % FILA_CAP; // 2,1,0 (ordem)
        int pilhaIdx = p->top - i;                    // top, top-1, top-2
        Peca tmp = f->dados[filaIdx];
        f->dados[filaIdx] = p->dados[pilhaIdx];
        p->dados[pilhaIdx] = tmp;
    }
    printf("Troca múltipla (3 primeiros da fila <-> 3 da pilha) realizada.\n");
}

/* --- Gera nova peça e enfileira se houver espaço --- */
void gerarEEnfileirarSePossivel(Fila *f) {
    if (!filaCheia(f)) {
        Peca nova = gerarPeca();
        enqueue(f, nova);
        // nota: normalmente queremos manter fila cheia sempre que possível
    }
}

/* --- Função para preencher inicialmente a fila até capacidade --- */
void preencherFilaInicial(Fila *f) {
    while (!filaCheia(f)) {
        Peca p = gerarPeca();
        enqueue(f, p);
    }
}

/* --- Programa principal com menu --- */
int main() {
    srand((unsigned int)time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // preencher fila inicialmente com 5 peças
    preencherFilaInicial(&fila);

    int opcao;
    printf("=== Gerenciador de Peças ===\n");
    printf("Fila circular (cap %d) + Pilha (cap %d)\n", FILA_CAP, PILHA_CAP);

    do {
        exibirEstado(&fila, &pilha);

        printf("Opções:\n");
        printf("1 - Jogar peça da frente da fila (dequeue)\n");
        printf("2 - Enviar peça da frente da fila para a pilha de reserva (push)\n");
        printf("3 - Usar peça da pilha de reserva (pop)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("6 - Exibir estado atual\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            // Limpa entrada em caso de erro
            while (getchar() != '\n');
            opcao = -1;
        }
        // consome eventual newline
        while (getchar() != '\n');

        if (opcao == 1) {
            // Jogar peça: remove frente da fila (peça sai do jogo)
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                // após remoção, gerar nova peça para manter fila cheia (quando possível)
                gerarEEnfileirarSePossivel(&fila);
            } else {
                printf("Fila vazia: nada para jogar.\n");
            }
        }
        else if (opcao == 2) {
            // Reservar peça: mover frente da fila para topo da pilha, se houver espaço
            if (pilhaCheia(&pilha)) {
                printf("Pilha cheia: não é possível reservar mais peças.\n");
            } else {
                Peca mover;
                if (dequeue(&fila, &mover)) {
                    if (push(&pilha, mover)) {
                        printf("Peça reservada: [%c %d]\n", mover.tipo, mover.id);
                        // após remoção, gerar nova peça para manter fila cheia (quando possível)
                        gerarEEnfileirarSePossivel(&fila);
                    } else {
                        // push falhou (teoricamente não chega aqui porque checamos antes)
                        printf("Erro ao reservar peça.\n");
                        // reenfileira para não perder a peça
                        enqueue(&fila, mover);
                    }
                } else {
                    printf("Fila vazia: nada para reservar.\n");
                }
            }
        }
        else if (opcao == 3) {
            // Usar peça reservada: pop da pilha (peça sai do jogo)
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("Peça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
                // Note: não retornamos a peça à fila (removida do jogo)
            } else {
                printf("Pilha vazia: nenhuma peça para usar.\n");
            }
        }
        else if (opcao == 4) {
            trocarFrenteComTopo(&fila, &pilha);
        }
        else if (opcao == 5) {
            trocaTriple(&fila, &pilha);
        }
        else if (opcao == 6) {
            // exibição já é feita no começo do loop; apenas repetir para clareza
            exibirEstado(&fila, &pilha);
        }
        else if (opcao == 0) {
            printf("Saindo...\n");
        }
        else {
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
