#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_TOKENS 1000
#define MAX_STRING_LEN 100
#define MAX_ERRORS 100
// Número de palavras-chave e operadores
#define NUM_KEYWORDS 9
#define NUM_ARITHMETIC_OPERATORS 4
#define NUM_RELATIONAL_OPERATORS 6
#define NUM_DELIMITERS 5

// Estrutura para armazenar os erros
char errors[MAX_ERRORS][256];
int error_count = 0;

// Definindo palavras-chave, operadores e delimitadores
const char* KEYWORDS[] = {"if", "for", "while", "break", "printf", "return", "int", "float", "main"};
const char* ARITHMETIC_OPERATORS[] = {"+", "-", "*", "/"};
const char* RELATIONAL_OPERATORS[] = {"==", "!=", "<", ">", "<=", ">="};
const char* ASSIGNMENT_OPERATOR = "=";
const char* DELIMITERS[] = {"(", ")", "{", "}", ";"};

// Alterado o nome de 'TOKEN_TYPE' para 'TOKEN_LABELS'
const char* TOKEN_LABELS[] = {
    "IF", "FOR", "WHILE", "BREAK", "PRINTF", "RETURN", "INT", "FLOAT", "MAIN",
    "IDENTIFIER", "ARITHMETIC_OPERATOR", "RELATIONAL_OPERATOR", "ASSIGNMENT_OPERATOR",
    "DELIMITER", "CONSTANT", "STRING", "NUMBER", "DECIMAL_NUMBER",
    "OPEN_P", "CLOSE_P", "OPEN_K", "CLOSE_K"
};

// Função para verificar se um lexema é uma palavra-chave
int is_keyword(const char *lexeme) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(KEYWORDS[i], lexeme) == 0) {
            return 1; // Palavra-chave encontrada
        }
    }
    return 0;
}

