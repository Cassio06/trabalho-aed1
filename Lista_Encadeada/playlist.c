/*
 * ESTRUTURA DE DADOS: LISTA ENCADEADA SIMPLES
 * APLICAÇÃO: Gerenciamento de Playlist de Músicas
 * 
 * JUSTIFICATIVA: Listas encadeadas permitem inserções e remoções dinâmicas de músicas 
 * em qualquer posição da playlist sem a necessidade de deslocamento manual de elementos.
 * 
 * COMPLEXIDADE:
 * - Inserção no início: O(1)
 * - Inserção no fim / Busca / Remoção: O(N)
 * - Espaço: O(N) alocado dinamicamente.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char titulo[50];
    char artista[50];
    float duracao;
    struct Musica *proximo;
} Musica;

typedef struct {
    Musica *inicio;
} Playlist;

void inicializar(Playlist *p) { p->inicio = NULL; }

Musica* criarMusica() {
    Musica *nova = (Musica*) malloc(sizeof(Musica));
    printf("Titulo da musica: "); fgets(nova->titulo, 50, stdin); nova->titulo[strcspn(nova->titulo, "\n")] = '\0';
    printf("Artista: "); fgets(nova->artista, 50, stdin); nova->artista[strcspn(nova->artista, "\n")] = '\0';
    printf("Duracao (minutos): "); scanf("%f", &nova->duracao); getchar();
    nova->proximo = NULL;
    return nova;
}

void inserirInicio(Playlist *p) {
    Musica *nova = criarMusica();
    nova->proximo = p->inicio;
    p->inicio = nova;
    printf("Musica adicionada no inicio!\n");
}

void inserirFim(Playlist *p) {
    Musica *nova = criarMusica();
    if (p->inicio == NULL) { p->inicio = nova; } 
    else {
        Musica *aux = p->inicio;
        while (aux->proximo != NULL) aux = aux->proximo;
        aux->proximo = nova;
    }
    printf("Musica adicionada no fim!\n");
}

void removerPorTitulo(Playlist *p, char *titulo) {
    if (p->inicio == NULL) { printf("Playlist vazia!\n"); return; }
    Musica *atual = p->inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) { printf("Musica nao encontrada!\n"); return; }
    if (anterior == NULL) p->inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    printf("Musica removida com sucesso!\n");
}

void listar(Playlist *p) {
    if (p->inicio == NULL) { printf("Playlist vazia!\n"); return; }
    Musica *aux = p->inicio;
    int pos = 1;
    printf("\n--- MINHA PLAYLIST ---\n");
    while (aux != NULL) {
        printf("%d. %s - %s (%.2f min)\n", pos++, aux->titulo, aux->artista, aux->duracao);
        aux = aux->proximo;
    }
}

int main() {
    Playlist p; inicializar(&p);
    int op; char busca[50];
    do {
        printf("\n=== GERENCIADOR DE PLAYLIST ===\n1. Inserir no Inicio\n2. Inserir no Fim\n3. Remover por Titulo\n4. Listar Playlist\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1: inserirInicio(&p); break;
            case 2: inserirFim(&p); break;
            case 3: printf("Titulo: "); fgets(busca, 50, stdin); busca[strcspn(busca, "\n")] = '\0'; removerPorTitulo(&p, busca); break;
            case 4: listar(&p); break;
        }
    } while (op != 0);
    return 0;
}
