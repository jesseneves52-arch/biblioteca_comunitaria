#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

Livro *cadastrarLivro(int codigo){
  Livro *livro_Retorno = (Livro *) malloc(sizeof(Livro));
    if (livro_Retorno == NULL)
    {
      printf("Erro ao criar livro\n");
      return NULL;
    }
   memset(livro_Retorno, 0,sizeof(Livro));
    livro_Retorno->codigo = codigo;
    printf("Escreva o titulo da obra:\n");
      scanf(" %79[^\n]", livro_Retorno->titulo);
    printf("Autor do livro:\n");
      scanf(" %49[^\n]", livro_Retorno->autor);
    printf("Genero literario:\n");
      scanf(" %29[^\n]", livro_Retorno->genero);
    printf("Exemplares disponiveis:\n");
      scanf("%d", &livro_Retorno->exemplaresDisponiveis); 
      livro_Retorno->quantidadeEmprestimosRegistrados = 0;


      return livro_Retorno;
}
int adicionarAoVetor(Livro **acervo, int *quantidade, Livro novoLivro){
    int novaQtd = (*quantidade) + 1;
      Livro *novoAcervo =(Livro *) realloc(*acervo,novaQtd * (sizeof(Livro))); 
        if (novoAcervo == NULL)
        {  
          printf("erro de memoria ao aumentar acervo\n");
           return 0;
        }
        *acervo = novoAcervo;
        (*acervo)[*quantidade] = novoLivro;
        (*quantidade)++;
        return 1;
        
}