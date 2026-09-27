#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main()
{   int quantidade = 0;
    char opcao[10];
     Livro *acervo = NULL;
    do
    {

        getchar();
        printf("\n===========MENU===========\n");
        printf("[1] - Cadastrar livro\n");
        printf("[2] - Listar livro\n");
        printf("[3] - Buscar por código\n");
        printf("[4] - Atualizar Exemplares\n");
        printf("[5] - Remover livro\n");
        printf("[6] - Salvar acervo\n");
        printf("[7] - Carregar acervo\n");
        printf("[8] - Liberar acervo\n");
        printf("[0]- Sair \n");
        printf("digite uma das opcoes..:");
        scanf(" %9s", opcao);
        scanf("%*[^\n]");
        if (strlen(opcao) != 1)
        {
            printf("Opção inválida! digite um número de 1 a 8, ou 0 para.\n");
        } else
        {
            switch (opcao[0])
            {
            case 1:
                cadastrarLivro(quantidade);
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

                break;
            case 0:

                break;

            default:
                break;
            }
        }

            
    } while (opcao == 0);
    
}
