/*fuções relacionadas à criação e leitura de dados*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"
int criarCodigo(Livro acervo[], int quantidade)
{
  int maior = 0;
  for (int i = 0; i < quantidade; i++)
  {
    if (acervo[i].codigo > maior)
    {
      maior = acervo[i].codigo;
    }
  }
  return maior + 1;
}
Livro *cadastrarLivro(Livro acervo[], int quantidade)
{
  Livro *livro_Retorno = (Livro *)malloc(sizeof(Livro));
  if (livro_Retorno == NULL)
  {
    printf("Erro ao criar livro\n");
    return NULL;
  }
  memset(livro_Retorno, 0, sizeof(Livro));
  livro_Retorno->codigo = criarCodigo(acervo, quantidade);
  printf("Escreva o titulo da obra:\n");
  scanf(" %79[^\n]", livro_Retorno->titulo);
  while (getchar() != '\n');
  
  printf("Autor do livro:\n");
  scanf(" %49[^\n]", livro_Retorno->autor);
   while (getchar() != '\n');

  printf("Genero literario:\n");
  scanf(" %29[^\n]", livro_Retorno->genero);
  while (getchar() != '\n');

  while (1) {
    printf("Exemplares disponiveis:\n");
    if (scanf("%d", &livro_Retorno->exemplaresDisponiveis) == 1) {
        if (livro_Retorno->exemplaresDisponiveis >= 0) {
          
            break; 
        } else {
            printf("Erro: A quantidade não pode ser negativa!\n");
          
        }
    } else {
        printf("Entrada invalida! Digite apenas numeros inteiros.\n");
        while (getchar() != '\n');
    } 
}
  livro_Retorno->quantidadeEmprestimosRegistrados = 0;
  livro_Retorno->totalEmprestimos = 0;

  return livro_Retorno;
}
int adicionarAoVetor(Livro **acervo, int *quantidade, Livro novoLivro)
{
  int novaQtd = (*quantidade) + 1;
  Livro *novoAcervo = (Livro *)realloc(*acervo, novaQtd * (sizeof(Livro)));
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
void salvarAcervo(Livro acervo[], int quantidade, char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "w");

  if (arquivo == NULL)
  {
    printf("erro de memoria!\n");
    return;
  }
  // salvamos os livros e o historico de emprestimo, pois será util para função calendario//
  for (int i = 0; i < quantidade; i++)
  {
    fprintf(arquivo, "%d;%s;%s;%s;%d;%d;%d",
            acervo[i].codigo,
            acervo[i].titulo,
            acervo[i].autor,
            acervo[i].genero,
            acervo[i].exemplaresDisponiveis,
            acervo[i].quantidadeEmprestimosRegistrados,
            acervo[i].totalEmprestimos);
            
    for (int j = 0; j < acervo[i].quantidadeEmprestimosRegistrados; j++)
    {
      fprintf(arquivo, ";%s;%d;%d;%d;%d",
              acervo[i].historicoEmprestimos[j].nomeLeitor,
              acervo[i].historicoEmprestimos[j].dataEmprestimo.dia,
              acervo[i].historicoEmprestimos[j].dataEmprestimo.mes,
              acervo[i].historicoEmprestimos[j].dataEmprestimo.ano,
              acervo[i].historicoEmprestimos[j].devolvido);
    }
    fprintf(arquivo, "\n");
  }
  fclose(arquivo);
  printf("acervo salvo com sucesso!!!\n");
}

int carregarAcervo(Livro **acervo, char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  int quantidadeLivros = 0;
  if (arquivo == NULL)
  {
    return quantidadeLivros;
  }
  Livro livroAux = {0};

  while (fscanf(arquivo, " %d;%79[^;];%49[^;];%29[^;];%d;%d;%d",
                &livroAux.codigo,
                livroAux.titulo,
                livroAux.autor,
                livroAux.genero,
                &livroAux.exemplaresDisponiveis,
                &livroAux.quantidadeEmprestimosRegistrados,
                &livroAux.totalEmprestimos) == 7)
  {
    memset(livroAux.historicoEmprestimos, 0, sizeof(livroAux.historicoEmprestimos));
    if (livroAux.quantidadeEmprestimosRegistrados > 0)
    {
      for (int i = 0; i < livroAux.quantidadeEmprestimosRegistrados; i++)
      {
        fscanf(arquivo, ";%49[^;];%d;%d;%d;%d",
               livroAux.historicoEmprestimos[i].nomeLeitor,
               &livroAux.historicoEmprestimos[i].dataEmprestimo.dia,
               &livroAux.historicoEmprestimos[i].dataEmprestimo.mes,
               &livroAux.historicoEmprestimos[i].dataEmprestimo.ano,
               &livroAux.historicoEmprestimos[i].devolvido);
      }
      
    }
    fscanf(arquivo, "%*[^\n]"); 
    fgetc(arquivo); 
    adicionarAoVetor(acervo, &quantidadeLivros, livroAux);
  }
  fclose(arquivo);
  return quantidadeLivros;
}
void listarTodos(Livro acervo[], int quantidade)
{
  if (quantidade == 0)
  {
    printf("Nenhum livro cadastrado!\n");
    return;
  }
  for (int i = 0; i < quantidade; i++)
  {
    printf("Codigo: %d\n", acervo[i].codigo);
    printf("Titulo: %s\n", acervo[i].titulo);
    printf("Autor: %s\n", acervo[i].autor);
    printf("Genero: %s\n", acervo[i].genero);
    printf("Exemplares disponiveis: %d\n", acervo[i].exemplaresDisponiveis);
    printf("Quantidade de emprestimos registrados: %d\n", acervo[i].quantidadeEmprestimosRegistrados);
    printf("\n");
  }
}
Livro *buscarPorCodigo(Livro acervo[], int quantidade, int codigoBuscado)
{
  for (int i = 0; i < quantidade; i++)
  {
    if (acervo[i].codigo == codigoBuscado)
    {
      return &acervo[i];
    }
  }
  return NULL;
}

void atualizarExemplaresDisponiveis(Livro *item, int novo_valor)
{
  if (item == NULL || novo_valor < 0)
  {
    printf("Valor invalido ou o livro indisponível\n");
    return;
  }
  item->exemplaresDisponiveis = novo_valor;
  printf("Exemplar atualizado!\n");
}
int removerLivro(Livro **acervo, int *quantidade, int codigo)
{
  Livro *vaux = *acervo;
  int aux = -1;
  for (int i = 0; i < (*quantidade); i++)
  {
    if (vaux[i].codigo == codigo)
    {
      aux = i;
      break;
    }
  }
  if (aux == -1)
    return 0;

  for (int i = aux; i < (*quantidade - 1); i++)
  {
    vaux[i] = vaux[i + 1];
  }
  (*quantidade)--;

  if (*quantidade == 0)
  {
    free(vaux);
    *acervo = NULL;
  }
  else
  {
    Livro *novo = (Livro *)realloc(vaux, (*quantidade) * sizeof(Livro));
    if (novo != NULL)
      *acervo = novo;
  }
  return 1;
}
int verificaSeLivroExiste(Livro *livro)
{
  if (livro == NULL)
  {
    printf("Erro: Livro nao encontrado no acervo!\n");
    return 0; // 0 (o livro não existe)
  }
  return 1; // 1 (o livro existe)
}

void liberarAcervo(Livro **acervo, int *quantidade)
{
  if (acervo != NULL && *acervo != NULL)
  {
    free(*acervo);
    *acervo = NULL;
    *quantidade = 0;
    
    return;
  }
  else
  {
    printf("não há nenhum livro em seu acervo\n");
    return;
  }
}

int removerLeitor(Livro *livro, int indice)
{ 
  int n = livro->quantidadeEmprestimosRegistrados;
  if (indice < 0 || indice >= n)
  {
    printf("Indice invalido para remover leitor.\n");
    return 0;
  }
  for (int i = indice; i < n - 1; i++)
  {
    livro->historicoEmprestimos[i] = livro->historicoEmprestimos[i + 1];
  }
  memset(&livro->historicoEmprestimos[n - 1], 0, sizeof(livro->historicoEmprestimos[n - 1]));
  livro->quantidadeEmprestimosRegistrados--;
  return 1;
}
void adicionarLeitor(Livro *livro, int indiceOrigem, int indiceDestino)
{
    livro->historicoEmprestimos[indiceDestino] = livro->historicoEmprestimos[indiceOrigem];
    livro->historicoEmprestimos[indiceDestino].devolvido = 0;
    removerLeitor(livro, indiceOrigem); 
}