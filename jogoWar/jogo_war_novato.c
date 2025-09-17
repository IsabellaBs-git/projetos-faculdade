#include <stdio.h>
#include <string.h>


//Definição da Struct Territorio
//Essa estrutura agrupa os dados referentes a cada territorio
typedef struct {
    char nome[30];    //Nome do territorio
    char cor[10];     //Cor do exercito que ocupa o territorio
    int tropas;       //Numero de tropas presentes
} Territorio;         //utilizando o struct dessa forma para otimizar tempo no desenv do codigo


int main() {
    Territorio territorios[5]; //Vetor para armazenar 5 territorios
    int i;

    printf("=== Cadastro de Territorios - Jogo War ===\n");

    // Laço para cadastrar os 5 territórios
    for (i= 0; i < 5; i++) {
        printf("\nCadastro do Territorio %d:\n", i + 1);

        //Leitura do nome
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; //Remove o \n

        //Leitura da cor do exercito
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; //Remove o \n


        //Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); //Consumir o /n deixado pelo scanf
    }


    //Exibicao dos territorios cadastrados
    printf("\n=== Territorios cadastrados ===\n");
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exercito: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("-------------------\n");
    }

    return 0;

}