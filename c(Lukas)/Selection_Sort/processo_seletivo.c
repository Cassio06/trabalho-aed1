/*
 * ALGORITMO: SELECTION SORT
 * APLICAÇÃO: Situação Problema 17 - Seleção dos Melhores Candidatos em um Processo Seletivo
 *
 * JUSTIFICATIVA: O Selection Sort varre a lista selecionando iterativamente o candidato com a
 * maior pontuação restante e posicionando-o na frente, realizando no máximo N-1 trocas.
 * É ideal quando o custo de escrita/troca de registros é elevado e se deseja extrair os Top-N.
 *
 * COMPLEXIDADE:
 * - Pior / Médio / Melhor Caso: O(N^2) comparações (N*(N-1)/2).
 * - Número de Trocas: O(N) no pior caso.
 * - Espaço Auxiliar: O(1) (in-place).
 */

#include <stdio.h>
#include <string.h>

#define MAX 40

typedef struct {
    char nome[50];
    float nota;
} Candidato;

void selectionSortTopN(Candidato v[], int n, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].nota > v[max].nota) {
                max = j;
            }
        }
        if (max != i) {
            Candidato temp = v[i];
            v[i] = v[max];
            v[max] = temp;
            (*trocas)++;
        }
    }
}

void exibirClassificacao(Candidato v[], int total, int topN, int comp, int trocas) {
    printf("\n--- CLASSIFICACAO GERAL (%d CANDIDATOS) ---\n", total);
    for (int i = 0; i < total; i++) {
        printf("%2dº Lugar: %-22s | Pontuacao: %.2f\n", i + 1, v[i].nome, v[i].nota);
    }
    printf("\n--- SELECIONADOS (TOP-%d) ---\n", topN);
    for (int i = 0; i < topN && i < total; i++) {
        printf("[APROVADO %dº] %-22s | Pontuacao: %.2f\n", i + 1, v[i].nome, v[i].nota);
    }
    printf("\nEstatisticas do Selection Sort: %d comparacoes e %d trocas realizadas.\n", comp, trocas);
}

// Teste automatizado com pelo menos 15 candidatos conforme exigido no enunciado
void executarSimulacao(Candidato candidatos[], int *total) {
    Candidato base[15] = {
        {"Ana Lima", 84.5f},
        {"Bruno Costa", 91.0f},
        {"Carla Alves", 76.0f},
        {"Daniel Rocha", 88.5f},
        {"Elisa Sousa", 95.0f},
        {"Fabio Santos", 69.5f},
        {"Gabriela Nunes", 82.0f},
        {"Heitor Melo", 79.5f},
        {"Isabela Dias", 93.5f},
        {"Joao Silva", 86.0f},
        {"Karen Ribeiro", 74.0f},
        {"Lucas Martins", 90.0f},
        {"Marina Barros", 81.5f},
        {"Nicolas Freitas", 89.0f},
        {"Olivia Gomes", 87.5f}
    };

    *total = 15;
    printf("\n=================================================================\n");
    printf("   SIMULACAO: PROCESSO SELETIVO COM 15 CANDIDATOS (TOP-5)        \n");
    printf("=================================================================\n");
    printf("\nLista original antes da ordenacao:\n");
    for (int i = 0; i < *total; i++) {
        candidatos[i] = base[i];
        printf("  - %-22s : %.2f pts\n", candidatos[i].nome, candidatos[i].nota);
    }

    int comp = 0, trocas = 0;
    selectionSortTopN(candidatos, *total, &comp, &trocas);
    exibirClassificacao(candidatos, *total, 5, comp, trocas);
}

int main(void) {
    Candidato candidatos[MAX];
    int total = 0, op, topN, comp = 0, trocas = 0;

    do {
        printf("\n=== PROCESSO SELETIVO - SELECTION SORT (SITUACAO 17) ===\n");
        printf("1. Cadastrar Candidato Manualmente\n");
        printf("2. Ordenar e Extrair Top-N\n");
        printf("3. Executar Simulacao com 15 Candidatos (Top-5)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        if (op == 1 && total < MAX) {
            printf("Nome: ");
            fgets(candidatos[total].nome, 50, stdin);
            candidatos[total].nome[strcspn(candidatos[total].nome, "\n")] = '\0';
            printf("Pontuacao (0 a 100): ");
            if (scanf("%f", &candidatos[total].nota) != 1 ||
                candidatos[total].nota < 0.0f || candidatos[total].nota > 100.0f) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Pontuacao invalida! Informe um valor de 0 a 100.\n");
                continue;
            }
            getchar();
            total++;
        } else if (op == 1 && total >= MAX) {
            printf("[ERRO] Capacidade maxima de candidatos (%d) atingida!\n", MAX);
        } else if (op == 2 && total > 0) {
            selectionSortTopN(candidatos, total, &comp, &trocas);
            printf("Quantos classificados deseja visualizar (Top-N)? ");
            if (scanf("%d", &topN) != 1 || topN <= 0) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Valor de Top-N invalido!\n");
                continue;
            }
            getchar();
            exibirClassificacao(candidatos, total, topN, comp, trocas);
        } else if (op == 2 && total == 0) {
            printf("[AVISO] Nenhum candidato cadastrado para ordenar.\n");
        } else if (op == 3) {
            executarSimulacao(candidatos, &total);
        } else if (op != 0) {
            printf("Opcao invalida!\n");
        }
    } while (op != 0);

    return 0;
}
