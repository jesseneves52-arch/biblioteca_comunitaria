#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




void registrarEmprestimo(Livro *livro, char *nomeLeitor, int dia, int mes, int ano){
    char opcao;
    if(livro->quantidadeEmprestimosRegistrados >= 5){
         printf("fila de espera para reservar livro cheia, aguarde!!\n"); 
         return;  
    }
      if (livro->exemplaresDisponiveis == 0)
    {
       printf("nenhum exemplar disponivel para emprestimo, reservar livro?[s/n]");
       scanf(" %c", &opcao);
       opcao = tolower(opcao);
       switch (opcao)
       {
        case 's':
           if(reservarLivroEmprestado(livro, nomeLeitor)){
            printf("livro reservado com sucesso! Aguarde\n");
            return;
           }
        case 'n':
            return;
        default:
            printf("opcao invalida\n");
            return;
       }
    }
 
    int empretioms = livro->quantidadeEmprestimosRegistrados;
    strcpy(livro->historicoEmprestimos[empretioms].nomeLeitor, nomeLeitor);
    livro->historicoEmprestimos[empretioms].dataEmprestimo.dia = dia;
    livro->historicoEmprestimos[empretioms].dataEmprestimo.mes = mes;
    livro->historicoEmprestimos[empretioms].dataEmprestimo.ano = ano;
    livro->historicoEmprestimos[empretioms].devolvido = 0;

    livro->quantidadeEmprestimosRegistrados++;
    livro->exemplaresDisponiveis--;
    printf("emprestimo registrado com sucesso\n");
}
int devolverLivro(Livro *livro, char *nomeLeitor);

int renovarEmprestimo(Livro *livro, char *nomeLeitor, int novoDia, int novoMes, int novoAno){


  
}

int reservarLivroEmprestado(Livro *livro, char *nomeLeitor){
    if (livro->exemplaresDisponiveis > 0)
  {
     printf("ainda há exemplares disponiveis\n");
     return -1;
  }
    if (livro->quantidadeEmprestimosRegistrados >= 5)
  {
    printf("maximo de emprestimos registrado!!\n");
    return -1;
  }
   int aux = livro->quantidadeEmprestimosRegistrados;
   strcpy(livro->historicoEmprestimos[aux].nomeLeitor, nomeLeitor);
   //2 = leitor aguardando livro, 0 = não devolvido
   livro->historicoEmprestimos[aux].devolvido = 2;
   livro->quantidadeEmprestimosRegistrados++;
   return aux;//sucesso!
}
float calcularMultaAtraso(Livro *livro, char *nomeLeitor, int diaAtual, int mesAtual, int anoAtual, int diasPermitidos);
void relatorioLivrosMaisEmprestados(Livro acervo[], int quantidade);