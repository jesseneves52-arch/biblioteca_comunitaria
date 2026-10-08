#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcoes.h"
#include <ctype.h>

int main()
{

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

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
        limparTela();
        if (quantidade > 0)
        {
            printf("%d livros carregados.\n", quantidade);
        }
        else
        {
            printf(" Nenhum livro salvo no acervo.\n");
        }
        printf("\n========================================\n");
        printf("              MENU PRINCIPAL           \n");
        printf("========================================\n");
        printf("  %2d. Cadastrar livro\n", 1);
        printf("  %2d. Listar livros\n", 2);
        printf("  %2d. Buscar por código\n", 3);
        printf("  %2d. Atualizar exemplares\n", 4);
        printf("  %2d. Remover livro\n", 5);
        printf("  %2d. Salvar acervo\n", 6);
        printf("  %2d. Carregar acervo\n", 7);
        printf("  %2d. Liberar acervo\n", 8);
        printf("  %2d. Registrar empréstimos\n", 9);
        printf("  %2d. Renovar empréstimo\n", 10);
        printf("  %2d. Devolução de livro\n", 11);
        printf("  %2d. Reservar livro\n", 12);
        printf("  %2d. Calcular multa por atraso\n", 13);
        printf("  %2d. Relatório de mais emprestados\n", 14);
        printf("  %2d. Estatísticas do acervo\n", 15);
        printf("  %2d. Sair\n", 0);
        printf("----------------------------------------\n");
        printf("Digite uma das opcoes: ");
        if (scanf("%d", &opcao) != 1){
              printf("[ERRO] Opção inválida. Digite apenas números.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }
        while (getchar() != '\n');
            switch (opcao)
            {
            case 1:
                livroAux = cadastrarLivro(acervo, quantidade);
                if (livroAux == NULL)
                {
                    printf("[ERRO] Falha ao cadastrar livro.\n");
                    break;
                }
                if (adicionarAoVetor(&acervo, &quantidade, *livroAux))
                {
                    printf("Livro adicionado ao acervo.\n");
                }
                else
                {
                    printf("[ERRO] Falha ao adicionar livro.\n");
                }
                free(livroAux);
                pausarEContinuar();
                break;

            case 2:
                listarTodos(acervo, quantidade);
                pausarEContinuar();
                break;

            case 3:
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                if (livroEncontrado != NULL)
                {
                    printf("\nLIVRO ENCONTRADO\n");
                    printf("--------------------\n");
                    printf("  Código               : %d\n", livroEncontrado->codigo);
                    printf("  Título               : %s\n", livroEncontrado->titulo);
                    printf("  Autor                : %s\n", livroEncontrado->autor);
                    printf("  Gênero               : %s\n", livroEncontrado->genero);
                   printf("  Exemplares disponíveis: %d\n", livroEncontrado->exemplaresDisponiveis);
                }
                else
                {
                    printf("[ERRO] Livro com código %d não encontrado.\n", codigo);
                }
                pausarEContinuar();
                break;

            case 4: /*atualizar exemplares.*/
                codigoLivro(&codigo);
                livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
                if (livroEncontrado != NULL)
                {
                    printf ("Novo numero de exemplares:\n");
                    if (scanf("%d", &novo_valor) !=1){
                        printf("[ERRO] Entrada inválida. Digite apenas números.\n");
                        while (getchar() != '\n');
                        break;
                    }
                    atualizarExemplaresDisponiveis (livroEncontrado, novo_valor);
                }
                else
                {
                    printf("[ERRO] Livro com código %d não encontrado.\n", codigo);
                }
                pausarEContinuar();
                break;

            case 5: /*Remover livro*/
                codigoLivro(&codigo);
                if (removerLivro(&acervo, &quantidade, codigo)){
                    printf ("Livro removido.\n");
                } else {
                    printf ("[ERRO] Livro não encontrado.\n");
                }
                pausarEContinuar();
                break;

            case 6:
                salvarAcervo(acervo, quantidade, arquivo);
                pausarEContinuar();
                break;

            case 7:
                liberarAcervo(&acervo, &quantidade);
                quantidade = carregarAcervo(&acervo, arquivo);
                pausarEContinuar();
                break;
                
            case 8:
                liberarAcervo (&acervo, &quantidade);
                printf("Acervo liberado.\n");
                pausarEContinuar();
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
                pausarEContinuar();
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
                pausarEContinuar();
                break;

            case 11:
              codigoLivro(&codigo);
              livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
              if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
                solicitarNome(nome_leitor);
              devolverLivro(livroEncontrado, nome_leitor);
              pausarEContinuar();
                break;

            case 12:
            codigoLivro(&codigo);
            livroEncontrado = buscarPorCodigo(acervo, quantidade, codigo);
              if(!verificaSeLivroExiste(livroEncontrado)){
                  break;
              }
              printf("Quem deseja reservar o livro?:\n");
                    solicitarNome(nome_leitor);
              sucesso = reservarLivroEmprestado(livroEncontrado,nome_leitor);
               if (sucesso != -1)
               {
                 printf("Livro registrado com sucesso, posição %d da fila", sucesso + 1);
               }
            pausarEContinuar();
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
               printf("Quantos dias foram permitidos para esse emprestimo?;\n");
               if (scanf("%d", &diasPerm) != 1)
               {
                   printf("Entrada invalida, digite apenas numeros\n");
                   while (getchar() != '\n');
                   break;
               }
               multa = calcularMultaAtraso(livroEncontrado,nome_leitor,dia,mes,ano,diasPerm);
               if (multa < 0) {
                printf("[ERRO] Leitor não encontrado.\n");
                }
               else if (multa ==0) {
               printf ("Sem atraso. Nenhuma multa a pagar.\n");
                } else {
               printf("Valor a pagar pelos dias atrasados: %.2f", multa);
                }
            pausarEContinuar();
                break;
            
            case 14:
               relatorioLivrosMaisEmprestados(acervo, quantidade);
               pausarEContinuar();
               break;
            case 15:
               estatiscasDoAcervo (acervo, quantidade);
               pausarEContinuar();
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
                    printf ("Acervo não salvo.\n");
                }
                printf("[FECHANDO PROGRAMA...]\n");
                exit(0);
               
                break;

            default:
            printf ("[ERRO]Opção inválida! Digite um número de 0 a 15.\n");
                break;
            pausarEContinuar();
            }
        

    } while (opcao != 0);
}
