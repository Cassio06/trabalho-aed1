/*
 * ESTRUTURA DE DADOS: TABELA HASH COM ENCADEAMENTO
 * APLICAÇÃO: Situação Problema 14 - Contagem de Frequência de Palavras em um Texto
 *
 * JUSTIFICATIVA: Mapeia cada palavra única (chave) para sua contagem de ocorrências (valor),
 * permitindo localizar e incrementar a frequência de qualquer palavra em tempo médio O(1)
 * à medida que um artigo ou notícia é processado.
 *
 * COMPLEXIDADE:
 * - Tempo de Processamento do Texto: O(N) em média, onde N é o número de palavras no texto.
 * - Espaço: O(M + U), onde M é o número de buckets e U é o total de palavras distintas.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 31

typedef struct Palavra {
    char termo[50];
    int contagem;
    struct Palavra *proximo;
} Palavra;

typedef struct {
    Palavra *tabela[TAM_HASH];
    int totalPalavrasLidas;
    int totalDistintas;
} TabelaFrequencia;

void inicializar(TabelaFrequencia *tf) {
    for (int i = 0; i < TAM_HASH; i++) tf->tabela[i] = NULL;
    tf->totalPalavrasLidas = 0;
    tf->totalDistintas = 0;
}

void limparTabela(TabelaFrequencia *tf) {
    for (int i = 0; i < TAM_HASH; i++) {
        Palavra *atual = tf->tabela[i];
        while (atual != NULL) {
            Palavra *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
        tf->tabela[i] = NULL;
    }
    tf->totalPalavrasLidas = 0;
    tf->totalDistintas = 0;
}

int funcaoHash(const char *str) {
    unsigned long hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = (hash * 31 + (unsigned char)str[i]) % TAM_HASH;
    }
    return (int)hash;
}

void inserirPalavra(TabelaFrequencia *tf, const char *termoBruto) {
    char limpo[50];
    int k = 0;
    for (int i = 0; termoBruto[i] != '\0' && k < 49; i++) {
        unsigned char c = (unsigned char)termoBruto[i];
        if (isalnum(c)) {
            limpo[k++] = (char)tolower(c);
        }
    }
    limpo[k] = '\0';
    if (k == 0) return;

    tf->totalPalavrasLidas++;
    int idx = funcaoHash(limpo);
    Palavra *aux = tf->tabela[idx];
    while (aux != NULL) {
        if (strcmp(aux->termo, limpo) == 0) {
            aux->contagem++;
            return;
        }
        aux = aux->proximo;
    }

    Palavra *nova = (Palavra*) malloc(sizeof(Palavra));
    if (nova == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para palavra.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nova->termo, limpo);
    nova->contagem = 1;
    nova->proximo = tf->tabela[idx];
    tf->tabela[idx] = nova;
    tf->totalDistintas++;
}

void processarTexto(TabelaFrequencia *tf, const char *texto) {
    char copia[2048];
    strncpy(copia, texto, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char *token = strtok(copia, " \t\n\r,.;:!?()[]{}\"'/-");
    while (token != NULL) {
        inserirPalavra(tf, token);
        token = strtok(NULL, " \t\n\r,.;:!?()[]{}\"'/-");
    }
}

void exibirRelatorioFrequencia(TabelaFrequencia *tf, int topK) {
    printf("\n--- RELATORIO DE FREQUENCIA DE PALAVRAS ---\n");
    printf("Total de palavras processadas : %d\n", tf->totalPalavrasLidas);
    printf("Total de palavras distintas   : %d\n", tf->totalDistintas);

    if (tf->totalDistintas == 0) return;

    // Coleta os ponteiros para exibir as palavras mais frequentes em ordem decrescente
    Palavra **vetor = (Palavra**) malloc(tf->totalDistintas * sizeof(Palavra*));
    if (vetor == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para relatorio.\n");
        exit(EXIT_FAILURE);
    }
    int n = 0;
    for (int i = 0; i < TAM_HASH; i++) {
        Palavra *aux = tf->tabela[i];
        while (aux != NULL) {
            vetor[n++] = aux;
            aux = aux->proximo;
        }
    }

    // Ordena por maior contagem (e alfabeticamente em caso de empate)
    for (int i = 0; i < n - 1; i++) {
        int melhor = i;
        for (int j = i + 1; j < n; j++) {
            if (vetor[j]->contagem > vetor[melhor]->contagem ||
                (vetor[j]->contagem == vetor[melhor]->contagem &&
                 strcmp(vetor[j]->termo, vetor[melhor]->termo) < 0)) {
                melhor = j;
            }
        }
        Palavra *temp = vetor[i];
        vetor[i] = vetor[melhor];
        vetor[melhor] = temp;
    }

    int limite = (topK < n) ? topK : n;
    printf("\nTop %d palavras mais frequentes:\n", limite);
    for (int i = 0; i < limite; i++) {
        printf("  %2dº %-18s -> %d ocorrencia(s)\n",
               i + 1, vetor[i]->termo, vetor[i]->contagem);
    }

    free(vetor);
}

void executarSimulacaoArtigo(TabelaFrequencia *tf) {
    limparTabela(tf);
    const char *artigo =
        "A estrutura de dados tabela hash e amplamente utilizada em sistemas modernos de computacao. "
        "Em bancos de dados, compiladores e mecanismos de busca, a tabela hash permite localizar "
        "chaves em tempo constante medio. Quando duas chaves produzem o mesmo indice na tabela hash, "
        "ocorre uma colisao, que pode ser tratada com listas encadeadas. "
        "Na analise de textos e processamento de linguagem natural, contar a frequencia de cada palavra "
        "ajuda na criacao de indices invertidos, nuvens de palavras e deteccao de plagio. "
        "Por isso, escolher uma boa estrutura de dados e uma boa funcao hash garante eficiencia e "
        "escalabilidade no processamento de dados reais.";

    printf("\n==============================================================================\n");
    printf("   SIMULACAO: PROCESSAMENTO DE TEXTO TECNICO DE DEMONSTRACAO (TABELA HASH)    \n");
    printf("==============================================================================\n");
    printf("\nTexto analisado:\n\"%s\"\n", artigo);

    processarTexto(tf, artigo);
    exibirRelatorioFrequencia(tf, 12);
}

int main(void) {
    TabelaFrequencia tf;
    inicializar(&tf);
    int op;
    char texto[1024];

    do {
        printf("\n=== CONTAGEM DE FREQUENCIA DE PALAVRAS (SITUACAO 14) ===\n");
        printf("1. Digitar Texto para Analise\n");
        printf("2. Executar Simulacao com Texto Tecnico de Demonstracao\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1:
                limparTabela(&tf);
                printf("Digite o texto para analisar:\n");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0';
                processarTexto(&tf, texto);
                exibirRelatorioFrequencia(&tf, 10);
                break;
            case 2:
                executarSimulacaoArtigo(&tf);
                break;
        }
    } while (op != 0);

    limparTabela(&tf);
    return 0;
}
