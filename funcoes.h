#ifndef FUNCOES_H
#define FUNCOES_H
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

typedef struct {
    int codigo;
    char titulo[80];
    char autor[50];
    char genero[30];
    int exemplaresDisponiveis;
    Emprestimo historicoEmprestimos[5];
    int quantidadeEmprestimosRegistrados;
} Livro;





int proximoCodigo(Livro acervo[], int quantidade);
Livro *cadastrarLivro(Livro acervo[], int quantidade);//
int adicionarAoVetor(Livro **acervo, int *quantidade, Livro novoLivro);//
void listarTodos(Livro acervo[], int quantidade);//
Livro *buscarPorCodigo(Livro acervo[], int quantidade,int codigoBuscado);//
void atualizarExemplaresDisponiveis(Livro *item, int novo_valor);//
int removerLivro(Livro **acervo, int *quantidade, int codigo);//
void salvarAcervo(Livro acervo[], int quantidade, char *nomeArquivo);//
int carregarAcervo(Livro **acervo, char *nomeArquivo);//
void liberarAcervo(Livro **acervo, int *quantidade);//
void registrarEmprestimo(Livro *livro, char *nomeLeitor, int dia, int mes, int ano);//
int devolverLivro(Livro *livro, char *nomeLeitor);
int renovarEmprestimo(Livro *livro, char *nomeLeitor, int novoDia, int novoMes, int novoAno);
int reservarLivroEmprestado(Livro *livro, char *nomeLeitor);
float calcularMultaAtraso(Livro *livro, char *nomeLeitor, int diaAtual, int mesAtual, int anoAtual, int diasPermitidos);
void relatorioLivrosMaisEmprestados(Livro acervo[], int quantidade);//
void dadoDoLeitor(char *nomeleitor, int* dia, int *mes, int *ano);//
void codigoLivro(int *codigo);//
int verificaSeLivroExiste(Livro *livro);//
/*ADD FUNÇÃO CALENDARIO*/
#endif