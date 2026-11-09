/*
 * ESTRUTURA DE DADOS: GRAFO NÃO-DIRECIONADO
 * APLICAÇÃO: Situação Problema 12 - Rede de Amizades em uma Rede Social Simples
 *
 * JUSTIFICATIVA: O grafo não-direcionado modela conexões simétricas entre usuários
 * (se A é amigo de B, B é amigo de A). Permite identificar amigos em comum, sugerir
 * novas conexões (amigos de 2º grau) e calcular graus de separação com Busca em Largura (BFS).
 *
 * COMPLEXIDADE:
 * - Adicionar amizade: O(1) após localizar os vértices.
 * - Listar amigos e Amigos em comum: O(V).
 * - Busca em Largura (BFS) para graus de separação: O(V^2) em matriz de adjacência.
 * - Espaço: O(V^2).
 */

#include <stdio.h>
#include <string.h>

#define MAX 25

typedef struct {
    char nomes[MAX][50];
    int matriz[MAX][MAX];
    int totalUsuarios;
} RedeSocial;

void inicializar(RedeSocial *r) {
    r->totalUsuarios = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++) r->matriz[i][j] = 0;
}

int buscarUsuario(RedeSocial *r, const char *nome) {
    for (int i = 0; i < r->totalUsuarios; i++)
        if (strcmp(r->nomes[i], nome) == 0) return i;
    return -1;
}

int buscarOuAdicionarUsuario(RedeSocial *r, const char *nome) {
    int id = buscarUsuario(r, nome);
    if (id != -1) return id;
    if (r->totalUsuarios >= MAX) return -1;
    strncpy(r->nomes[r->totalUsuarios], nome, 49);
    r->nomes[r->totalUsuarios][49] = '\0';
    return r->totalUsuarios++;
}

void conectarAmigos(RedeSocial *r, const char *u1, const char *u2) {
    if (strcmp(u1, u2) == 0) {
        printf("[ERRO] Um usuario nao pode adicionar a si mesmo como amigo.\n");
        return;
    }
    int id1 = buscarOuAdicionarUsuario(r, u1);
    int id2 = buscarOuAdicionarUsuario(r, u2);
    if (id1 == -1 || id2 == -1) {
        printf("[ERRO] Limite maximo de usuarios (%d) atingido!\n", MAX);
        return;
    }
    r->matriz[id1][id2] = 1;
    r->matriz[id2][id1] = 1;
    printf("[AMIZADE] %s <-> %s conectados!\n", u1, u2);
}

void listarAmigos(RedeSocial *r, const char *nome) {
    int id = buscarUsuario(r, nome);
    if (id == -1) {
        printf("Usuario '%s' nao encontrado.\n", nome);
        return;
    }
    int cont = 0;
    printf("\nAmigos de %s:\n", nome);
    for (int j = 0; j < r->totalUsuarios; j++) {
        if (r->matriz[id][j] == 1) {
            printf("  - %s\n", r->nomes[j]);
            cont++;
        }
    }
    if (cont == 0) printf("  (Nenhum amigo cadastrado)\n");
}

void amigosEmComum(RedeSocial *r, const char *u1, const char *u2) {
    int id1 = buscarUsuario(r, u1);
    int id2 = buscarUsuario(r, u2);
    if (id1 == -1 || id2 == -1) {
        printf("Um ou ambos os usuarios nao existem na rede.\n");
        return;
    }
    int cont = 0;
    printf("\nAmigos em comum entre %s e %s:\n", u1, u2);
    for (int j = 0; j < r->totalUsuarios; j++) {
        if (r->matriz[id1][j] == 1 && r->matriz[id2][j] == 1) {
            printf("  - %s\n", r->nomes[j]);
            cont++;
        }
    }
    if (cont == 0) printf("  (Nenhum amigo em comum)\n");
}

void sugerirConexoes(RedeSocial *r, const char *nome) {
    int id = buscarUsuario(r, nome);
    if (id == -1) {
        printf("Usuario '%s' nao encontrado.\n", nome);
        return;
    }
    int cont = 0;
    printf("\nSugestoes de amizade para %s (amigos de amigos):\n", nome);
    for (int candidato = 0; candidato < r->totalUsuarios; candidato++) {
        if (candidato == id || r->matriz[id][candidato] == 1) continue;
        int emComum = 0;
        for (int k = 0; k < r->totalUsuarios; k++) {
            if (r->matriz[id][k] == 1 && r->matriz[candidato][k] == 1) {
                emComum++;
            }
        }
        if (emComum > 0) {
            printf("  - %s (%d amigo(s) em comum)\n", r->nomes[candidato], emComum);
            cont++;
        }
    }
    if (cont == 0) printf("  (Nenhuma sugestao disponivel)\n");
}

