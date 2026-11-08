/*
 * ALGORITMO: QUICK SORT (com pivô Mediana-de-Três)
 * APLICAÇÃO: Situação Problema 23 - Ordenação de Catálogo de Produtos de E-commerce
 *
 * JUSTIFICATIVA: O Quick Sort é o algoritmo de ordenação em memória principal mais rápido na
 * prática (O(N log N) médio e baixo uso de memória auxiliar). A escolha de pivô por
 * mediana-de-três reduz a probabilidade de degeneração para O(N^2) em catálogos já ordenados.
 *
 * COMPLEXIDADE:
 * - Caso Médio e Melhor Caso: O(N log N)
 * - Pior Caso: O(N^2) (probabilidade reduzida pela mediana-de-três)
 * - Espaço Auxiliar: O(log N) no caso médio e O(N) no pior caso na pilha de recursão.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 150

// Critérios de ordenação: 1 = Preço (crescente), 2 = Nome (A-Z), 3 = Popularidade (decrescente)
#define CRITERIO_PRECO 1
#define CRITERIO_NOME 2
#define CRITERIO_POPULARIDADE 3

typedef struct {
    int id;
    char nome[50];
    float preco;
    int popularidade;
} Produto;

void trocar(Produto *a, Produto *b) {
    Produto temp = *a;
    *a = *b;
    *b = temp;
}

int compararProdutos(const Produto *a, const Produto *b, int criterio, long *comparacoes) {
    (*comparacoes)++;
    if (criterio == CRITERIO_PRECO) {
        if (a->preco < b->preco) return -1;
        if (a->preco > b->preco) return 1;
        return a->id - b->id;
    } else if (criterio == CRITERIO_NOME) {
        int cmp = strcmp(a->nome, b->nome);
        return (cmp != 0) ? cmp : (a->id - b->id);
    } else {
        // Maior popularidade primeiro
        if (a->popularidade > b->popularidade) return -1;
        if (a->popularidade < b->popularidade) return 1;
        return a->id - b->id;
    }
}

// Escolhe a mediana entre low, mid e high e coloca o pivô em high
void escolherPivoMedianaDeTres(Produto v[], int low, int high, int criterio, long *comparacoes) {
    int mid = low + (high - low) / 2;
    if (compararProdutos(&v[mid], &v[low], criterio, comparacoes) < 0)
        trocar(&v[low], &v[mid]);
    if (compararProdutos(&v[high], &v[low], criterio, comparacoes) < 0)
        trocar(&v[low], &v[high]);
    if (compararProdutos(&v[mid], &v[high], criterio, comparacoes) < 0)
        trocar(&v[mid], &v[high]);
}

int particionar(Produto v[], int low, int high, int criterio, long *comparacoes, long *trocas) {
    escolherPivoMedianaDeTres(v, low, high, criterio, comparacoes);
    Produto pivo = v[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compararProdutos(&v[j], &pivo, criterio, comparacoes) <= 0) {
            i++;
            trocar(&v[i], &v[j]);
            (*trocas)++;
        }
    }
    trocar(&v[i + 1], &v[high]);
    (*trocas)++;
    return i + 1;
}

void quickSort(Produto v[], int low, int high, int criterio, long *comparacoes, long *trocas) {
    if (low < high) {
        int pi = particionar(v, low, high, criterio, comparacoes, trocas);
        quickSort(v, low, pi - 1, criterio, comparacoes, trocas);
        quickSort(v, pi + 1, high, criterio, comparacoes, trocas);
    }
}

// Merge Sort auxiliar para comparação de desempenho conforme solicitado no enunciado
void intercalarMerge(Produto v[], Produto aux[], int inicio, int meio, int fim, int criterio, long *comparacoes) {
    for (int k = inicio; k <= fim; k++) aux[k] = v[k];
    int i = inicio, j = meio + 1, dest = inicio;
    while (i <= meio && j <= fim) {
        if (compararProdutos(&aux[i], &aux[j], criterio, comparacoes) <= 0)
            v[dest++] = aux[i++];
        else
            v[dest++] = aux[j++];
    }
    while (i <= meio) v[dest++] = aux[i++];
    while (j <= fim) v[dest++] = aux[j++];
}

void mergeSortRec(Produto v[], Produto aux[], int inicio, int fim, int criterio, long *comparacoes) {
    if (inicio >= fim) return;
    int meio = inicio + (fim - inicio) / 2;
    mergeSortRec(v, aux, inicio, meio, criterio, comparacoes);
    mergeSortRec(v, aux, meio + 1, fim, criterio, comparacoes);
    intercalarMerge(v, aux, inicio, meio, fim, criterio, comparacoes);
}

void gerarCatalogo100Produtos(Produto catalogo[], int *total) {
    const char *categorias[10] = {
        "Notebook", "Monitor", "Teclado", "Mouse", "Headset",
        "Smartphone", "SSD NVMe", "Placa de Video", "Roteador", "Webcam"
    };
    *total = 100;
    for (int i = 0; i < 100; i++) {
        catalogo[i].id = i + 1;
        snprintf(catalogo[i].nome, 50, "%s Modelo %03d",
                 categorias[(i * 7 + 3) % 10], ((i * 37) % 100) + 1);
        catalogo[i].preco = 49.90f + ((i * 173 + 29) % 4500) + (i % 10) * 0.90f;
        catalogo[i].popularidade = 100 + ((i * 251 + 43) % 900);
    }
}

void exibirAmostraCatalogo(Produto v[], int total, const char *titulo) {
    printf("\n--- %s (Exibindo 10 primeiros e 5 ultimos de %d produtos) ---\n", titulo, total);
    for (int i = 0; i < total && i < 10; i++) {
        printf("%3d. [ID %3d] %-24s | R$ %8.2f | Popularidade: %d\n",
               i + 1, v[i].id, v[i].nome, v[i].preco, v[i].popularidade);
    }
    if (total > 15) {
        printf("  ...\n");
        for (int i = total - 5; i < total; i++) {
            printf("%3d. [ID %3d] %-24s | R$ %8.2f | Popularidade: %d\n",
                   i + 1, v[i].id, v[i].nome, v[i].preco, v[i].popularidade);
        }
    }
}

void executarSimulacao100Produtos(Produto catalogo[], int *total) {
    gerarCatalogo100Produtos(catalogo, total);
    Produto copiaQuick[MAX], copiaMerge[MAX], auxMerge[MAX];

    printf("\n=========================================================================\n");
    printf("   SIMULACAO E-COMMERCE: 100 PRODUTOS, MULTIPLOS CRITERIOS E BENCHMARK   \n");
    printf("=========================================================================\n");

    // 1. Ordenar por Preço (Quick Sort vs Merge Sort)
    for (int i = 0; i < *total; i++) {
        copiaQuick[i] = catalogo[i];
        copiaMerge[i] = catalogo[i];
    }
    long compQuick = 0, trocasQuick = 0, compMerge = 0;
    clock_t t0 = clock();
    quickSort(copiaQuick, 0, *total - 1, CRITERIO_PRECO, &compQuick, &trocasQuick);
    clock_t t1 = clock();

    clock_t t2 = clock();
    mergeSortRec(copiaMerge, auxMerge, 0, *total - 1, CRITERIO_PRECO, &compMerge);
    clock_t t3 = clock();

    exibirAmostraCatalogo(copiaQuick, *total, "ORDENADO POR PRECO CRESCENTE (QUICK SORT MEDIANA-DE-TRES)");
    printf("\n[COMPARACAO QUICK SORT vs MERGE SORT (100 produtos por preco)]\n");
    printf("  -> Quick Sort (Mediana-de-3): %ld comparacoes, %ld trocas (%.3f ms)\n",
           compQuick, trocasQuick, ((double)(t1 - t0) * 1000.0) / CLOCKS_PER_SEC);
    printf("  -> Merge Sort               : %ld comparacoes (%.3f ms)\n",
           compMerge, ((double)(t3 - t2) * 1000.0) / CLOCKS_PER_SEC);

    // 2. Ordenar por Nome
    for (int i = 0; i < *total; i++) copiaQuick[i] = catalogo[i];
    compQuick = 0; trocasQuick = 0;
    quickSort(copiaQuick, 0, *total - 1, CRITERIO_NOME, &compQuick, &trocasQuick);
    exibirAmostraCatalogo(copiaQuick, *total, "ORDENADO POR NOME ALFABETICO (A-Z)");

    // 3. Ordenar por Popularidade
    for (int i = 0; i < *total; i++) copiaQuick[i] = catalogo[i];
    compQuick = 0; trocasQuick = 0;
    quickSort(copiaQuick, 0, *total - 1, CRITERIO_POPULARIDADE, &compQuick, &trocasQuick);
    exibirAmostraCatalogo(copiaQuick, *total, "ORDENADO POR POPULARIDADE DECRESCENTE");
}

int main() {
    Produto catalogo[MAX];
    int total = 0, op, criterio;

    do {
        printf("\n=== CATALOGO E-COMMERCE - QUICK SORT (SITUACAO 23) ===\n");
        printf("1. Cadastrar Produto Manualmente\n");
        printf("2. Ordenar Catalogo Atual (Escolher Criterio)\n");
        printf("3. Executar Simulacao com 100 Produtos e Comparar com Merge Sort\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        if (op == 1 && total < MAX) {
            catalogo[total].id = total + 1;
            printf("Nome do Produto: ");
            fgets(catalogo[total].nome, 50, stdin);
            catalogo[total].nome[strcspn(catalogo[total].nome, "\n")] = '\0';
            printf("Preco (ex: 120.50): ");
            if (scanf("%f", &catalogo[total].preco) != 1 || catalogo[total].preco < 0.0f) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Preco invalido!\n");
                continue;
            }
            printf("Popularidade (0 a 1000): ");
            if (scanf("%d", &catalogo[total].popularidade) != 1 || catalogo[total].popularidade < 0) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Popularidade invalida!\n");
                continue;
            }
            getchar();
            total++;
        } else if (op == 2 && total > 0) {
            printf("Criterio (1 - Preco; 2 - Nome; 3 - Popularidade): ");
            if (scanf("%d", &criterio) != 1 || criterio < 1 || criterio > 3) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("[ERRO] Criterio invalido! Escolha 1, 2 ou 3.\n");
                continue;
            }
            getchar();
            long comp = 0, trocas = 0;
            quickSort(catalogo, 0, total - 1, criterio, &comp, &trocas);
            exibirAmostraCatalogo(catalogo, total, "CATALOGO ORDENADO");
            printf("Comparacoes: %ld | Trocas: %ld\n", comp, trocas);
        } else if (op == 3) {
            executarSimulacao100Produtos(catalogo, &total);
        }
    } while (op != 0);

    return 0;
}
