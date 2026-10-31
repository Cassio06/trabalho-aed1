/*
 * ALGORITMO: QUICK SORT
 * APLICAÇÃO: Classificação de Resultados e Geração do Pódio de Competição Esportiva
 * 
 * JUSTIFICATIVA: Permite reordenar rapidamente grandes listas de atletas de acordo com seus
 * tempos/pontuações para determinar os vencedores (Top 3) e o ranking final da prova.
 * 
 * COMPLEXIDADE:
 * - Caso Médio: O(N log N)
 * - Espaço: O(log N) em memória.
 */

#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[50];
    float tempo;
} Atleta;

int particionar(Atleta v[], int low, int high) {
    float pivo = v[high].tempo;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (v[j].tempo <= pivo) {
            i++;
            Atleta temp = v[i]; v[i] = v[j]; v[j] = temp;
        }
    }
    Atleta temp = v[i + 1]; v[i + 1] = v[high]; v[high] = temp;
    return i + 1;
}

void quickSort(Atleta v[], int low, int high) {
    if (low < high) {
        int pi = particionar(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

int main() {
    Atleta atletas[MAX];
    int total = 0, op;
    do {
        printf("\n=== PODIO DE COMPETICAO ===\n1. Cadastrar Resultado de Atleta\n2. Gerar Podio e Classificacao Final\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        if (op == 1 && total < MAX) {
            printf("Nome do Atleta: "); fgets(atletas[total].nome, 50, stdin); atletas[total].nome[strcspn(atletas[total].nome, "\n")] = '\0';
            printf("Tempo (segundos, ex: 10.45): "); scanf("%f", &atletas[total].tempo); getchar();
            total++;
        } else if (op == 2 && total > 0) {
            quickSort(atletas, 0, total - 1);
            printf("\n--- RESULTADO DA COMPETICAO ---\n");
            for (int i = 0; i < total; i++) {
                if (i < 3) printf("PODIO %dº Lugar: %s (Tempo: %.2f s)\n", i + 1, atletas[i].nome, atletas[i].tempo);
                else printf("%dº Lugar: %s (Tempo: %.2f s)\n", i + 1, atletas[i].nome, atletas[i].tempo);
            }
        }
    } while (op != 0);
    return 0;
}