// BFS para calcular graus de separação entre dois usuários
void grauSeparacaoBFS(RedeSocial *r, const char *u1, const char *u2) {
    int orig = buscarUsuario(r, u1);
    int dest = buscarUsuario(r, u2);
    if (orig == -1 || dest == -1) {
        printf("Um ou ambos os usuarios nao existem na rede.\n");
        return;
    }
    if (orig == dest) {
        printf("\n[BFS] '%s' e '%s' sao o mesmo usuario (grau 0).\n", u1, u2);
        return;
    }

    int fila[MAX], inicio = 0, fim = 0;
    int distancia[MAX], anterior[MAX];
    for (int i = 0; i < r->totalUsuarios; i++) {
        distancia[i] = -1;
        anterior[i] = -1;
    }

    distancia[orig] = 0;
    fila[fim++] = orig;

    while (inicio < fim) {
        int atual = fila[inicio++];
        if (atual == dest) break;

        for (int vizinho = 0; vizinho < r->totalUsuarios; vizinho++) {
            if (r->matriz[atual][vizinho] == 1 && distancia[vizinho] == -1) {
                distancia[vizinho] = distancia[atual] + 1;
                anterior[vizinho] = atual;
                fila[fim++] = vizinho;
            }
        }
    }

    if (distancia[dest] == -1) {
        printf("\n[BFS] %s e %s NAO estao conectados na rede.\n", u1, u2);
        return;
    }

    printf("\n[BFS] Grau de separacao entre %s e %s: %d grau(s)\n", u1, u2, distancia[dest]);
    int caminho[MAX], tam = 0, curr = dest;
    while (curr != -1) {
        caminho[tam++] = curr;
        curr = anterior[curr];
    }
    printf("  -> Cadeia de conexao: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s%s", r->nomes[caminho[i]], (i > 0) ? " -> " : "\n");
    }
}

// Simulação com pelo menos 15 usuários e consultas de relacionamentos
void executarSimulacao(RedeSocial *r) {
    inicializar(r);
    printf("\n================================================================\n");
    printf("   SIMULACAO: REDE SOCIAL COM 15 USUARIOS E CONSULTAS (BFS)     \n");
    printf("================================================================\n");

    const char *usuarios[15] = {
        "Ana", "Bruno", "Carla", "Daniel", "Elisa",
        "Fabio", "Gabriela", "Heitor", "Isabela", "Joao",
        "Karen", "Lucas", "Marina", "Nicolas", "Olivia"
    };
    for (int i = 0; i < 15; i++) {
        buscarOuAdicionarUsuario(r, usuarios[i]);
    }

    conectarAmigos(r, "Ana", "Bruno");
    conectarAmigos(r, "Ana", "Carla");
    conectarAmigos(r, "Ana", "Daniel");
    conectarAmigos(r, "Bruno", "Carla");
    conectarAmigos(r, "Bruno", "Elisa");
    conectarAmigos(r, "Carla", "Fabio");
    conectarAmigos(r, "Daniel", "Gabriela");
    conectarAmigos(r, "Elisa", "Heitor");
    conectarAmigos(r, "Fabio", "Heitor");
    conectarAmigos(r, "Gabriela", "Isabela");
    conectarAmigos(r, "Heitor", "Joao");
    conectarAmigos(r, "Isabela", "Karen");
    conectarAmigos(r, "Joao", "Lucas");
    conectarAmigos(r, "Karen", "Marina");
    conectarAmigos(r, "Lucas", "Nicolas");
    conectarAmigos(r, "Marina", "Olivia");

    listarAmigos(r, "Ana");
    amigosEmComum(r, "Ana", "Bruno");
    amigosEmComum(r, "Elisa", "Fabio");
    sugerirConexoes(r, "Ana");
    grauSeparacaoBFS(r, "Ana", "Heitor");
    grauSeparacaoBFS(r, "Ana", "Olivia");
    grauSeparacaoBFS(r, "Bruno", "Nicolas");
}

int main(void) {
    RedeSocial r;
    inicializar(&r);
    int op;
    char u1[50], u2[50];

    do {
        printf("\n=== REDE SOCIAL DE AMIZADES (SITUACAO 12) ===\n");
        printf("1. Adicionar Amizade\n");
        printf("2. Listar Amigos de um Usuario\n");
        printf("3. Descobrir Amigos em Comum\n");
        printf("4. Sugerir Novas Conexoes\n");
        printf("5. Calcular Graus de Separacao (BFS)\n");
        printf("6. Executar Simulacao com 15 Usuarios\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1:
                printf("Usuario 1: ");
                fgets(u1, 50, stdin);
                u1[strcspn(u1, "\n")] = '\0';
                printf("Usuario 2: ");
                fgets(u2, 50, stdin);
                u2[strcspn(u2, "\n")] = '\0';
                conectarAmigos(&r, u1, u2);
                break;
            case 2:
                printf("Usuario: ");
                fgets(u1, 50, stdin);
                u1[strcspn(u1, "\n")] = '\0';
                listarAmigos(&r, u1);
                break;
            case 3:
                printf("Usuario 1: ");
                fgets(u1, 50, stdin);
                u1[strcspn(u1, "\n")] = '\0';
                printf("Usuario 2: ");
                fgets(u2, 50, stdin);
                u2[strcspn(u2, "\n")] = '\0';
                amigosEmComum(&r, u1, u2);
                break;
            case 4:
                printf("Usuario: ");
                fgets(u1, 50, stdin);
                u1[strcspn(u1, "\n")] = '\0';
                sugerirConexoes(&r, u1);
                break;
            case 5:
                printf("Usuario de origem: ");
                fgets(u1, 50, stdin);
                u1[strcspn(u1, "\n")] = '\0';
                printf("Usuario de destino: ");
                fgets(u2, 50, stdin);
                u2[strcspn(u2, "\n")] = '\0';
                grauSeparacaoBFS(&r, u1, u2);
                break;
            case 6:
                executarSimulacao(&r);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op != 0);

    return 0;
}
