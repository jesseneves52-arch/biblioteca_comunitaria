#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





/*void registrarEmprestimo(Livro *livro, char *nomeLeitor, int dia, int mes, int ano){
  if(livro->quantidadeEmprestimosRegistrados <)


    
}*/
int devolverLivro(Livro *livro, char *nomeLeitor);
int renovarEmprestimo(Livro *livro, char *nomeLeitor, int novoDia, int novoMes, int novoAno);
int reservarLivroEmprestado(Livro *livro, char *nomeLeitor);
float calcularMultaAtraso(Livro *livro, char *nomeLeitor, int diaAtual, int mesAtual, int anoAtual, int diasPermitidos);
void relatorioLivrosMaisEmprestados(Livro acervo[], int quantidade);