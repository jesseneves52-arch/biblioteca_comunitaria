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
void salvarAcervo(Livro acervo[], int quantidade, char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo,"w");

      if (arquivo == NULL)
      {
        printf("erro de memoria!\n");
        return;
      }
    for (int i = 0; i < quantidade; i++)
    {
      fprintf(arquivo,"%d;%s;%s;%s;%d;%d",
              acervo[i].codigo,
              acervo[i].titulo,
              acervo[i].autor,
              acervo[i].genero,
              acervo[i].exemplaresDisponiveis,
              acervo[i].quantidadeEmprestimosRegistrados);
      for (int j = 0; j < acervo[i].quantidadeEmprestimosRegistrados; j++)
      {
        fprintf(arquivo,"%s;%d;%d;%d;%d",
                acervo[i].historicoEmprestimos[j].nomeLeitor,
                acervo[i].historicoEmprestimos[j].dataEmprestimo.dia,
                acervo[i].historicoEmprestimos[j].dataEmprestimo.mes,
                acervo[i].historicoEmprestimos[j].dataEmprestimo.ano,
                acervo[i].historicoEmprestimos[j].devolvido);       
      } 
      fprintf(arquivo,"\n");
    }
     fclose(arquivo);
     printf("acervo salvo com sucesso!!!\n");
}

    /*int carregarAcervo(Livro acervo[], char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo,"r");
      if (arquivo == NULL)
      {
        printf("Erro de memoria ao carregar acervo");
        return;
      }
    while (fprintf())
    {
    
    } 
    
     



}*/