#include <stdio.h>
#include <string.h>

#define TAMANHO 50

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

void empilhar(Pilha *p, char c, int pos) {
    if (cheia(p)) return;
    p->topo++;
    p->dados[p->topo].simbolo = c;
    p->dados[p->topo].posicao = pos;
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

// Função de validação com o Relatório de Erros por posição
void validarExpressao(char *exp) {
    int i;
    Pilha p;
    inicializar(&p);

    printf("\n--------------------------------------------------\n");
    printf("Analisando expressao: \"%s\"\n", exp);

    for (i = 0; exp[i] != '\0'; i++) {
        char atual = exp[i];

        // Se for abertura, empilha o caractere junto com a sua posição (índice i)
        if (atual == '(' || atual == '[' || atual == '{') {
            empilhar(&p, atual, i);
        } 
        // Se for fechamento, valida
        else if (atual == ')' || atual == ']' || atual == '}') {
            if (vazia(&p)) {
                printf("-> RESULTADO: INCORRETA!\n");
                printf("   [RELATORIO DE ERRO] Desbalanceamento no caractere '%c' (posicao %d): Fechamento sem abertura correspondente.\n", atual, i);
                return;
            }

            ItemPilha topoItem = desempilhar(&p);

            if (!ehPar(topoItem.simbolo, atual)) {
                printf("-> RESULTADO: INCORRETA!\n");
                printf("   [RELATORIO DE ERRO] Desbalanceamento no caractere '%c' (posicao %d): Nao combina com '%c' aberto na posicao %d.\n", 
                       atual, i, topoItem.simbolo, topoItem.posicao);
                return;
            }
        }
    }

    // Se sobrou algum símbolo aberto na pilha ao final da leitura
    if (!vazia(&p)) {
        ItemPilha topoItem = desempilhar(&p);
        printf("-> RESULTADO: INCORRETA!\n");
        printf("   [RELATORIO DE ERRO] O simbolo '%c' na posicao %d nao foi fechado ate o final da expressao.\n", 
               topoItem.simbolo, topoItem.posicao);
        return;
    }

    printf("-> RESULTADO: CORRETA (Expressao perfeitamente balanceada)!\n");
}

int main() {
    char expressao[100];
    int opcao;
    int i;

    do {
        printf("\n===== VALIDADOR DE EXPRESSOES (SITUACAO 4) =====\n");
        printf("1 - Verificar Nova Expressao\n");
        printf("2 - Executar Simulacao de Testes Obrigatorios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("\nDigite a expressao matematica: ");
                fgets(expressao, 100, stdin);
                expressao[strcspn(expressao, "\n")] = '\0';

                validarExpressao(expressao);
                break;

            case 2:
                printf("\n=================== RODANDO SIMULACOES ===================");
                // Casos de teste indicados no enunciado
                char *testes[] = {
                    "{[()]}",   // Válida
                    "([)]",     // Inválida (fecha fora de ordem)
                    "((()))",   // Válida
                    "([]]"      // Inválida (desbalanceada)
                };

                for (i = 0; i < 4; i++) {
                    validarExpressao(testes[i]);
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}