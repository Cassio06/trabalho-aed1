/*
 * ALGORITMO: SELECTION SORT
 * APLICAÇÃO: Situação Problema 18 - Organização de Tarefas por Prioridade (Valor Numérico 1 a 5)
 *
 * JUSTIFICATIVA: Simples e determinístico para listas diárias pequenas (12 a 15 tarefas),
 * selecionando sucessivamente a atividade de maior urgência (menor valor numérico de 1 a 5)
 * com custo mínimo de movimentação de memória.
 *
 * COMPLEXIDADE:
 * - Tempo: O(N^2) em todos os casos.
 * - Trocas: O(N).
 * - Espaço Auxiliar: O(1) in-place.
 */

#include <stdio.h>
#include <string.h>

#define MAX 30

typedef struct {
    char descricao[60];
    int prioridade; // 1 (Urgente) a 5 (Baixa)
} Tarefa;

void selectionSortTarefas(Tarefa v[], int n, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Tarefa temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            (*trocas)++;
        }
    }
}

void listarTarefas(Tarefa v[], int total, const char *titulo) {
    printf("\n--- %s (%d tarefas) ---\n", titulo, total);
    for (int i = 0; i < total; i++) {
        printf("%2d. [Prioridade %d] %s\n", i + 1, v[i].prioridade, v[i].descricao);
    }
}

// Simulação de um dia de trabalho com 14 tarefas (entre 12 e 15 conforme enunciado)
void executarSimulacao(Tarefa lista[], int *total) {
    Tarefa base[14] = {
        {"Atualizar documentacao interna do modulo", 4},
        {"Corrigir falha critica no servidor de producao", 1},
        {"Responder e-mails pendentes de fornecedores", 3},
        {"Reuniao de alinhamento diario (Daily Scrum)", 2},
        {"Organizar arquivos antigos da pasta compartilhada", 5},
        {"Aplicar patch de seguranca no banco de dados", 1},
        {"Revisar Pull Request da equipe de desenvolvimento", 2},
        {"Validar homologacao com o cliente", 2},
        {"Planejar backlog da proxima Sprint", 3},
        {"Limpar logs temporarios de homologacao", 5},
        {"Restaurar backup de contingencia", 1},
        {"Elaborar relatorio semanal de metricas", 3},
        {"Pesquisar novas ferramentas de monitoramento", 4},
        {"Testar integracao da API de pagamentos", 2}
    };

    *total = 14;
    for (int i = 0; i < *total; i++) lista[i] = base[i];

    printf("\n=================================================================\n");
    printf("   SIMULACAO: DIA DE TRABALHO COM 14 TAREFAS (PRIORIDADE 1 A 5)  \n");
    printf("=================================================================\n");

    listarTarefas(lista, *total, "TAREFAS RECEBIDAS (ANTES DA ORDENACAO)");

    int comp = 0, trocas = 0;
    selectionSortTarefas(lista, *total, &comp, &trocas);

    listarTarefas(lista, *total, "TAREFAS REORGANIZADAS POR PRIORIDADE (SELECTION SORT)");
    printf("\nEstatisticas: %d comparacoes e %d trocas realizadas.\n", comp, trocas);
}

int main() {
    Tarefa lista[MAX];
    int total = 0, op, comp = 0, trocas = 0;

    do {
        printf("\n=== GERENCIADOR DE TAREFAS - SELECTION SORT (SITUACAO 18) ===\n");
        printf("1. Adicionar Tarefa Manualmente\n");
        printf("2. Ordenar por Prioridade e Listar\n");
        printf("3. Executar Simulacao de um Dia de Trabalho (14 Tarefas)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        if (op == 1 && total < MAX) {
            printf("Descricao da Tarefa: ");
            fgets(lista[total].descricao, 60, stdin);
            lista[total].descricao[strcspn(lista[total].descricao, "\n")] = '\0';
            printf("Prioridade (1 - Urgente ate 5 - Baixa): ");
            if (scanf("%d", &lista[total].prioridade) != 1 ||
                lista[total].prioridade < 1 || lista[total].prioridade > 5) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Prioridade invalida! Informe um valor de 1 a 5.\n");
                continue;
            }
            getchar();
            total++;
        } else if (op == 2 && total > 0) {
            selectionSortTarefas(lista, total, &comp, &trocas);
            listarTarefas(lista, total, "TAREFAS DO DIA (ORDENADAS POR PRIORIDADE)");
            printf("Estatisticas: %d comparacoes e %d trocas.\n", comp, trocas);
        } else if (op == 3) {
            executarSimulacao(lista, &total);
        }
    } while (op != 0);

    return 0;
}
