#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ACERVO 20

typedef struct {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
} Livro;

void exibirMenu();
void cadastrarLivros(Livro acervo[], int *numLivros);
void imprimirLivros(const Livro acervo[], int numLivros);
void pesquisarLivro(const Livro acervo[], int numLivros, int codigoBusca);
void ordenarLivros(Livro acervo[], int numLivros);
void limparBuffer();

int main() {
    
    Livro acervo[TAMANHO_ACERVO];
    int opcao;

    int numLivros = 0; 

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Por favor, digite um numero.\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarLivros(acervo, &numLivros);
                break;
            case 2:
                imprimirLivros(acervo, numLivros);
                break;
            case 3:
                pesquisarLivro(acervo, numLivros, 0); 
                break;
            case 4:
                ordenarLivros(acervo, numLivros);
                break;
            case 5:
                printf("\nSaindo do programa. Ate mais!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao entre 1 e 5.\n");
                break;
        }
        printf("\n----------------------------------------\n");
    } while (opcao != 5);

    return 0;
}

void exibirMenu() {
    printf("\n==== Sistema de Gerenciamento de Livros ====\n");
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir todos os livros\n");
    printf("3 - Pesquisar livro por codigo\n");
    printf("4 - Ordenar livros por ano de publicacao\n");
    printf("5 - Sair do programa\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarLivros(Livro acervo[], int *numLivros) {
    int i;
    int maxCadastro;
    
    if (*numLivros >= TAMANHO_ACERVO) {
        printf("\nO acervo esta cheio! Maximo de %d livros atingido.\n", TAMANHO_ACERVO);
        return;
    }
    
    printf("\nQuantos livros deseja cadastrar (maximo %d)? ", TAMANHO_ACERVO - *numLivros);
    if (scanf("%d", &maxCadastro) != 1 || maxCadastro <= 0) {
        printf("\nQuantidade invalida. Tente novamente.\n");
        limparBuffer();
        return;
    }
     
    if (*numLivros + maxCadastro > TAMANHO_ACERVO) {
        maxCadastro = TAMANHO_ACERVO - *numLivros;
        printf("Ajustando: Serão cadastrados %d livros.\n", maxCadastro);
    }
    
    for (i = 0; i < maxCadastro; i++) {
        printf("\n--- Cadastro do Livro %d ---\n", *numLivros + 1);
        
        printf("Codigo (int): ");
        if (scanf("%d", &acervo[*numLivros].codigo) != 1) {
            printf("Erro na leitura do codigo. Cadastro interrompido.\n");
            limparBuffer();
            return;
        }
        limparBuffer(); 
        
        printf("Titulo (max 49 caracteres): ");

        fgets(acervo[*numLivros].titulo, sizeof(acervo[*numLivros].titulo), stdin);
        acervo[*numLivros].titulo[strcspn(acervo[*numLivros].titulo, "\n")] = 0; // Remove '\n'
        
        printf("Autor (max 29 caracteres): ");
        fgets(acervo[*numLivros].autor, sizeof(acervo[*numLivros].autor), stdin);
        acervo[*numLivros].autor[strcspn(acervo[*numLivros].autor, "\n")] = 0;
        
        printf("Area (max 29 caracteres): ");
        fgets(acervo[*numLivros].area, sizeof(acervo[*numLivros].area), stdin);
        acervo[*numLivros].area[strcspn(acervo[*numLivros].area, "\n")] = 0;
        
        printf("Ano de Publicacao (int): ");
        if (scanf("%d", &acervo[*numLivros].ano) != 1) {
            printf("Erro na leitura do ano. Cadastro interrompido.\n");
            limparBuffer();
            return;
        }
        limparBuffer();
        
        printf("Editora (max 29 caracteres): ");
        fgets(acervo[*numLivros].editora, sizeof(acervo[*numLivros].editora), stdin);
        acervo[*numLivros].editora[strcspn(acervo[*numLivros].editora, "\n")] = 0;

        (*numLivros)++;
    }
    
    printf("\n%d livro(s) cadastrado(s) com sucesso!\n", maxCadastro);
}

void imprimirLivros(const Livro acervo[], int numLivros) {
    int i;
    
    if (numLivros == 0) {
        printf("\nO acervo esta vazio. Cadastre livros primeiro.\n");
        return;
    }
    
    printf("\n==== Lista Completa do Acervo (%d Livro(s)) ====\n", numLivros);
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("| Codigo | Titulo                                        | Autor                   | Area                    | Ano  | Editora                 |\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < numLivros; i++) {
        printf("| %-6d | %-45.45s | %-21.21s | %-21.21s | %-4d | %-23.23s |\n",
               acervo[i].codigo, 
               acervo[i].titulo, 
               acervo[i].autor, 
               acervo[i].area, 
               acervo[i].ano, 
               acervo[i].editora);
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}

void pesquisarLivro(const Livro acervo[], int numLivros, int codigoBusca) {
    
    if (numLivros == 0) {
        printf("\nO acervo esta vazio. Nao ha livros para pesquisar.\n");
        return;
    }
    
    if (codigoBusca == 0) {
        printf("\nDigite o codigo do livro a ser pesquisado: ");
        if (scanf("%d", &codigoBusca) != 1) {
            printf("Erro na leitura do codigo.\n");
            limparBuffer();
            return;
        }
    }
    
    printf("\n---- Resultado da Pesquisa por Codigo %d ----\n", codigoBusca);

    while (i < numLivros) {
        if (acervo[i].codigo == codigoBusca) {
            printf("LIVRO ENCONTRADO!\n");
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1; 
            break; 
        }
        i++;
    }
    
    if (!encontrado) {
        printf("Livro com codigo %d nao encontrado no acervo.\n", codigoBusca);
    }
}

void ordenarLivros(Livro acervo[], int numLivros) {
    int i, j;
    Livro temp;
    
    if (numLivros < 2) {
        printf("\nSao necessarios pelo menos 2 livros para ordenar.\n");
        return;
    }
    
    printf("\nOrdenando livros por Ano de Publicacao (Crescente) usando Bubble Sort...\n");
    
    for (i = 0; i < numLivros - 1; i++) {
        for (j = 0; j < numLivros - 1 - i; j++) {
            if (acervo[j].ano > acervo[j+1].ano) {
                temp = acervo[j];
                acervo[j] = acervo[j+1];
                acervo[j+1] = temp;
            }
        }
    }
    
    printf("Ordenacao concluida com sucesso.\n");
    imprimirLivros(acervo, numLivros);
}