// Função para verificar se o lexema é um operador aritmético
int is_arithmetic_operator(const char *lexeme) {
    for (int i = 0; i < NUM_ARITHMETIC_OPERATORS; i++) {
        if (strcmp(ARITHMETIC_OPERATORS[i], lexeme) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para verificar se o lexema é um operador relacional
int is_relational_operator(const char *lexeme) {
    for (int i = 0; i < NUM_RELATIONAL_OPERATORS; i++) {
        if (strcmp(RELATIONAL_OPERATORS[i], lexeme) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para verificar se o lexema é um operador de atribuição
int is_assignment_operator(const char *lexeme) {
    return strcmp(ASSIGNMENT_OPERATOR, lexeme) == 0;
}

// Função para verificar se o lexema é um delimitador
int is_delimiter(const char *lexeme) {
    if (strcmp(lexeme, "(") == 0) {
        printf("%s ---------- OPEN_P\n", lexeme);
        return 1;
    }
    if (strcmp(lexeme, ")") == 0) {
        printf("%s ---------- CLOSE_P\n", lexeme);
        return 1;
    }
    if (strcmp(lexeme, "{") == 0) {
        printf("%s ---------- OPEN_K\n", lexeme);
        return 1;
    }
    if (strcmp(lexeme, "}") == 0) {
        printf("%s ---------- CLOSE_K\n", lexeme);
        return 1;
    }
    if (strcmp(lexeme, ";") == 0) {
        printf("%s ---------- DELIMITER\n", lexeme);
        return 1;
    }
    return 0;
}

// Função para verificar se o lexema é um número inteiro
int is_integer(const char *lexeme) {
    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (!isdigit(lexeme[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para verificar se o lexema é um número decimal
int is_decimal(const char *lexeme) {
    int dot_count = 0;
    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (lexeme[i] == '.') {
            dot_count++;
        } else if (!isdigit(lexeme[i])) {
            return 0;
        }
    }
    return dot_count == 1;
}

// Função para verificar se o lexema é uma string
int is_string(const char *lexeme) {
    return lexeme[0] == '"' && lexeme[strlen(lexeme)-1] == '"';
}

// Função de análise léxica
void analisador_lexico(const char *line) {
    char lexeme[MAX_STRING_LEN];
    int lexeme_index = 0;
    int i = 0;
   
    // Percorrer a linha e identificar tokens
    while (line[i] != '\0') {
        // Ignora espaços em branco
        if (isspace(line[i])) {
            i++;
            continue;
        }

        // Identificar strings entre aspas
        if (line[i] == '"') {
            i++;
            while (line[i] != '"' && line[i] != '\0') {
                lexeme[lexeme_index++] = line[i++];
            }
            lexeme[lexeme_index] = '\0';
            printf("\"%s\" ---------- STRING\n", lexeme);
            lexeme_index = 0;
            i++; // Avançar para o próximo caractere após as aspas
            continue;
        }

        // Construir o lexema (identificador, constante, operador, etc.)
        if (isalnum(line[i]) || line[i] == '_') {
            lexeme[lexeme_index++] = line[i];
            i++;
            while (isalnum(line[i]) || line[i] == '_') {
                lexeme[lexeme_index++] = line[i++];
            }
            lexeme[lexeme_index] = '\0';

            if (is_keyword(lexeme)) {
                if (strcmp(lexeme, "if") == 0) {
                    printf("%s ---------- IF\n", lexeme);
                } else if (strcmp(lexeme, "for") == 0) {
                    printf("%s ---------- FOR\n", lexeme);
                } else if (strcmp(lexeme, "while") == 0) {
                    printf("%s ---------- WHILE\n", lexeme);
                } else if (strcmp(lexeme, "break") == 0) {
                    printf("%s ---------- BREAK\n", lexeme);
                } else if (strcmp(lexeme, "printf") == 0) {
                    printf("%s ---------- PRINTF\n", lexeme);
                } else if (strcmp(lexeme, "return") == 0) {
                    printf("%s ---------- RETURN\n", lexeme);
                } else if (strcmp(lexeme, "int") == 0) {
                    printf("%s ---------- INT\n", lexeme);
                } else if (strcmp(lexeme, "float") == 0) {
                    printf("%s ---------- FLOAT\n", lexeme);
                } else if (strcmp(lexeme, "main") == 0) {
                    printf("%s ---------- MAIN\n", lexeme);
                }
            } else if (is_arithmetic_operator(lexeme)) {
                printf("%s ---------- ARITHMETIC_OPERATOR\n", lexeme);
            } else if (is_relational_operator(lexeme)) {
                printf("%s ---------- RELATIONAL_OPERATOR\n", lexeme);
            } else if (is_assignment_operator(lexeme)) {
                printf("%s ---------- ASSIGNMENT_OPERATOR\n", lexeme);
            } else if (is_delimiter(lexeme)) {
                // Delimitadores já classificados dentro da função is_delimiter
            } else if (is_integer(lexeme)) {
                printf("%s ---------- NUMBER\n", lexeme);
            } else if (is_decimal(lexeme)) {
                printf("%s ---------- DECIMAL_NUMBER\n", lexeme);
            } else {
                printf("%s ---------- IDENTIFIER\n", lexeme);
            }

            lexeme_index = 0; // Reset lexeme index após processar
        } else {
            // Se for um operador ou delimitador de um caractere
            char op[2] = {line[i], '\0'};
            if (i + 1 < strlen(line) && (line[i] == '=' || line[i] == '!')) {
                op[1] = line[i + 1];
                op[2] = '\0';
                if (is_relational_operator(op)) {
                    printf("%s ---------- RELATIONAL_OPERATOR\n", op);
                    i++; // Avançar o índice ao encontrar operador de 2 caracteres
                }
            } else {
                if (is_arithmetic_operator(op)) {
                    printf("%s ---------- ARITHMETIC_OPERATOR\n", op);
                } else if (is_relational_operator(op)) {
                    printf("%s ---------- RELATIONAL_OPERATOR\n", op);
                } else if (is_assignment_operator(op)) {
                    printf("%s ---------- ASSIGNMENT_OPERATOR\n", op);
                } else if (is_delimiter(op)) {
                    // Delimitadores já classificados dentro da função is_delimiter
                }
            }
            i++; // Avançar para o próximo caractere
        }
    }
}
void imprimir_erros() {
    if (error_count == 0) {
        printf("Análise sintática sem erros.\n");
    } else {
        printf("\nTotal de erros sintáticos: %d\n", error_count);
        for (int i = 0; i < error_count; i++) {
            printf("%s\n", errors[i]);
        }
    }
}

// Função de análise sintática
void analisador_sintatico(const char *codigo) {
    char linha[1024];               // Variável para armazenar uma linha do código
    int open_braces = 0;            // Contagem de chaves { }
    int open_parentheses = 0;       // Contagem de parênteses ( )
    int open_quotes_double = 0;     // Contagem de aspas duplas "
    int open_quotes_single = 0;     // Contagem de aspas simples '
    int line_number = 1;            // Contagem de linhas
    int erro = 0;                   // Flag para identificar erros

    // Ponteiro para percorrer o código linha por linha
    const char *ptr = codigo;

    // Enquanto houver linhas no código
    while (*ptr != '\0') {
        // Extrai uma linha do código
        int i = 0;
        while (*ptr != '\0' && *ptr != '\n' && i < sizeof(linha) - 1) {
            linha[i++] = *ptr++;
        }
        linha[i] = '\0'; // Termina a string da linha


        // Ignora a linha em branco
        if (strlen(linha) == 0) {
            if (*ptr == '\n') ptr++;  // Avança para a próxima linha
            line_number++;
            continue;
        }

        // Processa os comentários (linha começa com "//")
        if (strstr(linha, "//") != NULL) {
            *strstr(linha, "//") = '\0';  // Remove o comentário da linha
        }

        // Verifica se a linha termina com '{', '}', ou ';'
        int last_char = linha[strlen(linha) - 1];
        if (last_char != '{' && last_char != '}' && last_char != ';') {
            printf("Erro sintático: Linha %d deve terminar com ';'.\n", line_number);
            erro = 1;
        }

        // Conta e verifica o balanceamento de chaves, parênteses e aspas
        for (int j = 0; j < strlen(linha); j++) {
            char c = linha[j];

            if (c == '{') {
                open_braces++;
            } else if (c == '}') {
                open_braces--;
                if (open_braces < 0) {
                    printf("Erro sintático: '}' inesperado na linha %d.\n", line_number);
                    erro = 1;
                    open_braces = 0;  // Reset para continuar
                }
            } else if (c == '(') {
                open_parentheses++;
            } else if (c == ')') {
                open_parentheses--;
                if (open_parentheses < 0) {
                    printf("Erro sintático: ')' inesperado na linha %d.\n", line_number);
                    erro = 1;
                    open_parentheses = 0;  // Reset para continuar
                }
            } else if (c == '"') {
                open_quotes_double = !open_quotes_double; // Alterna o estado das aspas duplas
            } else if (c == '\'') {
                open_quotes_single = !open_quotes_single; // Alterna o estado das aspas simples
            }
        }

        // Avança para a próxima linha
        if (*ptr == '\n') {
            ptr++;
            line_number++;
        }
    }

    // Verificação final de balanceamento
    if (open_braces != 0) {
        printf("Erro sintático: número de chaves desbalanceado. Faltando '%d' chaves '}'.\n", open_braces);
        erro = 1;
    }
    if (open_parentheses != 0) {
        printf("Erro sintático: número de parênteses desbalanceado. Faltando '%d' parênteses ')'.\n", open_parentheses);
        erro = 1;
    }
    if (open_quotes_double != 0) {
        printf("Erro sintático: aspas duplas não fechadas.\n");
        erro = 1;
    }
    if (open_quotes_single != 0) {
        printf("Erro sintático: aspas simples não fechadas.\n");
        erro = 1;
    }

    if (!erro) {
        // Exibe apenas se não houver erros
        printf("Análise sintática sem erros.\n");
    }
}

void remover_comentarios(char *codigo) {
    char resultado[1024];  // Buffer para armazenar o código sem comentários
    int i = 0, j = 0;
    int in_comentario_bloco = 0;  // Flag para verificar se estamos dentro de um comentário de bloco
    int in_comentario_linha = 0;  // Flag para verificar se estamos dentro de um comentário de linha
    
    while (codigo[i] != '\0') {
        // Se estamos dentro de um comentário de bloco
        if (in_comentario_bloco) {
            if (codigo[i] == '*' && codigo[i + 1] == '/') {
                in_comentario_bloco = 0;  // Finaliza o comentário de bloco
                i++;  // Pula o caractere '/'
            }
        }
        // Se estamos dentro de um comentário de linha
        else if (in_comentario_linha) {
            if (codigo[i] == '\n') {
                in_comentario_linha = 0;  // Finaliza o comentário de linha
            }
        }
        // Verifica se encontramos um início de comentário de bloco
        else if (codigo[i] == '/' && codigo[i + 1] == '*') {
            in_comentario_bloco = 1;
            i++;  // Pula o caractere '*'
        }
        // Verifica se encontramos um início de comentário de linha
        else if (codigo[i] == '/' && codigo[i + 1] == '/') {
            in_comentario_linha = 1;
            i++;  // Pula o caractere '/'
        }
        else {
            // Caso não esteja dentro de um comentário, copia o caractere para o resultado
            resultado[j++] = codigo[i];
        }
        i++;
    }
    resultado[j] = '\0';  // Finaliza a string

    // Copia o resultado de volta para o código original
    strcpy(codigo, resultado);
}

// Função de leitura do arquivo
char* ler_arquivo(const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    // Determina o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    // Aloca memória para armazenar o conteúdo do arquivo
    char *conteudo = (char*)malloc(tamanho + 1);
    if (conteudo == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    // Lê o conteúdo do arquivo
    fread(conteudo, 1, tamanho, arquivo);
    conteudo[tamanho] = '\0'; // Garante que a string esteja terminada em NULL

    fclose(arquivo);
    return conteudo;
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // Suporte UTF-8
    const char* nome_arquivo = "codigo.txt";

    char* code = ler_arquivo(nome_arquivo);
    if (code == NULL) {
        return 1; // Se não conseguiu ler o arquivo, retorna erro
    }

    remover_comentarios(code);

    printf("Análise Léxica:\n");
    analisador_lexico(code);  // Aqui você já faz a análise léxica
    printf("\n");

    printf("Análise Sintática:\n");
    analisador_sintatico(code);  // Dentro de analisador_sintatico, você pode estar chamando analisador_lexico novamente
   
    free(code); // Libera a memória alocada
    return 0;
}
