#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <ctype.h>
void dadoDoLeitor(char *nomeleitor, int* dia, int *mes, int *ano){
   printf("A quem o livro será emprestado:\n");
                    scanf(" %49[^\n]", nomeleitor);
                    printf("digite a data atual:(formato dia|mes|ano):\n");
                    scanf ("%d %d %d", dia, mes, ano);

}
void solicitarNome(char *nomedoLeitor)
{
     scanf(" %49[^\n]", nomedoLeitor);
}
void solicitarData(int* dia, int *mes, int *ano)
{  
      printf("digite a data atual:(formato dia|mes|ano):\n");
      scanf ("%d %d %d", dia, mes, ano);
}

void codigoLivro(int *codigo){
      printf("digite o código do livro que será emprestado:\n");
                scanf("%d", codigo);
}

void diminuir(char *nome){
      for (int i = 0; nome[i] != '\0'; i++)
      {
            nome[i] = tolower(nome[i]);
      }  
}

int compararDatas(Livro *livro, int diaAtual, int mesAtual,int anoAtual,int indice, int diasPermitidos)
{ int diaEmprestimo, mesEmprestimo, anoEmprestimo, diasComLivro;
    diaEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.dia;
    mesEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.mes;
    anoEmprestimo = livro->historicoEmprestimos[indice].dataEmprestimo.ano;

   int dataEmpTotal = anoEmprestimo * 365 + mesEmprestimo * 30 + diaEmprestimo;
   int dataAtualTotal = anoAtual * 365 + mesAtual * 30 + diaAtual;
    
    diasComLivro = dataAtualTotal - dataEmpTotal;
     if (diasComLivro > diasPermitidos)
     {
       return diasComLivro - diasPermitidos;
     }
     
     return 0;
}