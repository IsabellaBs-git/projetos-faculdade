

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 53    // tamanho da tabela hash (primo)
#define MAX_STR 128

/* --------------------- ESTRUTURAS --------------------- */

// Nó da árvore binária de salas (mapa da mansão)
typedef struct Sala {
    char nome[50];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Nó da BST de pistas (ordenada por string)
typedef struct PistaNode {
    char *pista;
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;

// Entrada da tabela hash (encadeamento separado)
typedef struct HashEntry {
    char *pista;            // chave
    char *suspeito;         // valor
    struct HashEntry *next;
} HashEntry;

/* -------------------- PROTÓTIPOS -------------------- */

/* criarSala() – cria dinamicamente um cômodo.
   Args: nome da sala (string)
   Retorno: ponteiro para Sala alocada dinamicamente
*/
Sala* criarSala(const char *nome);

/* explorarSalas() – navega pela árvore e ativa o sistema de pistas.
   Args:
    - raiz: nó inicial (Sala*)
    - pistasColetadas: ponteiro para raiz da BST de pistas (PistaNode**)
    - hash: tabela hash de associações pista->suspeito (HashEntry *[])
   Interativo: comandos 'e' (esquerda), 'd' (direita), 's' (sair).
   Ao entrar na sala, verifica se há pista associada e adiciona à BST se nova.
*/
void explorarSalas(Sala *raiz, PistaNode **pistasColetadas, HashEntry *hash[]);

/* inserirPista() / adicionarPista() – insere a pista coletada na árvore de pistas.
   Args:
    - root: raiz atual da BST
    - pista: string da pista a inserir
   Retorno: nova raiz da BST (PistaNode*)
*/
PistaNode* inserirPista(PistaNode *root, const char *pista);

/* inserirNaHash() – insere associação pista/suspeito na tabela hash.
   Args:
    - hash: tabela hash (HashEntry *[])
    - pista: chave (string)
    - suspeito: valor (string)
   Sem retorno.
*/
void inserirNaHash(HashEntry *hash[], const char *pista, const char *suspeito);

/* encontrarSuspeito() – consulta o suspeito correspondente a uma pista.
   Args:
    - hash: tabela hash
    - pista: chave
   Retorno: ponteiro para string do suspeito (ou NULL se não existir)
*/
char* encontrarSuspeito(HashEntry *hash[], const char *pista);

/* verificarSuspeitoFinal() – conduz à fase de julgamento final.
   Conta quantas pistas coletadas apontam para o acusado.
   Retorna 1 se houver pelo menos 2 pistas apontando para o acusado, 0 caso contrário.
*/
int verificarSuspeitoFinal(PistaNode *root, HashEntry *hash[], const char *acusado);

/* ----------------- FUNÇÕES AUXILIARES ----------------- */
void inorderPistas(PistaNode *root);
void liberarPistas(PistaNode *root);
int pistaExiste(PistaNode *root, const char *pista);
unsigned long hashString(const char *str);
void liberarHash(HashEntry *hash[]);
const char* pistaParaSala(const char *nomeSala);
Sala* montarMansaoFixa(void);

/* ----------------- IMPLEMENTAÇÃO ----------------- */

/* criarSala: cria dinamicamente um cômodo com o nome dado.
   Aloca memória para a struct Sala, inicializa os ponteiros e copia o nome.
*/
Sala* criarSala(const char *nome) {
    Sala *s = (Sala*) malloc(sizeof(Sala));
    if (!s) {
        fprintf(stderr, "Erro de alocacao em criarSala\n");
        exit(EXIT_FAILURE);
    }
    strncpy(s->nome, nome, sizeof(s->nome)-1);
    s->nome[sizeof(s->nome)-1] = '\0';
    s->esq = s->dir = NULL;
    return s;
}

/* Função hash para strings (djb2) */
unsigned long hashString(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

/* inserirNaHash: insere uma associação pista -> suspeito na tabela hash.
   Usa encadeamento separado (lista ligada) para colisões.
*/
void inserirNaHash(HashEntry *hash[], const char *pista, const char *suspeito) {
    unsigned long h = hashString(pista) % HASH_SIZE;
    HashEntry *entry = (HashEntry*) malloc(sizeof(HashEntry));
    entry->pista = strdup(pista);
    entry->suspeito = strdup(suspeito);
    entry->next = hash[h];
    hash[h] = entry;
}

/* encontrarSuspeito: busca pela pista na tabela hash; retorna suspeito ou NULL */
char* encontrarSuspeito(HashEntry *hash[], const char *pista) {
    unsigned long h = hashString(pista) % HASH_SIZE;
    HashEntry *cur = hash[h];
    while (cur) {
        if (strcmp(cur->pista, pista) == 0) return cur->suspeito;
        cur = cur->next;
    }
    return NULL;
}

/* inserirPista: insere string 'pista' na BST ordenada por strcmp.
   Se a pista já existir (igual), não insere duplicata.
*/
PistaNode* inserirPista(PistaNode *root, const char *pista) {
    if (!root) {
        PistaNode *node = (PistaNode*) malloc(sizeof(PistaNode));
        node->pista = strdup(pista);
        node->esq = node->dir = NULL;
        return node;
    }
    int cmp = strcmp(pista, root->pista);
    if (cmp < 0) root->esq = inserirPista(root->esq, pista);
    else if (cmp > 0) root->dir = inserirPista(root->dir, pista);
    // se igual, não insere
    return root;
}

/* pistaExiste: verifica se a pista já está na BST (evita repetição) */
int pistaExiste(PistaNode *root, const char *pista) {
    if (!root) return 0;
    int cmp = strcmp(pista, root->pista);
    if (cmp == 0) return 1;
    if (cmp < 0) return pistaExiste(root->esq, pista);
    return pistaExiste(root->dir, pista);
}

/* inorderPistas: exibe as pistas coletadas em ordem alfabética */
void inorderPistas(PistaNode *root) {
    if (!root) return;
    inorderPistas(root->esq);
    printf("- %s\n", root->pista);
    inorderPistas(root->dir);
}

/* liberarPistas: libera memória da BST de pistas */
void liberarPistas(PistaNode *root) {
    if (!root) return;
    liberarPistas(root->esq);
    liberarPistas(root->dir);
    free(root->pista);
    free(root);
}

/* liberarHash: libera memória da tabela hash */
void liberarHash(HashEntry *hash[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry *cur = hash[i];
        while (cur) {
            HashEntry *tmp = cur;
            cur = cur->next;
            free(tmp->pista);
            free(tmp->suspeito);
            free(tmp);
        }
        hash[i] = NULL;
    }
}

/* pistaParaSala: regra codificada que retorna a pista associada a uma sala (ou NULL) */
const char* pistaParaSala(const char *nomeSala) {
    // Regras de exemplo (ajuste conforme desejar)
    if (strcmp(nomeSala, "Hall") == 0) return "Pegada de lama";
    if (strcmp(nomeSala, "Biblioteca") == 0) return "Página arrancada";
    if (strcmp(nomeSala, "Cozinha") == 0) return "Fio de cabelo loiro";
    if (strcmp(nomeSala, "Escritório") == 0) return "Bilhete ameaçador";
    if (strcmp(nomeSala, "Quarto") == 0) return "Marca de sapato";
    if (strcmp(nomeSala, "Jardim") == 0) return "Pegada de sapato especial";
    if (strcmp(nomeSala, "Sala de Jantar") == 0) return "Restos de veneno";
    // Sem pista por padrão
    return NULL;
}

/* montarMansaoFixa: monta manualmente a árvore de salas (mapa) */
Sala* montarMansaoFixa(void) {
    Sala *root = criarSala("Hall");
    root->esq = criarSala("Biblioteca");
    root->dir = criarSala("Sala de Jantar");
    root->esq->esq = criarSala("Escritório");
    root->esq->dir = criarSala("Jardim");
    root->dir->esq = criarSala("Cozinha");
    root->dir->dir = criarSala("Quarto");
    return root;
}

/* explorarSalas: navega pela árvore de salas de maneira interativa.
   - Ao visitar sala, exibe pista (se houver).
   - Se pista existente e ainda não coletada, insere na BST de pistas.
   - Comandos:
       e/E -> ir para esquerda (se existir)
       d/D -> ir para direita (se existir)
       s/S -> sair da exploração
*/
void explorarSalas(Sala *raiz, PistaNode **pistasColetadas, HashEntry *hash[]) {
    Sala *atual = raiz;
    char buf[32];

    printf("Iniciando exploracao da mansao. Voce comeca no Hall.\n");

    while (1) {
        printf("\nSala atual: %s\n", atual->nome);

        const char *pista = pistaParaSala(atual->nome);
        if (pista) {
            printf("Voce encontrou uma pista: %s\n", pista);
            if (!pistaExiste(*pistasColetadas, pista)) {
                *pistasColetadas = inserirPista(*pistasColetadas, pista);
                printf("Pista coletada e adicionada ao seu caderno.\n");
            } else {
                printf("Voce ja coletou esta pista anteriormente.\n");
            }
        } else {
            printf("Nenhuma pista nesta sala.\n");
        }

        printf("Escolha direcao: [e] esquerda, [d] direita, [s] sair exploracao\n");
        printf("Comando: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;

        // obtém primeiro caracter não-espaco
        char c = 0;
        for (int i = 0; buf[i]; i++) {
            if (!isspace((unsigned char)buf[i])) { c = buf[i]; break; }
        }

        if (c == 's' || c == 'S') {
            printf("Encerrando exploracao.\n");
            break;
        } else if (c == 'e' || c == 'E') {
            if (atual->esq) atual = atual->esq;
            else printf("Nao ha sala a esquerda.\n");
        } else if (c == 'd' || c == 'D') {
            if (atual->dir) atual = atual->dir;
            else printf("Nao ha sala a direita.\n");
        } else {
            printf("Comando invalido.\n");
        }
    }
}

/* verificarMissaoAux: percorre BST de pistas e conta quantas apontam para 'acusado' */
int verificarMissaoAux(PistaNode *root, HashEntry *hash[], const char *acusado) {
    if (!root) return 0;
    int cnt = 0;
    cnt += verificarMissaoAux(root->esq, hash, acusado);
    char *sus = encontrarSuspeito(hash, root->pista);
    if (sus && strcmp(sus, acusado) == 0) cnt++;
    cnt += verificarMissaoAux(root->dir, hash, acusado);
    return cnt;
}

/* verificarSuspeitoFinal: conta pistas que relacionam ao acusado e decide
   Retorna 1 se haverao >= 2 pistas, 0 caso contrario.
*/
int verificarSuspeitoFinal(PistaNode *root, HashEntry *hash[], const char *acusado) {
    int total = verificarMissaoAux(root, hash, acusado);
    printf("Total de pistas que relacionam %s: %d\n", acusado, total);
    return (total >= 2) ? 1 : 0;
}

/* --------------------- MAIN --------------------- */
int main() {
    // inicializa tabela hash
    HashEntry *hash[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) hash[i] = NULL;

    // monta mansao fixa
    Sala *mansao = montarMansaoFixa();

    // Preenche tabela hash: pista -> suspeito
    // Exemplos de suspeitos
    inserirNaHash(hash, "Pegada de lama", "Sr. Verde");
    inserirNaHash(hash, "Página arrancada", "Sra. Azul");
    inserirNaHash(hash, "Fio de cabelo loiro", "Srta. Rosa");
    inserirNaHash(hash, "Bilhete ameaçador", "Prof. Amarelo");
    inserirNaHash(hash, "Marca de sapato", "Sr. Verde");
    inserirNaHash(hash, "Pegada de sapato especial", "Sr. Verde");
    inserirNaHash(hash, "Restos de veneno", "Sra. Azul");
    // pode adicionar mais associações conforme desejar

    // BST de pistas coletadas (vazia no inicio)
    PistaNode *pistasColetadas = NULL;

    // Explorar mansao
    explorarSalas(mansao, &pistasColetadas, hash);

    // Exibe pistas coletadas
    printf("\n===== Pistas coletadas =====\n");
    if (!pistasColetadas) {
        printf("Nenhuma pista coletada.\n");
    } else {
        inorderPistas(pistasColetadas);
    }

    // Acusacao final
    char acusado[64];
    printf("\nQuem voce acusa? (Digite o nome do suspeito, ex: Sr. Verde):\n");
    if (!fgets(acusado, sizeof(acusado), stdin)) {
        acusado[0] = '\0';
    } else {
        acusado[strcspn(acusado, "\n")] = '\0';
    }

    if (strlen(acusado) == 0) {
        printf("Nenhum acusado informado. Encerrando sem julgamento.\n");
    } else {
        int ok = verificarSuspeitoFinal(pistasColetadas, hash, acusado);
        if (ok) {
            printf("\nAcusacao bem-sucedida! Ha evidencias suficientes para culpar %s.\n", acusado);
        } else {
            printf("\nAcusacao fracassada. Nao ha pistas suficientes contra %s.\n", acusado);
        }
    }

    // libera memoria: pistas (BST)
    liberarPistas(pistasColetadas);

    // libera hash
    liberarHash(hash);

    // libera salas (árvore de salas) usando pos-ordem
    // função local auxiliar:
    void liberarSalas(Sala *node) {
        if (!node) return;
        liberarSalas(node->esq);
        liberarSalas(node->dir);
        free(node);
    }
    liberarSalas(mansao);

    printf("\nObrigado por jogar Detective Quest (terminal)!\n");
    return 0;
}

