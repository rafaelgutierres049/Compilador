#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

// Estrutura que representa a tabela de símbolos (implementada como um array simples)
typedef struct {
    char simbolo[MAX];  // Array de caracteres para armazenar os símbolos
    int topo;  // Índice para o topo da tabela (simulando uma pilha)
} TabelaSimbolos;

// Funções para manipulação da tabela de símbolos

// Inicializa a tabela de símbolos, definindo o topo como -1 (indicando tabela vazia)
TabelaSimbolos inicializaTabela() {
    TabelaSimbolos t;
    t.topo = -1;
    return t;
}

// Verifica se a tabela de símbolos está vazia
int tabelaVazia(TabelaSimbolos t) {
    return t.topo == -1;
}

// Verifica se a tabela de símbolos está cheia
int tabelaCheia(TabelaSimbolos t) {
    return t.topo == MAX - 1;
}

// Empilha um símbolo na tabela
TabelaSimbolos empilhaTabela(TabelaSimbolos t, char simbolo) {
    if (!tabelaCheia(t)) {
        t.simbolo[++(t.topo)] = simbolo;
    } else {
        printf("Erro: Tabela cheia!\n");
        exit(1);  // Encerra o programa se a tabela estiver cheia
    }
    return t;
}

// Desempilha o símbolo do topo da tabela
TabelaSimbolos desempilhaTabela(TabelaSimbolos t, char *simbolo) {
    if (!tabelaVazia(t)) {
        *simbolo = t.simbolo[(t.topo)--];
    } else {
        printf("Erro: Tabela vazia!\n");
        exit(1);  // Encerra o programa se a tabela estiver vazia
    }
    return t;
}

// Retorna o símbolo do topo da tabela sem desempilhá-lo
char topoTabela(TabelaSimbolos t) {
    if (!tabelaVazia(t)) {
        return t.simbolo[t.topo];
    } else {
        return '\0'; // Retorna caractere nulo se a tabela estiver vazia
    }
}

// Verifica a precedência dos operadores
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-': return 1;  // Operadores de menor precedência
        case '*':
        case '/': return 2;  // Operadores de maior precedência
        default: return 0;  // Caso não seja um operador válido
    }
}

// Função principal para converter a expressão infixa para pós-fixa
void infixaParaPosfixa(const char *infixa, char *posfixa) {
    TabelaSimbolos pilha = inicializaTabela();  // Inicializa a tabela (pilha) para armazenar os operadores

    int i = 0, j = 0;
    char c;

    // Diagrama de transição com `switch` e `case` para processar cada caractere da expressão infixa
    while ((c = infixa[i++]) != '\0') {
        switch (c) {
            case ' ': // Ignorar espaços em branco
                break;
            case '(': // Abrir parêntese
                pilha = empilhaTabela(pilha, c);
                break;
            case ')': // Fechar parêntese
                // Desempilha até encontrar o parêntese de abertura
                while (!tabelaVazia(pilha) && topoTabela(pilha) != '(') {
                    char simbolo;
                    pilha = desempilhaTabela(pilha, &simbolo);
                    posfixa[j++] = simbolo;
                    posfixa[j++] = ' ';  // Adiciona um espaço após o operador
                }
                pilha = desempilhaTabela(pilha, &c);  // Remove '('
                break;
            case '+': case '-': case '*': case '/': // Operadores aritméticos
                // Desempilha os operadores da pilha enquanto tiverem maior ou igual precedência
                while (!tabelaVazia(pilha) && precedencia(topoTabela(pilha)) >= precedencia(c)) {
                    char simbolo;
                    pilha = desempilhaTabela(pilha, &simbolo);
                    posfixa[j++] = simbolo;
                    posfixa[j++] = ' ';  // Adiciona um espaço após o operador
                }
                pilha = empilhaTabela(pilha, c);  // Empilha o operador atual
                break;
            default: // Números
                if (isdigit(c)) {
                    posfixa[j++] = c;
                    // Se o próximo caractere não for número, adiciona um espaço após o número
                    if (!isdigit(infixa[i])) {
                        posfixa[j++] = ' ';
                    }
                } else {
                    printf("Erro: Caractere inválido '%c'\n", c);
                    exit(1);  // Encerra o programa se um caractere inválido for encontrado
                }
                break;
        }
    }

    // Desempilha todos os operadores restantes da pilha
    while (!tabelaVazia(pilha)) {
        char simbolo;
        pilha = desempilhaTabela(pilha, &simbolo);
        posfixa[j++] = simbolo;
        posfixa[j++] = ' ';  // Adiciona um espaço após o operador
    }

    posfixa[j] = '\0';  // Finaliza a string pós-fixa
}

// Função principal do programa
int main() {
    char infixa[MAX];  // String para armazenar a expressão infixa
    char posfixa[MAX];  // String para armazenar a expressão pós-fixa

    printf("Digite uma expressao infixa: ");
    fgets(infixa, MAX, stdin);  // Lê a expressão infixa do usuário
    infixa[strcspn(infixa, "\n")] = '\0';  // Remove o '\n' do final da string

    // Converte a expressão infixa para pós-fixa
    infixaParaPosfixa(infixa, posfixa);

    // Exibe a expressão infixa e a pós-fixa
    printf("Expressao infixa: %s\n", infixa);
    printf("Expressao pos-fixa: %s\n", posfixa);

    return 0;
}
