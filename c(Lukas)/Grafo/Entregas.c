/*
 * ESTRUTURA DE DADOS: GRAFO PONDERADO (Lista de Adjacência)
 * APLICAÇÃO: Situação Problema 11 - Roteamento de Entrega de Mercadorias (Caminho Mínimo com Dijkstra)
 *
 * JUSTIFICATIVA: O grafo ponderado em lista de adjacência modela os bairros/pontos de entrega
 * (vértices) e as vias urbanas com seus custos/distâncias (arestas com peso), economizando
 * memória em mapas esparsos. O algoritmo de Dijkstra encontra o caminho de menor custo total.
 *
 * COMPLEXIDADE:
 * - Inserção de vértice/aresta: O(1) amortizado.
 * - Algoritmo de Dijkstra: O(V^2 + E) com busca linear do vértice mínimo.
 * - Espaço: O(V + E) na lista de adjacência.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 25
#define INF 999999

typedef struct NoAdj {
    int destino;
    int peso;
    struct NoAdj *proximo;
} NoAdj;

typedef struct {
    char nomes[MAX_VERTICES][50];
    NoAdj *adj[MAX_VERTICES];
    int numVertices;
} GrafoDelivery;

void inicializar(GrafoDelivery *g) {
    g->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
    }
}

void liberarGrafo(GrafoDelivery *g) {
    for (int i = 0; i < g->numVertices; i++) {
        NoAdj *atual = g->adj[i];
        while (atual != NULL) {
            NoAdj *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
        g->adj[i] = NULL;
    }
    g->numVertices = 0;
}

int buscarPonto(GrafoDelivery *g, const char *nome) {
    for (int i = 0; i < g->numVertices; i++) {
        if (strcmp(g->nomes[i], nome) == 0) return i;
    }
    return -1;
}

int buscarOuAdicionarPonto(GrafoDelivery *g, const char *nome) {
    int id = buscarPonto(g, nome);
    if (id != -1) return id;
    if (g->numVertices >= MAX_VERTICES) return -1;
    strncpy(g->nomes[g->numVertices], nome, 49);
    g->nomes[g->numVertices][49] = '\0';
    return g->numVertices++;
}

void inserirArestaDirecionada(GrafoDelivery *g, int u, int v, int peso) {
    NoAdj *atual = g->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) {
            atual->peso = peso;
            return;
        }
        atual = atual->proximo;
    }
    NoAdj *novo = (NoAdj*) malloc(sizeof(NoAdj));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para aresta.\n");
        exit(EXIT_FAILURE);
    }
    novo->destino = v;
    novo->peso = peso;
    novo->proximo = g->adj[u];
    g->adj[u] = novo;
}

void adicionarRota(GrafoDelivery *g, const char *origem, const char *destino, int peso) {
    if (peso <= 0) {
        printf("[ERRO] O peso/distancia da rota deve ser positivo para o algoritmo de Dijkstra.\n");
        return;
    }
    if (strcmp(origem, destino) == 0) {
        printf("[ERRO] Origem e destino da rota devem ser distintos.\n");
        return;
    }
    int u = buscarOuAdicionarPonto(g, origem);
    int v = buscarOuAdicionarPonto(g, destino);
    if (u == -1 || v == -1) {
        printf("[ERRO] Limite maximo de pontos (%d) atingido!\n", MAX_VERTICES);
        return;
    }
    inserirArestaDirecionada(g, u, v, peso);
    inserirArestaDirecionada(g, v, u, peso);
    printf("[ROTA] '%s' <-> '%s' (custo/distancia: %d km)\n", origem, destino, peso);
}

void listarMapa(GrafoDelivery *g) {
    printf("\n--- MAPA DE ROTAS (LISTA DE ADJACENCIA - %d VERTICES) ---\n", g->numVertices);
    for (int i = 0; i < g->numVertices; i++) {
        printf("[%2d] %-22s -> ", i + 1, g->nomes[i]);
        NoAdj *aux = g->adj[i];
        while (aux != NULL) {
            printf("%s (%d km)%s", g->nomes[aux->destino], aux->peso,
                   aux->proximo != NULL ? " | " : "");
            aux = aux->proximo;
        }
        printf("\n");
    }
}

void dijkstra(GrafoDelivery *g, const char *nomeOrig, const char *nomeDest) {
    int orig = buscarPonto(g, nomeOrig);
    int dest = buscarPonto(g, nomeDest);
    if (orig == -1 || dest == -1) {
        printf("Ponto de origem ou destino nao cadastrado no mapa!\n");
        return;
    }

    int dist[MAX_VERTICES], visitado[MAX_VERTICES], anterior[MAX_VERTICES];
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = INF;
        visitado[i] = 0;
        anterior[i] = -1;
    }
    dist[orig] = 0;

    for (int count = 0; count < g->numVertices - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < g->numVertices; v++) {
            if (!visitado[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visitado[u] = 1;

        NoAdj *aresta = g->adj[u];
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;
            if (!visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                anterior[v] = u;
            }
            aresta = aresta->proximo;
        }
    }

    if (dist[dest] == INF) {
        printf("\nNao ha rota disponivel entre '%s' e '%s'!\n", nomeOrig, nomeDest);
        return;
    }

    printf("\n[DIJKSTRA] Menor rota de '%s' ate '%s':\n", nomeOrig, nomeDest);
    printf("  -> Custo minimo total: %d km\n  -> Caminho: ", dist[dest]);
    int caminho[MAX_VERTICES], tam = 0, curr = dest;
    while (curr != -1) {
        caminho[tam++] = curr;
        curr = anterior[curr];
    }
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s%s", g->nomes[caminho[i]], (i > 0) ? " -> " : "\n");
    }
}

// Simulação com 10 bairros + CD Central (11 vértices) e demonstração de rotas entre diferentes pares de pontos
void executarSimulacao(GrafoDelivery *g) {
    liberarGrafo(g);
    printf("\n========================================================================\n");
    printf("   SIMULACAO DE DELIVERY: 10 BAIRROS + CD CENTRAL (11 VERTICES - DIJKSTRA)\n");
    printf("========================================================================\n");

    adicionarRota(g, "CD Central", "Centro", 4);
    adicionarRota(g, "CD Central", "Distrito Industrial", 3);
    adicionarRota(g, "Centro", "Jardim Europa", 5);
    adicionarRota(g, "Centro", "Vila Nova", 6);
    adicionarRota(g, "Distrito Industrial", "Vila Nova", 4);
    adicionarRota(g, "Jardim Europa", "Bela Vista", 3);
    adicionarRota(g, "Vila Nova", "Bela Vista", 2);
    adicionarRota(g, "Vila Nova", "Sao Jose", 7);
    adicionarRota(g, "Bela Vista", "Morumbi", 4);
    adicionarRota(g, "Sao Jose", "Santa Cecilia", 3);
    adicionarRota(g, "Morumbi", "Parque das Flores", 5);
    adicionarRota(g, "Santa Cecilia", "Parque das Flores", 2);
    adicionarRota(g, "Parque das Flores", "Campus Universitario", 4);
    adicionarRota(g, "Morumbi", "Campus Universitario", 11);

    listarMapa(g);

    dijkstra(g, "CD Central", "Campus Universitario");
    dijkstra(g, "CD Central", "Morumbi");
    dijkstra(g, "Distrito Industrial", "Santa Cecilia");
    dijkstra(g, "Jardim Europa", "Parque das Flores");
    dijkstra(g, "Centro", "Santa Cecilia");
}

int main(void) {
    GrafoDelivery g;
    inicializar(&g);
    int op, peso;
    char p1[50], p2[50];

    do {
        printf("\n=== ROTEAMENTO DE DELIVERY (SITUACAO 11) ===\n");
        printf("1. Cadastrar Rota Ponderada\n");
        printf("2. Calcular Rota Minima (Dijkstra)\n");
        printf("3. Exibir Lista de Adjacencia do Mapa\n");
        printf("4. Executar Simulacao (10 Bairros + CD Central = 11 Vertices)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1:
                printf("Ponto de Origem: ");
                fgets(p1, 50, stdin);
                p1[strcspn(p1, "\n")] = '\0';
                printf("Ponto de Destino: ");
                fgets(p2, 50, stdin);
                p2[strcspn(p2, "\n")] = '\0';
                printf("Distancia/Custo (km): ");
                if (scanf("%d", &peso) != 1 || peso <= 0) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    printf("[ERRO] Distancia invalida! Informe um valor inteiro positivo.\n");
                    break;
                }
                getchar();
                adicionarRota(&g, p1, p2, peso);
                break;
            case 2:
                printf("Origem da entrega: ");
                fgets(p1, 50, stdin);
                p1[strcspn(p1, "\n")] = '\0';
                printf("Destino da entrega: ");
                fgets(p2, 50, stdin);
                p2[strcspn(p2, "\n")] = '\0';
                dijkstra(&g, p1, p2);
                break;
            case 3:
                listarMapa(&g);
                break;
            case 4:
                executarSimulacao(&g);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op != 0);

    liberarGrafo(&g);
    return 0;
}
