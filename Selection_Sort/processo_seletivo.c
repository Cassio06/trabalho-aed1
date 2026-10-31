/*
 * ALGORITMO: SELECTION SORT
 * APLICAÇÃO: Seleção dos Melhores Candidatos em Processo Seletivo (Top-N)
 * 
 * JUSTIFICATIVA: O Selection Sort varre o vetor selecionando iterativamente a maior nota restante
 * e posicionando-a no topo. Útil quando se deseja extrair os Top-N candidatos reduzindo o custo de trocas.
 * 
 * COMPLEXIDADE:
 * - Pior/Melhor/Médio Caso: O(N^2) comparações.
 * - Número de Trocas: O(N), minimizando gravações em memória.
 * - Espaço Auxiliar: O(1).
 */

#include <stdio.h>
#include <string.h>

#define MAX 30

typedef struct {
    char nome[50];
    float nota;
} Candidato;

void selectionSortTopN(Candidato v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++)
            if (v[j].nota > v[max].nota) max = j;
        Candidato temp = v[i]; v[i] = v[max]; v[max] = temp;
    }
}

int main() {
    Candidato candidatos[MAX];
    int total = 0, op, topN;

    do {
        printf("\n=== PROCESSO SELETIVO ===\n1. Cadastrar Candidato\n2. Ordenar e Extrair Top-N\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        if (op == 1 && total < MAX) {
            printf("Nome: "); fgets(candidatos[total].nome, 50, stdin); candidatos[total].nome[strcspn(candidatos[total].nome, "\n")] = '\0';
            printf("Nota: "); scanf("%f", &candidatos[total].nota); getchar();
            total++;
        } else if (op == 2 && total > 0) {
            selectionSortTopN(candidatos, total);
            printf("Quantos classificados deseja visualizar (Top-N)? "); scanf("%d", &topN); getchar();
            printf("\n--- CLASSIFICACAO DOS CANDIDATOS ---\n");
            for (int i = 0; i < topN && i < total; i++)
                printf("%dº Lugar: %s | Nota: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nota);
        }
    } while (op != 0);
    return 0;
}
