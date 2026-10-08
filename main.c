#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcoes.h"
#include <ctype.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    char salvar;
    int quantidade = 0;
    float multa;
    int codigo, novo_valor, dia, mes, ano, sucesso, opcao, diasPerm;
    char nome_leitor[50];
    Livro *livroEncontrado = NULL;
    Livro *livroAux = NULL;
    char arquivo[] = "acervo_biblioteca.txt";
    Livro *acervo = NULL;
    quantidade = carregarAcervo(&acervo, arquivo);

    do
    {
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
        printf("[10] - renovar emprestimo\n");
        printf("[11] - Devolução de livro\n");
        printf("[12] - reservar livro\n");
        printf("[13] - calcular multa por atraso de entrega\n");
        printf("[14] - relatorio de livros mais emprestados\n");
        printf("[15] - Estatísticas do acervo\n");
        printf("[0]- Sair \n");
        printf("digite uma das opcoes..:");
        
        if (scanf("%d", &opcao) != 1){
              printf ("Opcao invalida! digite apenas numeros.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
            switch (opcao)
            {
            case 1:
                livroAux = cadastrarLivro(acervo, quantidade);
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

            case 2:
                listarTodos(acervo, quantidade);
                break;

            case 3:
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
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

            case 4: /*atualizar exemplares.*/
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                if (livroEncontrado != NULL)
                {
                    printf ("Novo numero de exemplares:\n");
                    if (scanf("%d", &novo_valor) !=1){
                        printf("entrada invalida, digite apenas numeros\n");
                        while (getchar() != '\n');
                        break;
                    }
                    atualizarExemplaresDisponiveis (livroEncontrado, novo_valor);
                }
                else
                {
                    printf("Livro com código %d não encontrado.\n", codigo);
                }
                break;

            case 5: /*Remover livro*/
                codigoLivro(&codigo);
                if (removerLivro(&acervo, &quantidade, codigo)){
                    printf ("Livro removido com sucesso!\n");
                } else {
                    printf ("Livro não encontrado!\n");
                }
                break;

            case 6:
                salvarAcervo(acervo, quantidade, arquivo);
                break;

            case 7:
                liberarAcervo(&acervo, &quantidade);
                quantidade = carregarAcervo(&acervo, arquivo);   
                break;
                
            case 8:
                liberarAcervo (&acervo, &quantidade);
                printf("Acervo liberado, pronto para receber novos livros!!\n");
                break;

            case 9:
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
              if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
                    solicitarData(&dia,&mes,&ano);
                    solicitarNome(nome_leitor);
                    registrarEmprestimo(livroEncontrado, nome_leitor, dia, mes, ano);
                break;
            case 10:
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                 if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
                solicitarData(&dia,&mes,&ano);
                solicitarNome(nome_leitor);
                renovarEmprestimo(livroEncontrado, nome_leitor, dia, mes, ano);
                break;

            case 11:
              codigoLivro(&codigo);
              livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
              if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
                solicitarNome(nome_leitor);
              devolverLivro(livroEncontrado, nome_leitor);
                break;

            case 12:
            codigoLivro(&codigo);
            livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
              if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
              printf("quem deseja reservar o livro?:\n");
                    solicitarNome(nome_leitor);
              sucesso = reservarLivroEmprestado(livroEncontrado,nome_leitor);
               if (sucesso != -1)
               {
                 printf("livro registrado com sucesso, posição %d da fila", sucesso + 1);
               }
                break;
               
            case 13:
               codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
               if(!verificaSeLivroExiste(livroEncontrado))
               {
                  break;
               }
               solicitarNome(nome_leitor);
               solicitarData(&dia,&mes,&ano);
               printf("quantos dia foram permitidos para esse emprestimo?;\n");
               if (scanf("%d", &diasPerm) != 1)
               {
                   printf("entrada invalida, digite apenas numeros\n");
                   while (getchar() != '\n');
                   break;
               }
               multa = calcularMultaAtraso(livroEncontrado,nome_leitor,dia,mes,ano,diasPerm);
               if (multa < 0) {
                printf("leitor nao encontrado.\n");
                }
               else if (multa ==0) {
               printf ("Sem atraso, nenhuma multa a pagar.\n");
                } else {
               printf("valor a pagar pelos dias atrasados: %.2f", multa);
                }
                break;
            
            case 14:
               relatorioLivrosMaisEmprestados(acervo, quantidade);
               break;
            case 15:
               estatiscasDoAcervo (acervo, quantidade);
               break;
            case 0:
                printf ("Deseja salvar o acervo antes de sair? [s/n] : ");
                scanf  (" %c", &salvar);
                scanf("%*[^\n]");
                salvar = tolower(salvar);
                if (salvar == 's')
                {
                    salvarAcervo(acervo, quantidade, arquivo);
                }
                if (salvar == 'n')
                {
                    printf ("Acervo não salvo!\n");
                }
                printf("[FECHANDO PROGRAMA...]\n");
                exit(0);
                break;

            default:
                break;
            }
        

    } while (opcao != 0);
}
