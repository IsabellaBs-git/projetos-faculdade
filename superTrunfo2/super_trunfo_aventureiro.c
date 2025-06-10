#include <stdio.h>
#include <string.h>

// Tamanho máximo para strings
#define TAM 50

int main() {
    // Declaração de variáveis
    char nomePais1[TAM], nomePais2[TAM];
    int populacao1, populacao2;
    float area1, area2, pib1, pib2;
    int pontosTuristicos1, pontosTuristicos2;
    float densidade1, densidade2;

    int opcao;

    // Cadastro da Carta 1
    printf("Cadastro da Carta 1:\n");
    printf("Nome do país: ");
    scanf(" %[^\n]", nomePais1);

    printf("População: ");
    scanf("%d", &populacao1);

    printf("Área (em km²): ");
    scanf("%f", &area1);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // Cadastro da Carta 2
    printf("\nCadastro da Carta 2:\n");
    printf("Nome do país: ");
    scanf(" %[^\n]", nomePais2);

    printf("População: ");
    scanf("%d", &populacao2);

    printf("Área (em km²): ");
    scanf("%f", &area2);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // Cálculo da densidade demográfica
    densidade1 = populacao1 / area1;
    densidade2 = populacao2 / area2;

    // Menu interativo
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Demográfica\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    printf("\nComparação de cartas (%s):\n", 
           opcao == 1 ? "População" :
           opcao == 2 ? "Área" :
           opcao == 3 ? "PIB" :
           opcao == 4 ? "Pontos Turísticos" :
           opcao == 5 ? "Densidade Demográfica" : "Atributo Inválido");

    // Comparações com lógica if-else aninhada
    switch (opcao) {
        case 1: // População
            printf("%s: %d habitantes\n", nomePais1, populacao1);
            printf("%s: %d habitantes\n", nomePais2, populacao2);
            if (populacao1 > populacao2) {
                printf("Resultado: %s venceu!\n", nomePais1);
            } else if (populacao2 > populacao1) {
                printf("Resultado: %s venceu!\n", nomePais2);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;

        case 2: // Área
            printf("%s: %.2f km²\n", nomePais1, area1);
            printf("%s: %.2f km²\n", nomePais2, area2);
            if (area1 > area2) {
                printf("Resultado: %s venceu!\n", nomePais1);
            } else if (area2 > area1) {
                printf("Resultado: %s venceu!\n", nomePais2);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;

        case 3: // PIB
            printf("%s: %.2f bilhões\n", nomePais1, pib1);
            printf("%s: %.2f bilhões\n", nomePais2, pib2);
            if (pib1 > pib2) {
                printf("Resultado: %s venceu!\n", nomePais1);
            } else if (pib2 > pib1) {
                printf("Resultado: %s venceu!\n", nomePais2);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;

        case 4: // Pontos Turísticos
            printf("%s: %d pontos turísticos\n", nomePais1, pontosTuristicos1);
            printf("%s: %d pontos turísticos\n", nomePais2, pontosTuristicos2);
            if (pontosTuristicos1 > pontosTuristicos2) {
                printf("Resultado: %s venceu!\n", nomePais1);
            } else if (pontosTuristicos2 > pontosTuristicos1) {
                printf("Resultado: %s venceu!\n", nomePais2);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;

        case 5: // Densidade Demográfica (menor vence)
            printf("%s: %.2f hab/km²\n", nomePais1, densidade1);
            printf("%s: %.2f hab/km²\n", nomePais2, densidade2);
            if (densidade1 < densidade2) {
                printf("Resultado: %s venceu!\n", nomePais1);
            } else if (densidade2 < densidade1) {
                printf("Resultado: %s venceu!\n", nomePais2);
            } else {
                printf("Resultado: Empate!\n");
            }
            break;

        default:
            printf("Opção inválida!\n");
            break;
    }

    return 0;
}
