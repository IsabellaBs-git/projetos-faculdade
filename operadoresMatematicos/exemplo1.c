#include <stdio.h>

int main() {
    /*
    Soma (+)
    Sub (-)
    Multi (*)
    Div (/)
    */
   int numero1, numero2;
   int soma, subtracao, multiplicação, divisao;

   printf("Coloque o número 1: \n");
   scanf("%d", &numero1);
   printf("Entre com o número 2: \n");
   scanf("%d", &numero2);

   //opercao soma
   soma = numero1 + numero2;

    //opercao subtracao
   subtracao = numero1 - numero2;

    //opercao multiplicacao
   multiplicação = numero1 * numero2;

    //opercao divisao
   divisao = numero1/numero2;

   printf("A Soma é: %d\n:", soma);
   printf("A Subtração é: %d\n:", subtracao);
   printf("A Multiplicação é: %d\n:", multiplicação);
   printf("A Divisão é: %d\n", divisao);

}