/*
 * ALGORITMO: SELECTION SORT
 * APLICAÇÃO: Organização de Tarefas por Nível de Prioridade Numérica
 * 
 * JUSTIFICATIVA: Simples de implementar em listas de tamanho moderado (ex: tarefas do dia),
 * organizando as atividades de forma determinística por sua ordem de prioridade.
 * 
 * COMPLEXIDADE:
 * - Tempo: O(N^2)
 * - Espaço: O(1) in-place.
 */

#include <stdio.h>
#include <string.h>

#define MAX 30

typedef struct {
    char descricao[50];
    int prioridade; // 1 a 5
} Tarefa;

void selectionSortTarefas(Tarefa v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j].prioridade < v[min].prioridade) min = j;
        Tarefa temp = v[i]; v[i] = v[min]; v[min] = temp;
    }
}

int main() {
    Tarefa lista[MAX];
    int total = 0, op;

    do {
        printf("\n=== GERENCIADOR DE TAREFAS ===\n1. Adicionar Tarefa\n2. Ordenar por Prioridade e Listar\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        if (op == 1 && total < MAX) {
            printf("Descricao da Tarefa: "); fgets(lista[total].descricao, 50, stdin); lista[total].descricao[strcspn(lista[total].descricao, "\n")] = '\0';
            printf("Prioridade (1 - Urgente ate 5 - Baixa): "); scanf("%d", &lista[total].prioridade); getchar();
            total++;
        } else if (op == 2 && total > 0) {
            selectionSortTarefas(lista, total);
            printf("\n--- TAREFAS DO DIA (ORDENADAS POR PRIORIDADE) ---\n");
            for (int i = 0; i < total; i++)
                printf("Prioridade %d: %s\n", lista[i].prioridade, lista[i].descricao);
        }
    } while (op != 0);
    return 0;
}
