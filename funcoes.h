#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    int codigo;
    char titulo[80];
    char autor[50];
    char genero[30];
    int exemplaresDisponiveis;
    Emprestimo historicoEmprestimos[5];
    int quantidadeEmprestimosRegistrados;
} Livro;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;


typedef struct {
    char nomeLeitor[50];
    Data dataEmprestimo;
    int devolvido;
} Emprestimo;

Livro *cadastrarLivro();
int adicionarAoVetor(Livro **acervo, int *quantidade, Livro novoLivro);
void listarTodos(Livro acervo[], int quantidade);
Livro *buscarPorCodigo(Livro acervo[], int quantidade,int codigoBuscado);
void atualizarExemplaresDisponiveis(Livro *item, int novo_valor);
int removerLivro(Livro **acervo, int *quantidade, int codigo);
void salvarAcervo(Livro acervo[], int quantidade, char *nomeArquivo);
int carregarAcervo(Livro acervo[], char *nomeArquivo);
void liberarAcervo(Livro **acervo, int *quantidade);
/*ADD FUNÇÃO CALENDARIO*/
#endif