#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <ctype.h>
int anoBissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}
void dadoDoLeitor(char *nomeleitor, int* dia, int *mes, int *ano){
   printf("A quem o livro será emprestado:\n");
      scanf(" %49[^\n]", nomeleitor);
      solicitarData(dia, mes, ano);             

}

void solicitarNome(char *nomedoLeitor)
{
     printf("digite o nome do leitor:\n");
     scanf(" %49[^\n]", nomedoLeitor);
}
void solicitarData(int* dia, int *mes, int *ano)
{  
      printf("digite a data de emprestimo (dd mm aaaa):\n");
      scanf("%d %d %d", dia, mes, ano);
}

void codigoLivro(int *codigo){
      printf("digite o código do livro:\n");
                scanf("%d", codigo);
}

void diminuir(char *nome){
      for (int i = 0; nome[i] != '\0'; i++)
      {
            nome[i] = tolower(nome[i]);
      }  
}

int dataEmDias(int dia, int mes, int ano)
{
      int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      int total = 0;
 
      // soma os anos completos anteriores
      for (int a = 1900; a < ano; a++)
      {
            total += anoBissexto(a) ? 366 : 365;
      }
      if (anoBissexto(ano))
      {
            diasNoMes[1] = 29;
      }
      for (int m = 0; m < mes - 1; m++)
      {
            total += diasNoMes[m];
      }
      return total + dia;
}
 
int compararDatas(Livro *livro, int diaAtual, int mesAtual, int anoAtual, int indice, int diasPermitidos)
{
      int diaEmprestimo, mesEmprestimo, anoEmprestimo, diasComLivro;
      diaEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.dia;
      mesEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.mes;
      anoEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.ano;
 
      int dataEmpTotal = dataEmDias(diaEmprestimo, mesEmprestimo, anoEmprestimo);
      int dataAtualTotal = dataEmDias(diaAtual, mesAtual, anoAtual);
 
      diasComLivro = dataAtualTotal - dataEmpTotal;
      if (diasComLivro > diasPermitidos)
      {
            return diasComLivro - diasPermitidos;
      }
 
      return 0;
}
