#include <stdio.h>
#include <stdlib.h> // Para a função exit()
#include <string.h> // Para as funções de manipulação de strings (strcmp, strcpy)

// --- Etapa 1: Definição de Constantes e Estruturas ---

/**
 * @brief Constante que define o tamanho máximo do acervo de livros.
 */
#define TAMANHO_ACERVO 20

/**
 * @brief Estrutura para armazenar os dados de um livro.
 * Contém campos para código, título, autor, área, ano e editora.
 */
typedef struct {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
} Livro;

// --- Assinaturas das Funções (Protótipos) ---

void exibirMenu();
void cadastrarLivros(Livro acervo[], int *numLivros);
void imprimirLivros(const Livro acervo[], int numLivros);
void pesquisarLivro(const Livro acervo[], int numLivros, int codigoBusca);
void ordenarLivros(Livro acervo[], int numLivros);
void limparBuffer(); // Função auxiliar para limpar o buffer de entrada

// --- Função Principal (main) ---

int main() {
    // Declaração do vetor de structs para o acervo e variáveis auxiliares
    Livro acervo[TAMANHO_ACERVO];
    int opcao;
    // Variável para rastrear o número real de livros cadastrados,
    // que é essencial para percorrer apenas os elementos válidos do vetor.
    int numLivros = 0; 

    // Estrutura de repetição para manter o menu ativo até que o usuário escolha sair
    do {
        exibirMenu(); // Chama a função para exibir as opções
        printf("Escolha uma opcao: ");
        // Leitura da opção do usuário. O ideal é verificar o retorno de scanf.
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Por favor, digite um numero.\n");
            limparBuffer(); // Limpa o buffer em caso de erro de leitura
            continue;
        }

        // Estrutura condicional (switch-case) para tomar decisões
        switch (opcao) {
            case 1:
                cadastrarLivros(acervo, &numLivros);
                break;
            case 2:
                imprimirLivros(acervo, numLivros);
                break;
            case 3:
                // Pesquisa exige um código, que será solicitado dentro da função.
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

// --- Funções de Implementação (Etapa 2) ---

/**
 * @brief Exibe o menu de opções para o usuário.
 */
void exibirMenu() {
    printf("\n==== Sistema de Gerenciamento de Livros ====\n");
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir todos os livros\n");
    printf("3 - Pesquisar livro por codigo\n");
    printf("4 - Ordenar livros por ano de publicacao\n");
    printf("5 - Sair do programa\n");
}

/**
 * @brief Limpa o buffer de entrada (stdin) para evitar problemas de leitura.
 * Utiliza o loop para consumir todos os caracteres restantes até um newline (\n) ou EOF.
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Permite ao bibliotecário cadastrar novos livros no acervo.
 * Utiliza a variável 'numLivros' para saber onde começar o cadastro e quantos livros já existem.
 * * @param acervo Vetor de structs Livro.
 * @param numLivros Ponteiro para o contador de livros cadastrados.
 */
void cadastrarLivros(Livro acervo[], int *numLivros) {
    int i;
    int maxCadastro;
    
    // Verifica se o acervo está cheio
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
    
    // Ajusta o número de cadastros para não exceder o limite do acervo
    if (*numLivros + maxCadastro > TAMANHO_ACERVO) {
        maxCadastro = TAMANHO_ACERVO - *numLivros;
        printf("Ajustando: Serão cadastrados %d livros.\n", maxCadastro);
    }
    
    // Estrutura de repetição para percorrer o vetor e preencher as structs
    for (i = 0; i < maxCadastro; i++) {
        printf("\n--- Cadastro do Livro %d ---\n", *numLivros + 1);
        
        // --- Leitura do Código (int) ---
        printf("Codigo (int): ");
        if (scanf("%d", &acervo[*numLivros].codigo) != 1) {
            printf("Erro na leitura do codigo. Cadastro interrompido.\n");
            limparBuffer();
            return;
        }
        limparBuffer(); // Limpa o buffer após ler o inteiro
        
        // --- Leitura de Strings (char[]) ---
        
        printf("Titulo (max 49 caracteres): ");
        // Usamos fgets para ler a linha inteira, incluindo espaços, e evitar problemas de buffer.
        // O '\n' final de fgets deve ser removido.
        fgets(acervo[*numLivros].titulo, sizeof(acervo[*numLivros].titulo), stdin);
        acervo[*numLivros].titulo[strcspn(acervo[*numLivros].titulo, "\n")] = 0; // Remove '\n'
        
        printf("Autor (max 29 caracteres): ");
        fgets(acervo[*numLivros].autor, sizeof(acervo[*numLivros].autor), stdin);
        acervo[*numLivros].autor[strcspn(acervo[*numLivros].autor, "\n")] = 0;
        
        printf("Area (max 29 caracteres): ");
        fgets(acervo[*numLivros].area, sizeof(acervo[*numLivros].area), stdin);
        acervo[*numLivros].area[strcspn(acervo[*numLivros].area, "\n")] = 0;
        
        // --- Leitura do Ano (int) ---
        printf("Ano de Publicacao (int): ");
        if (scanf("%d", &acervo[*numLivros].ano) != 1) {
            printf("Erro na leitura do ano. Cadastro interrompido.\n");
            limparBuffer();
            return;
        }
        limparBuffer(); // Limpa o buffer após ler o inteiro
        
        // --- Leitura da Editora (char[]) ---
        printf("Editora (max 29 caracteres): ");
        fgets(acervo[*numLivros].editora, sizeof(acervo[*numLivros].editora), stdin);
        acervo[*numLivros].editora[strcspn(acervo[*numLivros].editora, "\n")] = 0;

        // Incrementa o número de livros cadastrados a cada iteração bem-sucedida
        (*numLivros)++;
    }
    
    printf("\n%d livro(s) cadastrado(s) com sucesso!\n", maxCadastro);
}

/**
 * @brief Imprime os dados de todos os livros cadastrados no acervo.
 *
 * @param acervo Vetor de structs Livro.
 * @param numLivros Número real de livros cadastrados.
 */
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

    // Estrutura de repetição para percorrer apenas os livros válidos
    for (i = 0; i < numLivros; i++) {
        // Uso de formatadores de largura fixa para manter o alinhamento
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

/**
 * @brief Pesquisa um livro no acervo pelo código.
 *
 * @param acervo Vetor de structs Livro.
 * @param numLivros Número real de livros cadastrados.
 * @param codigoBusca Código a ser pesquisado (0 para solicitar ao usuário).
 */
void pesquisarLivro(const Livro acervo[], int numLivros, int codigoBusca) {
    int i = 0;
    int encontrado = 0; // Flag (estrutura condicional) para verificar se o livro foi encontrado
    
    if (numLivros == 0) {
        printf("\nO acervo esta vazio. Nao ha livros para pesquisar.\n");
        return;
    }
    
    if (codigoBusca == 0) { // Se a função for chamada com código 0, solicita ao usuário
        printf("\nDigite o codigo do livro a ser pesquisado: ");
        if (scanf("%d", &codigoBusca) != 1) {
            printf("Erro na leitura do codigo.\n");
            limparBuffer();
            return;
        }
    }
    
    printf("\n---- Resultado da Pesquisa por Codigo %d ----\n", codigoBusca);

    // Estrutura de repetição (while) para percorrer o vetor
    while (i < numLivros) {
        // Estrutura condicional para verificar a igualdade
        if (acervo[i].codigo == codigoBusca) {
            printf("LIVRO ENCONTRADO!\n");
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1; // Define a flag como verdadeiro
            break; // Sai do loop após encontrar o livro (otimização)
        }
        i++;
    }
    
    // Estrutura condicional final
    if (!encontrado) {
        printf("Livro com codigo %d nao encontrado no acervo.\n", codigoBusca);
    }
}

/**
 * @brief Ordena o vetor de livros pelo campo 'ano' utilizando o algoritmo Bubble Sort (Ordenação da Bolha).
 *
 * @param acervo Vetor de structs Livro.
 * @param numLivros Número real de livros cadastrados.
 */
void ordenarLivros(Livro acervo[], int numLivros) {
    int i, j;
    Livro temp; // Variável temporária do tipo struct Livro para a troca (swap)
    
    if (numLivros < 2) {
        printf("\nSao necessarios pelo menos 2 livros para ordenar.\n");
        return;
    }
    
    printf("\nOrdenando livros por Ano de Publicacao (Crescente) usando Bubble Sort...\n");
    
    // Estruturas de repetição aninhadas (for) para o Bubble Sort
    // Loop externo: Controla o número de passagens
    for (i = 0; i < numLivros - 1; i++) {
        // Loop interno: Percorre os elementos e faz a comparação/troca
        for (j = 0; j < numLivros - 1 - i; j++) {
            // Estrutura condicional: Compara o ano de publicação
            if (acervo[j].ano > acervo[j+1].ano) {
                // Realiza a troca (Swap) de duas structs inteiras
                temp = acervo[j];
                acervo[j] = acervo[j+1];
                acervo[j+1] = temp;
            }
        }
    }
    
    printf("Ordenacao concluida com sucesso.\n");
    imprimirLivros(acervo, numLivros); // Chama a função para exibir o resultado
}