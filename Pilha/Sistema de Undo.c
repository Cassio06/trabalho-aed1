#include <stdio.h>
#include <string.h>

#define TAMANHO 15

// Estrutura que representa a ação do editor de texto
typedef struct {
    char tipo[20];      // Ex: "Digitacao", "Exclusao", "Formatacao"
    char texto[50];     // O texto associado à ação
} Acao;

// Estrutura da Pilha
typedef struct {
    Acao dados[TAMANHO];
    int topo;
} Pilha;

// Inicializa a pilha
void inicializar(Pilha *p) {
    p->topo = -1;
}

// Verifica se a pilha está vazia
int vazia(Pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha está cheia
int cheia(Pilha *p) {
    return p->topo == TAMANHO - 1;
}

// Executa e empilha uma ação (Push)
void empilhar(Pilha *p, Acao acao) {
    if (cheia(p)) {
        printf("\n[AVISO] Historico de acoes cheio! Nao e possivel guardar mais acoes.\n");
        return;
    }
    p->topo++;
    p->dados[p->topo] = acao;
    printf("Acao '%s' (%s) registrada com sucesso!\n", acao.texto, acao.tipo);
}

// Visualiza a última ação realizada sem remover (Peek/Topo)
void topo(Pilha *p) {
    if (vazia(p)) {
        printf("\nNenhuma acao no historico.\n");
        return;
    }
    Acao ultima = p->dados[p->topo];
    printf("\nUltima acao realizada: [%s] \"%s\"\n", ultima.tipo, ultima.texto);
}

// Desfaz a última ação (Pop)
int desempilhar(Pilha *p, Acao *acao) {
    if (vazia(p)) {
        printf("\nNada para desfazer!\n");
        return 0;
    }
    *acao = p->dados[p->topo];
    p->topo--;
    printf("\n[DESFAZENDO] Acao revertida: [%s] \"%s\"\n", acao->tipo, acao->texto);
    return 1;
}

// Lista todo o histórico de ações ativas na pilha
void listar(Pilha *p, char *nomePilha) {
    int i;
    if (vazia(p)) {
        printf("\n[%s] Vazia.\n", nomePilha);
        return;
    }
    printf("\n--- %s ---\n", nomePilha);
    for ( i = p->topo; i >= 0; i--) {
        printf("%d. [%s] %s\n", i + 1, p->dados[i].tipo, p->dados[i].texto);
    }
}

// Função que simula as 12 ações do editor e o processo de desfazer/refazer
void executarSimulacao(Pilha *undo, Pilha *redo) {
    int i;
    printf("\n======================================================\n");
    printf("       INICIANDO SIMULACAO AUTOMATIZADA (UNDO/REDO)   \n");
    printf("======================================================\n");

    inicializar(undo);
    inicializar(redo);

    // Conjunto com 12 ações para preencher os requisitos do trabalho
    Acao acoesSimuladas[12] = {
        {"Digitacao", "Ola, este e um documento de teste."},
        {"Digitacao", "Estrutura de dados e uma materia importante."},
        {"Formatacao", "Negrito na palavra 'dados'"},
        {"Exclusao", "importante."},
        {"Digitacao", "fundamental para Engenharia de Software."},
        {"Formatacao", "Italico em 'Engenharia de Software'"},
        {"Digitacao", "Vamos testar o sistema de Undo e Redo."},
        {"Exclusao", " e Redo."},
        {"Digitacao", " usando Pilhas em C."},
        {"Formatacao", "Fonte alterada para tamanho 12"},
        {"Digitacao", "Fim da primeira secao."},
        {"Exclusao", "Fim da primeira secao."}
    };

    // PASSO 1: Empilhando 12 Ações
    printf("\n--- PASSO 1: Inserindo 12 Acoes na Pilha ---\n");
    for (i = 0; i < 12; i++) {
        empilhar(undo, acoesSimuladas[i]);
        inicializar(redo);
    }

    // PASSO 2: Listando Estado Inicial
    printf("\n--- ESTADO ATUAL DAS PILHAS APOS 12 ACOES ---");
    listar(undo, "Undo");
    listar(redo, "Redo");

    // PASSO 3: Desfazendo 4 Ações Seguidas (Desempilhar do Undo -> Empilhar no Redo)
    printf("\n--- PASSO 2: Desfazendo 4 Acoes Seguidas (Undo) ---\n");
    Acao aux;
    for (i = 1; i <= 4; i++) {
        if (desempilhar(undo, &aux)) {
            empilhar(redo, aux);
        }
    }

    // PASSO 4: Listando Estado Pós-Undo
    printf("\n--- ESTADO APOS DESFAZER 4 ACOES ---");
    listar(undo, "Undo");
    listar(redo, "Redo");

    // PASSO 5: Refazendo 2 Ações (Desempilhar do Redo -> Empilhar no Undo)
    printf("\n--- PASSO 3: Refazendo 2 Acoes (Redo) ---\n");
    for (i = 1; i <= 2; i++) {
        if (desempilhar(redo, &aux)) {
            empilhar(undo, aux);
            printf("\n[REFAZENDO] Acao refeita: [%s] \"%s\"\n", aux.tipo, aux.texto);
        }
    }

    // PASSO 6: Estado Final
    printf("\n--- ESTADO FINAL DA SIMULACAO ---");
    listar(undo, "Undo");
    listar(redo, "Redo");

    printf("\n======================================================\n");
    printf("              SIMULACAO CONCLUIDA!                     \n");
    printf("======================================================\n");
}

int main() {
    Pilha undo, redo;
    Acao acao;
    int opcao;

    inicializar(&undo);
    inicializar(&redo);

    do {
        printf("\n===== EDITOR DE TEXTO (SISTEMA DE UNDO) =====\n");
        printf("1 - Executar Nova Acao (Empilhar)\n");
        printf("2 - Ver Ultima Acao (Topo)\n");
        printf("3 - Desfazer Ultima Acao (Undo)\n");
        printf("4 - Verificar se Historico esta Vazio\n");
        printf("5 - Listar Historico de Acoes\n");
        printf("6 - Refazer (Redo)\n");
        printf("7 - Executar Simulacao Automatizada (12 Acoes)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o tipo da acao (ex: Digitacao, Exclusao, Formatacao): ");
                fgets(acao.tipo, 20, stdin);
                acao.tipo[strcspn(acao.tipo, "\n")] = '\0'; // Remove o '\n'

                printf("Digite o conteudo/texto da acao: ");
                fgets(acao.texto, 50, stdin);
                acao.texto[strcspn(acao.texto, "\n")] = '\0'; // Remove o '\n'

                empilhar(&undo, acao);
                inicializar (&redo); // Limpa o redo ao empilhar uma nova ação
                break;

            case 2:
                topo(&undo);
                break;

            case 3:
            // Tira de undo e joga em redo
                if (desempilhar(&undo, &acao)) {
                    empilhar(&redo, acao);
                    printf("\n[Undo] Desfeito: [%s] \"%s\" \n", acao.texto, acao.tipo);
                } else {
                    printf("\nNada para desfazer!\n");
                }
                break;

            case 4:
                if (vazia(&undo)) {
                    printf("\nO historico esta vazio.\n");
                } else {
                    printf("\nO historico contem acoes salvas.\n");
                }
                break;

            case 5:
                listar(&undo, "Undo");
                listar(&redo, "Redo");
                break;

            // Tira de redo e devolve para undo
            case 6:
            {
                    Acao refazer;
                    if (desempilhar(&redo, &refazer)) {
                        empilhar(&undo, refazer);
                        printf("\n[REFAZENDO] Acao refeita: [%s] \"%s\"\n", refazer.tipo, refazer.texto);
                    } else {
                        printf("\nNada para refazer!\n");
                    }
            }
                break;

            case 7:
                executarSimulacao(&undo, &redo);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}