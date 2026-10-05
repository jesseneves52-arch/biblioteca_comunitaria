#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>




void registrarEmprestimo(Livro *livro, char *nomeLeitor, int dia, int mes, int ano){
    char opcao;
    if(livro->quantidadeEmprestimosRegistrados >= 5){
         printf("fila de espera para reservar livro cheia, aguarde!!\n"); 
         return;  
    }
      if (livro->exemplaresDisponiveis <= 0)
    {
       printf("nenhum exemplar disponivel para emprestimo, reservar livro?[s/n]");
       scanf(" %c", &opcao);
       scanf("%*[^\n]");
       opcao = tolower(opcao);
       switch (opcao)
       {
        case 's':
           if(reservarLivroEmprestado(livro, nomeLeitor) != -1){
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
    livro->totalEmprestimos++;
    livro->exemplaresDisponiveis--;
    printf("emprestimo registrado com sucesso\n");
}
int devolverLivro(Livro *livro, char *nomeLeitor){
char nomeBusca[50];
int indice = -1, indiceReserva = -1;
    strcpy(nomeBusca, nomeLeitor);
    diminuir(nomeBusca);
    for (int i = 0; i < livro->quantidadeEmprestimosRegistrados; i++) {
        char nomeHistorico[50];
        strcpy(nomeHistorico, livro->historicoEmprestimos[i].nomeLeitor);
        diminuir(nomeHistorico);
        if (livro->historicoEmprestimos[i].devolvido == 2 && indiceReserva == -1)
        {
          indiceReserva = i;
        }
        if (strcmp(nomeHistorico, nomeBusca) == 0 && livro->historicoEmprestimos[i].devolvido == 0)
        {
        indice = i;
        }
    
    }
    if (indice == -1) {
      printf("Nenhuma pessoa com esse nome foi encontrada\n");
        return 0; 
    }
    if (indiceReserva != -1)
    {
       
     //indice onde ele está e indice de pra onde ele vai
     adicionarLeitor(livro,indiceReserva, indice);
      if (indiceReserva < indice){
            indice--;
        }
    time_t t = time(NULL);
    struct tm *h = localtime(&t);
    Emprestimo *e = &livro->historicoEmprestimos[indice];
    e->dataEmprestimo.dia = h->tm_mday;
    e->dataEmprestimo.mes = h->tm_mon + 1;
    e->dataEmprestimo.ano = h->tm_year + 1900;
    livro->totalEmprestimos++;
    printf("livro repassado para %s\n", e->nomeLeitor);
    }
    else{
      removerLeitor(livro, indice);
      livro->exemplaresDisponiveis++;
    }
    printf("livro devolvido com sucesso\n");
    return 1;
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
            printf ("Emprestimo renovado com sucesso!\n");
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
  char nomeBusca[50];
  strcpy(nomeBusca, nomeLeitor);
  diminuir(nomeBusca);
  for (int i = 0; i < livro->quantidadeEmprestimosRegistrados; i++){
    char nomeHistorico[50];
    strcpy(nomeHistorico, livro->historicoEmprestimos[i].nomeLeitor);
    diminuir(nomeHistorico);
    if (strcmp(nomeHistorico, nomeBusca) == 0 && livro->historicoEmprestimos[i].devolvido == 2)
    {
      printf("Leitor ja esta na fila de espera\n");
      return -1;
    }
  }
   int aux = livro->quantidadeEmprestimosRegistrados;
   strcpy(livro->historicoEmprestimos[aux].nomeLeitor, nomeLeitor);
   //2 = leitor aguardando livro, 0 = não devolvido
   livro->historicoEmprestimos[aux].devolvido = 2;
   livro->quantidadeEmprestimosRegistrados++;
   return aux;//sucesso!
}
float calcularMultaAtraso(Livro *livro, char *nomeLeitor, int diaAtual, int mesAtual, int anoAtual, int diasPermitidos)
{  int atraso;
  float valor;    
   if(livro == NULL) return -1.0f;
     //função que converter a data inteira em dias
    char nomeBusca[50];
    int indice = -1;
    strcpy(nomeBusca, nomeLeitor);
    diminuir(nomeBusca);
    for (int i = 0; i < livro->quantidadeEmprestimosRegistrados; i++) {
        char nomeHistorico[50];
        strcpy(nomeHistorico, livro->historicoEmprestimos[i].nomeLeitor);
        diminuir(nomeHistorico);
        if (strcmp(nomeHistorico, nomeBusca) == 0 && indice == -1 && livro->historicoEmprestimos[i].devolvido == 0)
        {
           indice = i;
          atraso = compararDatas(livro, diaAtual,mesAtual,anoAtual, indice, diasPermitidos);
            return atraso * 2.5f;
        }
       }
       printf("nenhum leitor encontrado\n");
       return -1.0f;

}
void relatorioLivrosMaisEmprestados(Livro acervo[], int quantidade){
    if (quantidade == 0) {
        printf ("Nenhum livro foi registrado.\n");
        return;
    }
    Livro *copia = malloc(quantidade * sizeof(Livro));
    int trocou;
    if (copia == NULL) return;

    for (int i = 0; i < quantidade; i++) {
        copia[i] = acervo[i];
    }

    for (int i = 0; i < quantidade-1; i++)
    { trocou = 0;
        for (int j = 0; j < quantidade - i -1; j++)
        {
            if (copia[j].totalEmprestimos < copia[j+1].totalEmprestimos){
                Livro temp = copia[j];
                copia[j] = copia [j+1];
                copia[j+1] = temp;
                trocou = 1;
            }
        }
         if (!trocou){
            printf("organização completa!!\n");
            break; 
         }
    }
   
    printf ("Lista de livros mais emprestados:\n");
    for (int i=0; i<quantidade; i++){
        printf ("%d. %s: %d emprestimos\n", i+1, copia[i].titulo, copia[i].totalEmprestimos);
    }
free (copia);
}