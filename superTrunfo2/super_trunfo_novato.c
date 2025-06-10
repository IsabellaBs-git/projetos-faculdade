#include <stdio.h>

int main() {
    // Declaração de variáveis para a Carta 1
    char estado1[3], codigo1[5], nomeCidade1[50];
    int populacao1, pontosTuristicos1;
    float area1, pib1;
    float densidade1, pibPerCapita1;

    // Declaração de variáveis para a Carta 2
    char estado2[3], codigo2[5], nomeCidade2[50];
    int populacao2, pontosTuristicos2;
    float area2, pib2;
    float densidade2, pibPerCapita2;

    // Entrada de dados para a Carta 1
    printf("Cadastro da Carta 1:\n");
    printf("Estado: ");
    scanf(" %s", estado1);

    printf("Código da carta: ");
    scanf("%s", codigo1);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", nomeCidade1);

    printf("População: ");
    scanf("%d", &populacao1);

    printf("Área (km²): ");
    scanf("%f", &area1);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib1);

    printf("Número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos1);

    // Cálculos para a Carta 1
    densidade1 = populacao1 / area1;
    pibPerCapita1 = (pib1 * 1000000000.0) / populacao1;

    // Entrada de dados para a Carta 2
    printf("\nCadastro da Carta 2:\n");
    printf("Estado: ");
    scanf(" %s", estado2);

    printf("Código da carta: ");
    scanf("%s", codigo2);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", nomeCidade2);

    printf("População: ");
    scanf("%d", &populacao2);

    printf("Área (km²): ");
    scanf("%f", &area2);

    printf("PIB (em bilhões): ");
    scanf("%f", &pib2);

    printf("Número de pontos turísticos: ");
    scanf("%d", &pontosTuristicos2);

    // Cálculos para a Carta 2
    densidade2 = populacao2 / area2;
    pibPerCapita2 = (pib2 * 1000000000.0) / populacao2;

    // Escolha do atributo para comparação (FIXO: População)
    printf("\nComparação de cartas (Atributo - População):\n");

    printf("Carta 1 - %s (%s): %d habitantes\n", nomeCidade1, estado1, populacao1);
    printf("Carta 2 - %s (%s): %d habitantes\n", nomeCidade2, estado2, populacao2);

    // Comparação usando estrutura if
    if (populacao1 > populacao2) {
        printf("Resultado: Carta 1 (%s) venceu!\n", nomeCidade1);
    } else if (populacao2 > populacao1) {
        printf("Resultado: Carta 2 (%s) venceu!\n", nomeCidade2);
    } else {
        printf("Resultado: Empate!\n");
    }

    return 0;
}
