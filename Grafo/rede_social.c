/*
 * ESTRUTURA DE DADOS: GRAFO NÃO-DIRECIONADO (Matriz de Adjacência)
 * APLICAÇÃO: Rede Social de Amizades
 * 
 * JUSTIFICATIVA: O grafo não-direcionado modela conexões simétricas (se A é amigo de B, B é amigo de A).
 * Permite mapear conexões, listar contatos e analisar graus de separação.
 * 
 * COMPLEXIDADE:
 * - Adicionar Amizade: O(1)
 * - Consulta de Amigos: O(V)
 * - Espaço: O(V^2)
 */

#include <stdio.h>
#include <string.h>

#define MAX 15

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

int buscarOuAdicionarUsuario(RedeSocial *r, char *nome) {
    for (int i = 0; i < r->totalUsuarios; i++)
        if (strcmp(r->nomes[i], nome) == 0) return i;
    if (r->totalUsuarios >= MAX) return -1;
    strcpy(r->nomes[r->totalUsuarios], nome);
    return r->totalUsuarios++;
}

void conectarAmigos(RedeSocial *r, char *u1, char *u2) {
    int id1 = buscarOuAdicionarUsuario(r, u1);
    int id2 = buscarOuAdicionarUsuario(r, u2);
    if (id1 != -1 && id2 != -1) {
        r->matriz[id1][id2] = 1;
        r->matriz[id2][id1] = 1;
        printf("Amizade registrada entre %s e %s!\n", u1, u2);
    }
}

void listarAmigos(RedeSocial *r, char *nome) {
    int id = buscarOuAdicionarUsuario(r, nome);
    printf("\nAmigos de %s:\n", nome);
    for (int j = 0; j < r->totalUsuarios; j++)
        if (r->matriz[id][j] == 1) printf("- %s\n", r->nomes[j]);
}

int main() {
    RedeSocial r; inicializar(&r);
    int op; char u1[50], u2[50];
    do {
        printf("\n=== REDE SOCIAL DE AMIZADES ===\n1. Adicionar Amizade\n2. Listar Amigos de um Usuario\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1:
                printf("Usuario 1: "); fgets(u1, 50, stdin); u1[strcspn(u1, "\n")] = '\0';
                printf("Usuario 2: "); fgets(u2, 50, stdin); u2[strcspn(u2, "\n")] = '\0';
                conectarAmigos(&r, u1, u2); break;
            case 2:
                printf("Usuario: "); fgets(u1, 50, stdin); u1[strcspn(u1, "\n")] = '\0';
                listarAmigos(&r, u1); break;
        }
    } while (op != 0);
    return 0;
}
