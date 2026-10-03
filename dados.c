#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

void dadoDoLeitor(char *nomeleitor, int* dia, int *mes, int *ano){
   printf("A quem o livro será emprestado:\n");
                    scanf(" %49[^\n]", nomeleitor);
                    printf("digite a data atual:(formato dia|mes|ano):\n");
                    scanf ("%d %d %d", dia, mes, ano);

}

void codigoLivro(int *codigo){
      printf("digite o código do livro que será emprestado:\n");
                scanf("%d", codigo);
}