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
int devolverLivro(Livro *livro, char *nomeLeitor){
char nomeBusca[50];
int indice = -1, indiceReserva = 0;
    strcpy(nomeBusca, nomeLeitor);
    diminuir(nomeBusca);
    for (int i = 0; i < livro->quantidadeEmprestimosRegistrados; i++) {
        char nomeHistorico[50];
        strcpy(nomeHistorico, livro->historicoEmprestimos[i].nomeLeitor);
        diminuir(nomeHistorico);
        if (livro->historicoEmprestimos[i].devolvido == 2 && indiceReserva == 0)
        {
          indiceReserva = i;
        }
        if (strcmp(nomeHistorico, nomeBusca) == 0 && livro->historicoEmprestimos[i].devolvido == 0)
        {
        indice = i;
        }
        //ainda é preciso adicionar a função de calcular multa por atraso
    }
    if (indice == -1) {
      printf("nenhuma pessoa com esse nome foi encontrada\n");
        return 0; 
    }
    if (indiceReserva != 0)
    {
     //indice onde ele está e indice de pra onde ele vai
     adicionarLeitor(livro,indiceReserva, indice);
    }
    else{
      removerLeitor(livro, indice);
      livro->quantidadeEmprestimosRegistrados--;
      livro->exemplaresDisponiveis++;
    }
     
}

int renovarEmprestimo(Livro *livro, char *nomeLeitor, int novoDia, int novoMes, int novoAno){
char nomeBusca[50];
    strcpy(nomeBusca, nomeLeitor);
    diminuir(nomeBusca); 
    for (int i = 0; i < livro->quantidadeEmprestimosRegistrados; i++) {
        char nomeHistorico[50];
        strcpy(nomeHistorico, livro->historicoEmprestimos[i].nomeLeitor);
        diminuir(nomeHistorico);

        if (strcmp(nomeHistorico, nomeBusca) == 0 && livro->historicoEmprestimos[i].devolvido == 0) {
            
            
            livro->historicoEmprestimos[i].dataEmprestimo.dia = novoDia;
            livro->historicoEmprestimos[i].dataEmprestimo.mes = novoMes;
            livro->historicoEmprestimos[i].dataEmprestimo.ano = novoAno;
            
            return 1; 
        }
    }
    printf("\n--Leitor não encontrado, verifique se o nome digitado está correto--\n");
    return 0; 
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