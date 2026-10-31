/*
 * ESTRUTURA DE DADOS: TABELA HASH COM ENCADEAMENTO
 * APLICAÇÃO: Contagem de Frequência de Palavras em Texto
 * 
 * JUSTIFICATIVA: Mapeia cada palavra única (chave) para uma contagem de ocorrências (valor),
 * permitindo incrementar a frequência em tempo médio O(1) à medida que o texto é lido.
 * 
 * COMPLEXIDADE:
 * - Tempo de Processamento: O(N), onde N é o total de palavras do texto.
 * - Espaço: O(U), onde U é o número de palavras únicas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 20

typedef struct Palavra {
    char termo[50];
    int contagem;
    struct Palavra *proximo;
} Palavra;

typedef struct {
    Palavra *tabela[TAM_HASH];
} TabelaFrequencia;

void inicializar(TabelaFrequencia *tf) {
    for (int i = 0; i < TAM_HASH; i++) tf->tabela[i] = NULL;
}

int funcaoHash(char *str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) hash += str[i];
    return hash % TAM_HASH;
}

void inserirPalavra(TabelaFrequencia *tf, char *termo) {
    int idx = funcaoHash(termo);
    Palavra *aux = tf->tabela[idx];
    while (aux != NULL) {
        if (strcmp(aux->termo, termo) == 0) { aux->contagem++; return; }
        aux = aux->proximo;
    }
    Palavra *nova = (Palavra*) malloc(sizeof(Palavra));
    strcpy(nova->termo, termo);
    nova->contagem = 1;
    nova->proximo = tf->tabela[idx];
    tf->tabela[idx] = nova;
}

void exibirFrequencia(TabelaFrequencia *tf) {
    printf("\n--- FREQUENCIA DE PALAVRAS ---\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Palavra *aux = tf->tabela[i];
        while (aux != NULL) {
            printf("Palavra: '%s' | Ocorrencias: %d\n", aux->termo, aux->contagem);
            aux = aux->proximo;
        }
    }
}

int main() {
    TabelaFrequencia tf; inicializar(&tf);
    char texto[200], *palavra;
    printf("Digite uma frase/texto para analisar: ");
    fgets(texto, 200, stdin); texto[strcspn(texto, "\n")] = '\0';

    palavra = strtok(texto, " ,.-");
    while (palavra != NULL) {
        inserirPalavra(&tf, palavra);
        palavra = strtok(NULL, " ,.-");
    }
    exibirFrequencia(&tf);
    return 0;
}
