/*
 * ESTRUTURA DE DADOS: PILHA (LIFO - Last-In, First-Out)
 * APLICAÇÃO: Situação Problema 4 - Verificação de Expressões com Parênteses, Colchetes e Chaves
 *
 * JUSTIFICATIVA: Em expressões aninhadas, o último delimitador de abertura encontrado deve ser
 * obrigatoriamente o primeiro a ser fechado. A pilha armazena cada símbolo de abertura e sua
 * posição original em O(1), permitindo validar o pareamento e apontar o índice exato de erros.
 *
 * COMPLEXIDADE:
 * - Tempo de verificação: O(N), onde N é o comprimento da string avaliada.
 * - Operações de empilhar e desempilhar: O(1).
 * - Espaço auxiliar: O(N) no pior caso (expressão contendo apenas símbolos de abertura).
 */

#include <stdio.h>
#include <string.h>

#define TAMANHO 100

// Estrutura para guardar o caractere e sua posição na string
typedef struct {
    char simbolo;
    int posicao;
} ItemPilha;

// Estrutura da Pilha ajustada para o ItemPilha
typedef struct {
    ItemPilha dados[TAMANHO];
    int topo;
} Pilha;

void inicializar(Pilha *p) {
    p->topo = -1;
}

int vazia(Pilha *p) {
    return p->topo == -1;
}

int cheia(Pilha *p) {
    return p->topo == TAMANHO - 1;
}

int empilhar(Pilha *p, char c, int pos) {
    if (cheia(p)) return 0;
    p->topo++;
    p->dados[p->topo].simbolo = c;
    p->dados[p->topo].posicao = pos;
    return 1;
}

ItemPilha desempilhar(Pilha *p) {
    ItemPilha vazio = {'\0', -1};
    if (vazia(p)) return vazio;
    ItemPilha item = p->dados[p->topo];
    p->topo--;
    return item;
}

// Verifica se o par abre/fecha é correspondente
int ehPar(char abertura, char fechamento) {
    if (abertura == '(' && fechamento == ')') return 1;
    if (abertura == '[' && fechamento == ']') return 1;
    if (abertura == '{' && fechamento == '}') return 1;
    return 0;
}

// Função que recebe uma string, exibe o relatório de erros por posição e retorna 1 (balanceada) ou 0 (inválida)
int validarExpressao(const char *exp) {
    int i;
    Pilha p;
    inicializar(&p);

    printf("\n--------------------------------------------------\n");
    printf("Analisando expressao: \"%s\"\n", exp);

    for (i = 0; exp[i] != '\0'; i++) {
        char atual = exp[i];

        // Se for abertura, empilha o caractere junto com a sua posição (índice i)
        if (atual == '(' || atual == '[' || atual == '{') {
            if (!empilhar(&p, atual, i)) {
                printf("-> RESULTADO: INCORRETA!\n");
                printf("   [RELATORIO DE ERRO] Limite maximo da pilha (%d simbolos) excedido na posicao %d.\n", TAMANHO, i);
                return 0;
            }
        }
        // Se for fechamento, valida
        else if (atual == ')' || atual == ']' || atual == '}') {
            if (vazia(&p)) {
                printf("-> RESULTADO: INCORRETA!\n");
                printf("   [RELATORIO DE ERRO] Desbalanceamento no caractere '%c' (posicao %d): Fechamento sem abertura correspondente.\n", atual, i);
                return 0;
            }

            ItemPilha topoItem = desempilhar(&p);

            if (!ehPar(topoItem.simbolo, atual)) {
                printf("-> RESULTADO: INCORRETA!\n");
                printf("   [RELATORIO DE ERRO] Desbalanceamento no caractere '%c' (posicao %d): Nao combina com '%c' aberto na posicao %d.\n",
                       atual, i, topoItem.simbolo, topoItem.posicao);
                return 0;
            }
        }
    }

    // Se sobrou algum símbolo aberto na pilha ao final da leitura
    if (!vazia(&p)) {
        ItemPilha topoItem = desempilhar(&p);
        printf("-> RESULTADO: INCORRETA!\n");
        printf("   [RELATORIO DE ERRO] O simbolo '%c' na posicao %d nao foi fechado ate o final da expressao.\n",
               topoItem.simbolo, topoItem.posicao);
        return 0;
    }

    printf("-> RESULTADO: CORRETA (Expressao perfeitamente balanceada)!\n");
    return 1;
}

int main(void) {
    char expressao[100];
    int opcao;
    int i;

    do {
        printf("\n===== VALIDADOR DE EXPRESSOES (SITUACAO 4) =====\n");
        printf("1 - Verificar Nova Expressao\n");
        printf("2 - Executar Simulacao de Testes Obrigatorios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) break;
        getchar();

        switch (opcao) {
            case 1:
                printf("\nDigite a expressao matematica: ");
                fgets(expressao, 100, stdin);
                expressao[strcspn(expressao, "\n")] = '\0';

                validarExpressao(expressao);
                break;

            case 2: {
                printf("\n=================== RODANDO SIMULACOES ===================\n");
                // Casos de teste indicados no enunciado + casos adicionais de borda
                const char *testes[] = {
                    "{ [ ( ) ] }",          // Válida (enunciado)
                    "( [ ) ]",              // Inválida - fecha fora de ordem (enunciado)
                    "((()))",               // Válida (enunciado)
                    "([)]",                 // Inválida - cruzada (enunciado)
                    "([]]",                 // Inválida - fechamento extra
                    "{[a + (b * c)] - d}",  // Válida com variáveis
                    "((a + b) * [c - d]"    // Inválida - abertura sem fechar
                };

                for (i = 0; i < 7; i++) {
                    validarExpressao(testes[i]);
                }
                break;
            }

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
