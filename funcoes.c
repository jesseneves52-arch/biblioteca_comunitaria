#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

Livro *cadastrarLivro(int codigo){
  Livro *livro_Retorno = (Livro *) malloc(sizeof(Livro));
    printf("Escreva o titulo da obra:\n");
      scanf("^%79[^\n]", livro_Retorno->titulo);
    printf("Autor do livro:\n");
      scanf("^%49[^\n]", livro_Retorno->autor);
    printf("Genero literario:\n");
      scanf("^%29[^\n]", livro_Retorno->genero);
    printf("Exemplares disponiveis:\n");
      scanf("%d", livro_Retorno->exemplaresDisponiveis); 



    return livro_Retorno;
}
int adicionarAoVetor(Livro **acervo, int *quantidade, Livro novoLivro){





}