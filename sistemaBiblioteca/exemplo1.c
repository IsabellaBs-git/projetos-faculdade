#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Para o strcspn

// ---- Constantes Globais ----
#define MAX_LIVROS 50
#define TAM_STRING 100

// ---- Definição da estrutura (Struct) ----
struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// ---- Função para limpar o buffer de entrada ----
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// ---- Função principal ----
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do {
        printf("============================\n");
        printf(" BIBLIOTECA - PARTE 1\n");
        printf("============================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("\n");
        printf("Escolha uma opção: ");

        //Lê a opção do usuário.
        scanf("%d", &opcao);
        limparBufferEntrada();

        // ---- Processamento da Opção ----
        switch (opcao) {
            case 1: // CADASTRO DE LIVRO
                printf("--- Cadastro de Novo Livro --- \n\n");
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro:\n");
                    fflush(stdout);
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o nome do autor:\n");
                    fflush(stdout);
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                    printf("Digite o nome da editora:\n");
                    fflush(stdout);
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                    printf("Digite a edicao: ");
                    fflush(stdout);
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    totalLivros++;
                    printf("\nLivro cadastrado com sucesso!\n");
                    fflush(stdout);
                } else {
                    printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
                    fflush(stdout);
                }

                printf("\npressione Enter para continuar...\n");
                fflush(stdout);
                getchar(); //pausa para o usuário ler a mensagem antes de voltar para o menu.
                break;

            case 2: //LISTAGEM DE LIVROS
                printf("--- Lista de Livros Cadastrados ---\n\n");

                if (totalLivros == 0){
                    printf("Nenhum livro cadastrado ainda.\n");
                    fflush(stdout);
                } else {
                    for (int i = 0; i < totalLivros; i++){
                        printf("---------------------------\n");
                        printf("Livro: %d\n", i + 1);
                        fflush(stdout);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        fflush(stdout);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        fflush(stdout);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        fflush(stdout);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    }
                    printf("-----------------------\n");
                    fflush(stdout);
                }

                printf("\nPressione Enter para continuar...");
                fflush(stdout);
                getchar();
                break;
            
            case 0: //SAIR
                printf("\n Saindo do sistema...\n");
                fflush(stdout);
                break;

            default: //opcao invalida
                printf("\nOpcao invalida! Tente novamente.\n");
                fflush(stdout);
                printf("\nPressione Enter para continuar\n");
                fflush(stdout);
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}

