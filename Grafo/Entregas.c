/*
 * ESTRUTURA DE DADOS: GRAFO PONDERADO (Matriz de Adjacência)
 * APLICAÇÃO: Roteamento de Entrega de Mercadorias (Caminho Mínimo com Dijkstra)
 * 
 * JUSTIFICATIVA: O grafo ponderado modela os pontos de entrega (vértices) e as rotas
 * com suas respectivas distâncias/custos (arestas com pesos). O algoritmo de Dijkstra encontra
 * a rota de menor custo total a partir de uma origem.
 * 
 * COMPLEXIDADE:
 * - Algoritmo de Dijkstra: O(V^2), onde V é o número de vértices.
 * - Espaço: O(V^2) na matriz de adjacência.
 */

#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999999

typedef struct {
    char nomes[MAX][50];
    int matriz[MAX][MAX];
    int numVertices;
} GrafoDelivery;

void inicializar(GrafoDelivery *g) {
    g->numVertices = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            g->matriz[i][j] = (i == j) ? 0 : INF;
}

int buscarOuAdicionarPonto(GrafoDelivery *g, char *nome) {
    for (int i = 0; i < g->numVertices; i++) {
        if (strcmp(g->nomes[i], nome) == 0) return i;
    }
    if (g->numVertices >= MAX) return -1;
    strcpy(g->nomes[g->numVertices], nome);
    return g->numVertices++;
}

void adicionarRota(GrafoDelivery *g, char *origem, char *destino, int peso) {
    int u = buscarOuAdicionarPonto(g, origem);
    int v = buscarOuAdicionarPonto(g, destino);
    if (u != -1 && v != -1) {
        g->matriz[u][v] = peso;
        g->matriz[v][u] = peso;
        printf("Rota entre '%s' e '%s' adicionada com custo/distancia %d!\n", origem, destino, peso);
    }
}

void dijkstra(GrafoDelivery *g, int orig, int dest) {
    int dist[MAX], visitado[MAX], anterior[MAX];
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF; visitado[i] = 0; anterior[i] = -1;
    }
    dist[orig] = 0;

    for (int count = 0; count < g->numVertices - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < g->numVertices; v++)
            if (!visitado[v] && dist[v] <= min) { min = dist[v]; u = v; }

        if (u == -1) break;
        visitado[u] = 1;

        for (int v = 0; v < g->numVertices; v++)
            if (!visitado[v] && g->matriz[u][v] != INF && dist[u] + g->matriz[u][v] < dist[v]) {
                dist[v] = dist[u] + g->matriz[u][v];
                anterior[v] = u;
            }
    }

    if (dist[dest] == INF) { printf("Nao ha rota disponivel entre esses pontos!\n"); return; }
    printf("\nCusto minimo total de entrega: %d\nCaminho: ", dist[dest]);
    int caminho[MAX], tam = 0, curr = dest;
    while (curr != -1) { caminho[tam++] = curr; curr = anterior[curr]; }
    for (int i = tam - 1; i >= 0; i--) printf("%s%s", g->nomes[caminho[i]], (i > 0) ? " -> " : "\n");
}

int main() {
    GrafoDelivery g; inicializar(&g);
    int op, peso; char p1[50], p2[50];
    do {
        printf("\n=== ROTEAMENTO DE DELIVERY ===\n1. Cadastrar Rota Ponderada\n2. Calcular Rota Minima \n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1:
                printf("Ponto de Origem: "); fgets(p1, 50, stdin); p1[strcspn(p1, "\n")] = '\0';
                printf("Ponto de Destino: "); fgets(p2, 50, stdin); p2[strcspn(p2, "\n")] = '\0';
                printf("Distancia/Custo: "); scanf("%d", &peso); getchar();
                adicionarRota(&g, p1, p2, peso); break;
            case 2:
                printf("Origem da entrega: "); fgets(p1, 50, stdin); p1[strcspn(p1, "\n")] = '\0';
                printf("Destino da entrega: "); fgets(p2, 50, stdin); p2[strcspn(p2, "\n")] = '\0';
                int u = buscarOuAdicionarPonto(&g, p1), v = buscarOuAdicionarPonto(&g, p2);
                dijkstra(&g, u, v); break;
        }
    } while (op != 0);
    return 0;
}
