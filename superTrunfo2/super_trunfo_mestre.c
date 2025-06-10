#include <stdio.h>
#include <string.h>

// Definições
#define TAM 50

// Enum para atributos
enum Atributo {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE
};

// Função auxiliar para imprimir nome do atributo
const char* nomeAtributo(int opcao) {
    switch(opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Inválido";
    }
}

int main() {
    // Cartas pré-definidas
    char pais1[TAM] = "Brasil";
    int populacao1 = 213000000;
    float area1 = 8515767.0;
    float pib1 = 14400.0;
    int pontos1 = 20;

    char pais2[TAM] = "Argentina";
    int populacao2 = 45000000;
    float area2 = 2780400.0;
    float pib2 = 5000.0;
    int pontos2 = 12;

    float densidade1 = populacao1 / area1;
    float densidade2 = populacao2 / area2;

    int atributo1, atributo2;
    float valor1_carta1 = 0, valor2_carta1 = 0;
    float valor1_carta2 = 0, valor2_carta2 = 0;

    // Menu 1: escolha do primeiro atributo
    printf("Escolha o primeiro atributo para comparar:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos Turísticos\n5 - Densidade Demográfica\nOpção: ");
    scanf("%d", &atributo1);

    // Menu 2: escolha do segundo atributo (exclui o primeiro)
    printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
    for (int i = 1; i <= 5; i++) {
        if (i != atributo1) {
            printf("%d - %s\n", i, nomeAtributo(i));
        }
    }
    printf("Opção: ");
    scanf("%d", &atributo2);

    // Validação básica
    if (atributo1 == atributo2 || atributo1 < 1 || atributo1 > 5 || atributo2 < 1 || atributo2 > 5) {
        printf("\nErro: atributos inválidos ou repetidos.\n");
        return 1;
    }

    // Obter valores dos atributos escolhidos
    switch (atributo1) {
        case POPULACAO:
            valor1_carta1 = populacao1;
            valor1_carta2 = populacao2;
            break;
        case AREA:
            valor1_carta1 = area1;
            valor1_carta2 = area2;
            break;
        case PIB:
            valor1_carta1 = pib1;
            valor1_carta2 = pib2;
            break;
        case PONTOS_TURISTICOS:
            valor1_carta1 = pontos1;
            valor1_carta2 = pontos2;
            break;
        case DENSIDADE:
            valor1_carta1 = densidade1;
            valor1_carta2 = densidade2;
            break;
    }

    switch (atributo2) {
        case POPULACAO:
            valor2_carta1 = populacao1;
            valor2_carta2 = populacao2;
            break;
        case AREA:
            valor2_carta1 = area1;
            valor2_carta2 = area2;
            break;
        case PIB:
            valor2_carta1 = pib1;
            valor2_carta2 = pib2;
            break;
        case PONTOS_TURISTICOS:
            valor2_carta1 = pontos1;
            valor2_carta2 = pontos2;
            break;
        case DENSIDADE:
            valor2_carta1 = densidade1;
            valor2_carta2 = densidade2;
            break;
    }

    // Aplicar regras de comparação por atributo
    float soma1 = 0, soma2 = 0;

    // Primeiro atributo
    if (atributo1 == DENSIDADE) {
        soma1 += valor1_carta1 < valor1_carta2 ? 1 : (valor1_carta1 > valor1_carta2 ? 0 : 0.5);
        soma2 += valor1_carta2 < valor1_carta1 ? 1 : (valor1_carta1 > valor1_carta2 ? 0 : 0.5);
    } else {
        soma1 += valor1_carta1 > valor1_carta2 ? 1 : (valor1_carta1 < valor1_carta2 ? 0 : 0.5);
        soma2 += valor1_carta2 > valor1_carta1 ? 1 : (valor1_carta2 < valor1_carta1 ? 0 : 0.5);
    }

    // Segundo atributo
    if (atributo2 == DENSIDADE) {
        soma1 += valor2_carta1 < valor2_carta2 ? 1 : (valor2_carta1 > valor2_carta2 ? 0 : 0.5);
        soma2 += valor2_carta2 < valor2_carta1 ? 1 : (valor2_carta2 > valor2_carta1 ? 0 : 0.5);
    } else {
        soma1 += valor2_carta1 > valor2_carta2 ? 1 : (valor2_carta1 < valor2_carta2 ? 0 : 0.5);
        soma2 += valor2_carta2 > valor2_carta1 ? 1 : (valor2_carta2 < valor2_carta1 ? 0 : 0.5);
    }

    // Exibir resultados
    printf("\nComparando %s e %s\n", pais1, pais2);
    printf("Atributo 1 - %s:\n", nomeAtributo(atributo1));
    printf("%s: %.2f | %s: %.2f\n", pais1, valor1_carta1, pais2, valor1_carta2);

    printf("Atributo 2 - %s:\n", nomeAtributo(atributo2));
    printf("%s: %.2f | %s: %.2f\n", pais1, valor2_carta1, pais2, valor2_carta2);

    printf("\nResultado final:\n");
    printf("Pontuação %s: %.1f pontos\n", pais1, soma1);
    printf("Pontuação %s: %.1f pontos\n", pais2, soma2);

    // Vencedor
    printf("Vencedor: %s\n", soma1 > soma2 ? pais1 : (soma2 > soma1 ? pais2 : "Empate!"));

    return 0;
}
