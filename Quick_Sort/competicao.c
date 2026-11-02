/*
 * ALGORITMO: QUICK SORT
 * APLICAÇÃO: Situação Problema 24 - Classificação de Resultados de uma Competição Esportiva
 *
 * JUSTIFICATIVA: Ordena rapidamente os registros dos atletas por tempo de prova (menor tempo
 * vence), permitindo gerar de imediato o pódio (Top 3) e a classificação geral final.
 *
 * COMPLEXIDADE:
 * - Caso Médio: O(N log N)
 * - Pior Caso: O(N^2)
 * - Espaço Auxiliar: O(log N) em memória na pilha de recursão.
 */

#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[50];
    float tempo; // Tempo em segundos (menor = melhor colocação)
} Atleta;

int particionar(Atleta v[], int low, int high, int *comparacoes, int *trocas) {
    float pivo = v[high].tempo;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*comparacoes)++;
        if (v[j].tempo <= pivo) {
            i++;
            Atleta temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            (*trocas)++;
        }
    }
    Atleta temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;
    (*trocas)++;
    return i + 1;
}

void quickSort(Atleta v[], int low, int high, int *comparacoes, int *trocas) {
    if (low < high) {
        int pi = particionar(v, low, high, comparacoes, trocas);
        quickSort(v, low, pi - 1, comparacoes, trocas);
        quickSort(v, pi + 1, high, comparacoes, trocas);
    }
}

void exibirResultadoCompeticao(Atleta atletas[], int total, int comp, int trocas) {
    printf("\n=================== PODIO OFICIAL (TOP 3) ===================\n");
    const char *medalhas[3] = {"OURO  ", "PRATA ", "BRONZE"};
    for (int i = 0; i < 3 && i < total; i++) {
        printf("  [%s - %dº Lugar] %-22s | Tempo: %.2f s\n",
               medalhas[i], i + 1, atletas[i].nome, atletas[i].tempo);
    }
    printf("=============================================================\n");

    printf("\n--- CLASSIFICACAO FINAL COMPLETA (%d ATLETAS) ---\n", total);
    for (int i = 0; i < total; i++) {
        printf("%2dº Lugar: %-22s | Tempo: %.2f s\n", i + 1, atletas[i].nome, atletas[i].tempo);
    }
    printf("\nEstatisticas do Quick Sort: %d comparacoes e %d particionamentos/trocas.\n", comp, trocas);
}

// Simulação automatizada com 30 atletas conforme exigido no enunciado
void executarSimulacao(Atleta atletas[], int *total) {
    Atleta base[30] = {
        {"Ana Lima", 11.42f},        {"Bruno Costa", 10.85f},
        {"Carla Alves", 12.10f},     {"Daniel Rocha", 10.12f},
        {"Elisa Sousa", 11.78f},     {"Fabio Santos", 10.54f},
        {"Gabriela Nunes", 11.95f},  {"Heitor Melo", 9.98f},
        {"Isabela Dias", 11.20f},    {"Joao Silva", 10.33f},
        {"Karen Ribeiro", 12.45f},   {"Lucas Martins", 10.05f},
        {"Marina Barros", 11.60f},   {"Nicolas Freitas", 10.71f},
        {"Olivia Gomes", 12.02f},    {"Paulo Araujo", 10.19f},
        {"Rafaela Torres", 11.34f},  {"Samuel Pinto", 10.48f},
        {"Tais Carvalho", 11.88f},   {"Victor Braga", 9.91f},
        {"Alice Teixeira", 11.50f},  {"Bernardo Castro", 10.62f},
        {"Camila Fernandes", 12.18f},{"Diego Moura", 10.27f},
        {"Eduarda Lopes", 11.11f},   {"Felipe Correia", 10.40f},
        {"Giovana Cardoso", 11.73f}, {"Henrique Vieira", 10.08f},
        {"Iara Mendes", 12.30f},     {"Julio Farias", 10.95f}
    };

    *total = 30;
    for (int i = 0; i < *total; i++) atletas[i] = base[i];

    printf("\n=================================================================\n");
    printf("   SIMULACAO: CORRIDA DE 100m RASOS COM 30 ATLETAS (QUICK SORT)  \n");
    printf("=================================================================\n");

    int comp = 0, trocas = 0;
    quickSort(atletas, 0, *total - 1, &comp, &trocas);
    exibirResultadoCompeticao(atletas, *total, comp, trocas);
}

int main() {
    Atleta atletas[MAX];
    int total = 0, op, comp = 0, trocas = 0;

    do {
        printf("\n=== CLASSIFICACAO ESPORTIVA - QUICK SORT (SITUACAO 24) ===\n");
        printf("1. Cadastrar Resultado de Atleta Manualmente\n");
        printf("2. Ordenar e Gerar Podio (Top 3) e Classificacao Final\n");
        printf("3. Executar Simulacao com 30 Atletas\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        if (op == 1 && total < MAX) {
            printf("Nome do Atleta: ");
            fgets(atletas[total].nome, 50, stdin);
            atletas[total].nome[strcspn(atletas[total].nome, "\n")] = '\0';
            printf("Tempo (segundos, ex: 10.45): ");
            scanf("%f", &atletas[total].tempo);
            getchar();
            total++;
        } else if (op == 2 && total > 0) {
            comp = 0; trocas = 0;
            quickSort(atletas, 0, total - 1, &comp, &trocas);
            exibirResultadoCompeticao(atletas, total, comp, trocas);
        } else if (op == 3) {
            executarSimulacao(atletas, &total);
        }
    } while (op != 0);

    return 0;
}
