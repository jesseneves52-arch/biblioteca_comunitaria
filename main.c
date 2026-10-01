#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcoes.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int quantidade = 0;
    char opcao[10];
    char arquivo[] = "acervo_biblioteca.txt";
    Livro *acervo = NULL;
    quantidade = carregarAcervo(acervo, arquivo);

    do
    {

        getchar();
        if (quantidade > 0)
        {
            printf("foram carregados %d livros\n", quantidade);
        }
        else
        {
            printf("Nenhum livro salvo no acervo\n");
        }
        printf("\n===========MENU===========\n");
        printf("[1] - Cadastrar livro\n");
        printf("[2] - Listar livros\n");
        printf("[3] - Buscar por código\n");
        printf("[4] - Atualizar Exemplares\n");
        printf("[5] - Remover livro\n");
        printf("[6] - Salvar acervo\n");
        printf("[7] - Carregar acervo\n");
        printf("[8] - Liberar acervo\n");
        printf("[9] - registrar emprestimos\n");
        printf("[10]");
        printf("[11]");
        printf("[12]");
        printf("[13]");
        printf("[14]");
        printf("[0]- Sair \n");
        printf("digite uma das opcoes..:");
        scanf(" %9s", opcao);
        scanf("%*[^\n]");
        if (strlen(opcao) != 1)
        {
            printf("Opção inválida! digite um número de 1 a 8, ou 0 para.\n");
        }
        else
        {
            switch (opcao[0])
            {
            case '1':
                Livro *livroAux = cadastrarLivro(quantidade);
                if (livroAux == NULL)
                {
                    printf("erro ao cadastrar livro\n");
                    break;
                }
                if (adicionarAoVetor(&acervo, &quantidade, *livroAux))
                {
                    printf("Livro adicionado ao acervo com sucesso!!\n");
                }
                else
                {
                    printf("erro ao adicionar livro!!\n");
                }
                free(livroAux);
                break;
            case '2':
                listarTodos(acervo, quantidade);
                break;
            case '3':
                int codigo;
                printf("digite o codigo do livro que deseja buscar: ");
                scanf("%d", &codigo);
                Livro *livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                if (livroEncontrado != NULL)
                {
                    printf("Livro encontrado:\n");
                    printf("Código: %d\n", livroEncontrado->codigo);
                    printf("Título: %s\n", livroEncontrado->titulo);
                    printf("Autor: %s\n", livroEncontrado->autor);
                    printf("Gênero: %s\n", livroEncontrado->genero);
                    printf("Exemplares disponíveis: %d\n", livroEncontrado->exemplaresDisponiveis);
                }
                else
                {
                    printf("Livro com código %d não encontrado.\n", codigo);
                }
                break;
            case '4': /*atualizar exemplares.*/
                int novo_valor;
                printf("Digite o codigo do livro que você queira atualizar.\n");
                scanf("%d", &codigo);
                Livro *livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                if (livroEncontrado != NULL)
                {
                    printf ("Novo numero de exemplares:\n");
                    scanf ("%d", &novo_valor);
                    atualizarExemplaresDisponiveis (livroEncontrado, novo_valor);
                }
                else
                {
                    printf("Livro com código %d não encontrado.\n", codigo);
                }
                break;
            case '5': /*Remover livro*/
                printf("Digite o codigo do livro que você queira remover.\n");
                scanf("%d", &codigo);
                
                
                break;
            case '6':
                salvarAcervo(acervo, quantidade, arquivo);
                break;
            case '7':

                break;
            case '8':

                break;
            case '9':
                int codigoaux,dia, mes,ano;
                 char nome_leitor[50];
                printf("digite o código do livro que será emprestado:\n");
                scanf("%d", &codigoaux);
                if (buscarPorCodigo(acervo,quantidade,codigoaux) == NULL){
                    printf("erro livro não encotrado\n");
                    break;
                }
                    printf("A quem o livro será emprestado:\n");
                    scanf(" %49[^\n]", nome_leitor);
                    printf("digite a data atual:(formato dia|mes|ano):\n");
                    scanf ("%d %d %d", &dia, &mes, &ano);
                    registrarEmprestimo(buscarPorCodigo(acervo, quantidade, codigoaux), nome_leitor, dia, mes, ano);
                break;
            case '10':

                break;
            case '11':

                break;
            case '12':

                break;
            case '13':

                break;
            case '0':
                printf("[FECHANDO PROGRAMA...]\n");
                exit(0);
                break;

            default:
                break;
            }
        }

    } while (opcao[0] != '0');
}
