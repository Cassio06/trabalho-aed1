/*
 * ESTRUTURA DE DADOS: LISTA ENCADEADA SIMPLES
 * APLICAÇÃO: Situação Problema 5 - Gerenciamento de Playlist de Músicas
 *
 * JUSTIFICATIVA: Listas encadeadas permitem inserções, remoções e reordenações dinâmicas
 * de músicas em qualquer posição da playlist (início, fim ou posição intermediária)
 * sem necessidade de realocação de vetor ou deslocamento físico em bloco.
 *
 * COMPLEXIDADE:
 * - Inserir no início: O(1)
 * - Inserir no fim / Inserir em posição específica / Remover por título / Buscar / Reordenar: O(N)
 * - Listar playlist: O(N)
 * - Espaço: O(N) alocado dinamicamente conforme o número de músicas.
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
    int tamanho;
} Playlist;

void inicializar(Playlist *p) {
    p->inicio = NULL;
    p->tamanho = 0;
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

Musica* novaMusicaDados(const char *titulo, const char *artista, float duracao) {
    Musica *nova = (Musica*) malloc(sizeof(Musica));
    if (nova == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para musica.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(nova->titulo, titulo, 49);
    nova->titulo[49] = '\0';
    strncpy(nova->artista, artista, 49);
    nova->artista[49] = '\0';
    nova->duracao = duracao;
    nova->proximo = NULL;
    return nova;
}

Musica* lerMusicaConsole() {
    char titulo[50], artista[50];
    float duracao;
    printf("Titulo da musica: ");
    fgets(titulo, 50, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';
    printf("Artista: ");
    fgets(artista, 50, stdin);
    artista[strcspn(artista, "\n")] = '\0';
    printf("Duracao (minutos, ex: 3.45): ");
    while (scanf("%f", &duracao) != 1 || duracao <= 0.0f) {
        limparBufferEntrada();
        printf("Valor invalido. Informe uma duracao positiva (ex: 3.45): ");
    }
    limparBufferEntrada();
    return novaMusicaDados(titulo, artista, duracao);
}

void inserirInicioDados(Playlist *p, const char *titulo, const char *artista, float duracao) {
    Musica *nova = novaMusicaDados(titulo, artista, duracao);
    nova->proximo = p->inicio;
    p->inicio = nova;
    p->tamanho++;
    printf("[+] Adicionada no inicio: '%s' - %s (%.2f min)\n", titulo, artista, duracao);
}

void inserirFimDados(Playlist *p, const char *titulo, const char *artista, float duracao) {
    Musica *nova = novaMusicaDados(titulo, artista, duracao);
    if (p->inicio == NULL) {
        p->inicio = nova;
    } else {
        Musica *aux = p->inicio;
        while (aux->proximo != NULL) aux = aux->proximo;
        aux->proximo = nova;
    }
    p->tamanho++;
    printf("[+] Adicionada no fim: '%s' - %s (%.2f min)\n", titulo, artista, duracao);
}

// Insere em posição específica (1 = início, tamanho + 1 = fim)
void inserirPosicaoDados(Playlist *p, const char *titulo, const char *artista, float duracao, int pos) {
    if (pos <= 1 || p->inicio == NULL) {
        inserirInicioDados(p, titulo, artista, duracao);
        return;
    }
    if (pos > p->tamanho) {
        inserirFimDados(p, titulo, artista, duracao);
        return;
    }
    Musica *nova = novaMusicaDados(titulo, artista, duracao);
    Musica *atual = p->inicio;
    for (int i = 1; i < pos - 1 && atual->proximo != NULL; i++) {
        atual = atual->proximo;
    }
    nova->proximo = atual->proximo;
    atual->proximo = nova;
    p->tamanho++;
    printf("[+] Adicionada na posicao %d: '%s' - %s (%.2f min)\n", pos, titulo, artista, duracao);
}

void removerPorTitulo(Playlist *p, const char *titulo) {
    if (p->inicio == NULL) {
        printf("Playlist vazia!\n");
        return;
    }
    Musica *atual = p->inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Musica '%s' nao encontrada!\n", titulo);
        return;
    }
    if (anterior == NULL) p->inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    p->tamanho--;
    printf("[-] Musica '%s' removida com sucesso!\n", titulo);
}

void buscarPorTitulo(Playlist *p, const char *titulo) {
    Musica *aux = p->inicio;
    int pos = 1;
    while (aux != NULL) {
        if (strcmp(aux->titulo, titulo) == 0) {
            printf("[BUSCA] Encontrada na posicao %d: '%s' - %s (%.2f min)\n",
                   pos, aux->titulo, aux->artista, aux->duracao);
            return;
        }
        aux = aux->proximo;
        pos++;
    }
    printf("[BUSCA] Musica '%s' nao encontrada na playlist.\n", titulo);
}

// Reordena movendo uma música da posição de origem para a posição de destino
void moverMusica(Playlist *p, int origem, int destino) {
    if (p->inicio == NULL || origem < 1 || origem > p->tamanho ||
        destino < 1 || destino > p->tamanho || origem == destino) {
        printf("Posicoes invalidas para reordenacao.\n");
        return;
    }
    Musica *atual = p->inicio, *anterior = NULL;
    for (int i = 1; i < origem; i++) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (anterior == NULL) p->inicio = atual->proximo;
    else anterior->proximo = atual->proximo;

    if (destino == 1) {
        atual->proximo = p->inicio;
        p->inicio = atual;
    } else {
        Musica *cursor = p->inicio;
        for (int i = 1; i < destino - 1 && cursor->proximo != NULL; i++) {
            cursor = cursor->proximo;
        }
        atual->proximo = cursor->proximo;
        cursor->proximo = atual;
    }
    printf("[REORDENACAO] Musica '%s' movida da posicao %d para %d!\n",
           atual->titulo, origem, destino);
}

void listar(Playlist *p) {
    if (p->inicio == NULL) {
        printf("Playlist vazia!\n");
        return;
    }
    Musica *aux = p->inicio;
    int pos = 1;
    float totalDuracao = 0.0f;
    printf("\n--- MINHA PLAYLIST (%d musicas) ---\n", p->tamanho);
    while (aux != NULL) {
        printf("%2d. %-28s | %-20s | %.2f min\n", pos++, aux->titulo, aux->artista, aux->duracao);
        totalDuracao += aux->duracao;
        aux = aux->proximo;
    }
    printf("Tempo total da playlist: %.2f min\n", totalDuracao);
}

void limparPlaylist(Playlist *p) {
    Musica *atual = p->inicio;
    while (atual != NULL) {
        Musica *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    p->inicio = NULL;
    p->tamanho = 0;
}

// Simulação de criação e edição de uma playlist com pelo menos 12 músicas
void executarSimulacao(Playlist *p) {
    limparPlaylist(p);
    printf("\n============================================================\n");
    printf("   SIMULACAO: CRIACAO E EDICAO DE PLAYLIST (12 MUSICAS)     \n");
    printf("============================================================\n");

    inserirFimDados(p, "Bohemian Rhapsody", "Queen", 5.92f);
    inserirFimDados(p, "Hotel California", "Eagles", 6.50f);
    inserirFimDados(p, "Imagine", "John Lennon", 3.07f);
    inserirFimDados(p, "Smells Like Teen Spirit", "Nirvana", 5.02f);
    inserirFimDados(p, "Billie Jean", "Michael Jackson", 4.90f);
    inserirFimDados(p, "Sweet Child O' Mine", "Guns N' Roses", 5.93f);
    inserirFimDados(p, "Wonderwall", "Oasis", 4.30f);
    inserirFimDados(p, "Lose Yourself", "Eminem", 5.33f);
    inserirFimDados(p, "Clocks", "Coldplay", 5.08f);
    inserirFimDados(p, "Tempo Perdido", "Legiao Urbana", 5.03f);
    inserirInicioDados(p, "Aquarela", "Toquinho", 4.25f);
    inserirPosicaoDados(p, "Evidencias", "Chitaozinho & Xororo", 4.65f, 4);

    listar(p);

    printf("\n--- Testando Busca, Reordenacao e Remocao ---\n");
    buscarPorTitulo(p, "Evidencias");
    buscarPorTitulo(p, "Inexistente");
    moverMusica(p, 12, 2);
    removerPorTitulo(p, "Imagine");

    listar(p);
}

int main() {
    Playlist p;
    inicializar(&p);
    int op, pos, orig, dest;
    char busca[50];

    do {
        printf("\n=== GERENCIADOR DE PLAYLIST (SITUACAO 5) ===\n");
        printf("1. Inserir no Inicio\n");
        printf("2. Inserir no Fim\n");
        printf("3. Inserir em Posicao Especifica\n");
        printf("4. Remover por Titulo\n");
        printf("5. Buscar por Titulo\n");
        printf("6. Reordenar Musica (Mover Posicao)\n");
        printf("7. Listar Playlist\n");
        printf("8. Executar Simulacao Completa (12 Musicas)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1: {
                Musica *m = lerMusicaConsole();
                inserirInicioDados(&p, m->titulo, m->artista, m->duracao);
                free(m);
                break;
            }
            case 2: {
                Musica *m = lerMusicaConsole();
                inserirFimDados(&p, m->titulo, m->artista, m->duracao);
                free(m);
                break;
            }
            case 3: {
                Musica *m = lerMusicaConsole();
                printf("Posicao desejada (1 a %d): ", p.tamanho + 1);
                if (scanf("%d", &pos) != 1) {
                    limparBufferEntrada();
                    printf("Posicao invalida!\n");
                    free(m);
                    break;
                }
                limparBufferEntrada();
                inserirPosicaoDados(&p, m->titulo, m->artista, m->duracao, pos);
                free(m);
                break;
            }
            case 4:
                printf("Titulo a remover: ");
                fgets(busca, 50, stdin);
                busca[strcspn(busca, "\n")] = '\0';
                removerPorTitulo(&p, busca);
                break;
            case 5:
                printf("Titulo a buscar: ");
                fgets(busca, 50, stdin);
                busca[strcspn(busca, "\n")] = '\0';
                buscarPorTitulo(&p, busca);
                break;
            case 6:
                printf("Posicao de origem: ");
                if (scanf("%d", &orig) != 1) {
                    limparBufferEntrada();
                    printf("Posicao de origem invalida!\n");
                    break;
                }
                printf("Posicao de destino: ");
                if (scanf("%d", &dest) != 1) {
                    limparBufferEntrada();
                    printf("Posicao de destino invalida!\n");
                    break;
                }
                limparBufferEntrada();
                moverMusica(&p, orig, dest);
                break;
            case 7:
                listar(&p);
                break;
            case 8:
                executarSimulacao(&p);
                break;
        }
    } while (op != 0);

    limparPlaylist(&p);
    return 0;
}
