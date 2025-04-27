#include <stdio.h>

int main() {
    int idade;
    float altura;
    char opcao;
    char nome[20];

    printf("Digite a sua idade: ");
    scanf("%d", &idade);
    printf("A idade é: %d\n", idade);

    printf("Digite a sua altura: ");
    scanf("%f", &altura);
    printf("A altura é: %f\n", altura);

    printf("Digite a sua opção: ");
    scanf(" %c", &opcao);
    printf("A opção é: %c\n", opcao);

    printf("Digite o seu nome: ");
    scanf("%s", &nome);
    printf("O seu nome é: %s", nome);

}