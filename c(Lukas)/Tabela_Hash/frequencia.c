/*
 * ESTRUTURA DE DADOS: TABELA HASH COM ENCADEAMENTO
 * APLICAÇÃO: Situação Problema 14 - Contagem de Frequência de Palavras em um Texto
 *
 * JUSTIFICATIVA: Mapeia cada palavra única (chave) para sua contagem de ocorrências (valor),
 * permitindo localizar e incrementar a frequência de qualquer palavra em tempo médio O(1)
 * à medida que um artigo ou notícia é processado.
 *
 * COMPLEXIDADE:
 * - Tokenizacao: O(B), nos B bytes do texto. Contagem linear esperada com
 *   distribuicao adequada e fator de carga controlado (na demo, M = 31 fixo).
 * - Ranking: O(U^2) comparacoes para U palavras distintas.
 * - Espaco: O(M + S + B), com S bytes das palavras distintas armazenadas.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 31

typedef struct Palavra {
    char *termo; // Tamanho exato em bytes UTF-8, sem truncar palavras longas.
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
            free(atual->termo);
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
        // Base 33 e modulo 31: o prefixo participa do indice final.
        hash = (hash * 33 + (unsigned char)str[i]) % TAM_HASH;
    }
    return (int)hash;
}

// Recebe uma palavra ja normalizada pelo tokenizador UTF-8 abaixo.
void inserirPalavra(TabelaFrequencia *tf, const char *limpo) {
    if (*limpo == '\0') return;
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
    nova->termo = (char*) malloc(strlen(limpo) + 1);
    if (nova->termo == NULL) {
        free(nova);
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para termo.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nova->termo, limpo);
    nova->contagem = 1;
    nova->proximo = tf->tabela[idx];
    tf->tabela[idx] = nova;
    tf->totalDistintas++;
}

// Decodifica UTF-8 sem depender do locale do sistema. Bytes invalidos separam termos.
static size_t lerCodigoUtf8(const unsigned char *s, unsigned int *codigo) {
    unsigned int c = s[0];
    if (c < 0x80) { *codigo = c; return 1; }
    size_t tamanho;
    unsigned int minimo;
    if (c >= 0xC2 && c <= 0xDF) { tamanho = 2; minimo = 0x80; c &= 0x1F; }
    else if (c >= 0xE0 && c <= 0xEF) { tamanho = 3; minimo = 0x800; c &= 0x0F; }
    else if (c >= 0xF0 && c <= 0xF4) { tamanho = 4; minimo = 0x10000; c &= 0x07; }
    else { *codigo = 0; return 1; }
    for (size_t i = 1; i < tamanho; i++) {
        if ((s[i] & 0xC0) != 0x80) { *codigo = 0; return 1; }
        c = (c << 6) | (s[i] & 0x3F);
    }
    if (c < minimo || c > 0x10FFFF || (c >= 0xD800 && c <= 0xDFFF)) {
        *codigo = 0;
        return 1;
    }
    *codigo = c;
    return tamanho;
}

void processarTexto(TabelaFrequencia *tf, const char *texto) {
    // Letras ASCII e latinas precompostas (incluindo todos os acentos portugueses)
    // e digitos formam palavras; pontuacao, hifens e demais simbolos separam termos.
    char *palavra = (char*) malloc(strlen(texto) + 1);
    if (palavra == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para texto.\n");
        exit(EXIT_FAILURE);
    }
    size_t usados = 0;
    const unsigned char *p = (const unsigned char*) texto;
    while (*p != '\0') {
        unsigned int codigo;
        size_t bytes = lerCodigoUtf8(p, &codigo);
        int latino = (codigo >= 0xC0 && codigo <= 0xFF
                      && codigo != 0xD7 && codigo != 0xF7);
        if ((codigo < 0x80 && isalnum((unsigned char)codigo)) || latino) {
            if (codigo >= 'A' && codigo <= 'Z') codigo += 'a' - 'A';
            else if (codigo >= 0xC0 && codigo <= 0xDE) codigo += 0x20;
            if (codigo < 0x80) palavra[usados++] = (char)codigo;
            else {
                palavra[usados++] = (char)(0xC0 | (codigo >> 6));
                palavra[usados++] = (char)(0x80 | (codigo & 0x3F));
            }
        } else if (usados > 0) {
            palavra[usados] = '\0';
            inserirPalavra(tf, palavra);
            usados = 0;
        }
        p += bytes;
    }
    palavra[usados] = '\0';
    inserirPalavra(tf, palavra);
    free(palavra);
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
    // Texto real em dominio publico, transcrito sem modernizar a grafia de 1899.
    // ASSIS, Machado de. Dom Casmurro. Cap. I, primeiro paragrafo.
    // Fonte: https://pt.wikisource.org/wiki/Dom_Casmurro/I (acesso: 11/11/2026).
    const char *artigo =
        "Uma noite destas, vindo da cidade para o Engenho Novo, encontrei no trem da Central "
        "um rapaz aqui do bairro, que eu conheço de vista e de chapéo. Comprimentou-me, "
        "sentou-se ao pé de mim, falou da lua e dos ministros, e acabou recitando-me versos. "
        "A viagem era curta, e os versos pôde ser que não fossem inteiramente maus. Succedeu, "
        "porém, que como eu estava cançado, fechei os olhos tres ou quatro vezes; tanto bastou "
        "para que elle interrompesse a leitura e mettesse os versos no bolso.";

    printf("\n==============================================================================\n");
    printf("   SIMULACAO: TEXTO REAL - Dom Casmurro, Machado de Assis (1899)          \n");
    printf("==============================================================================\n");
    printf("Fonte: Wikisource - https://pt.wikisource.org/wiki/Dom_Casmurro/I\n");
    printf("Capitulo I, primeiro paragrafo; grafia original preservada.\n");
    printf("\nTexto analisado:\n\"%s\"\n", artigo);

    processarTexto(tf, artigo);
    exibirRelatorioFrequencia(tf, 12);
}

// Le uma linha inteira, inclusive acima dos antigos limites de 1024/2048 bytes.
static char *lerLinhaTexto(void) {
    size_t capacidade = 128, tamanho = 0;
    char *texto = (char*) malloc(capacidade);
    if (texto == NULL) exit(EXIT_FAILURE);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (tamanho + 1 >= capacidade) {
            capacidade *= 2;
            char *ampliado = (char*) realloc(texto, capacidade);
            if (ampliado == NULL) { free(texto); exit(EXIT_FAILURE); }
            texto = ampliado;
        }
        texto[tamanho++] = (char)c;
    }
    texto[tamanho] = '\0';
    return texto;
}

int main(void) {
    TabelaFrequencia tf;
    inicializar(&tf);
    int op;

    do {
        printf("\n=== CONTAGEM DE FREQUENCIA DE PALAVRAS (SITUACAO 14) ===\n");
        printf("1. Digitar Texto para Analise\n");
        printf("2. Executar Simulacao com Texto Real (Dom Casmurro)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        int resto;
        while ((resto = getchar()) != '\n' && resto != EOF) {}

        switch (op) {
            case 1: {
                limparTabela(&tf);
                printf("Digite o texto para analisar:\n");
                char *texto = lerLinhaTexto();
                processarTexto(&tf, texto);
                free(texto);
                exibirRelatorioFrequencia(&tf, 10);
                break;
            }
            case 2:
                executarSimulacaoArtigo(&tf);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (op != 0);

    limparTabela(&tf);
    return 0;
}
