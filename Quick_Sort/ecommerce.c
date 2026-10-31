/*
 * ALGORITMO: QUICK SORT (Divisão e Conquista)
 * APLICAÇÃO: Ordenação de Catálogo de Produtos de E-commerce por Preço
 * 
 * JUSTIFICATIVA: O Quick Sort é um dos algoritmos de ordenação em memória mais rápidos na prática.
 * Utiliza o particionamento ao redor de um pivô para ordenar o catálogo de produtos de forma eficiente.
 * 
 * COMPLEXIDADE:
 * - Caso Médio: O(N log N)
 * - Pior Caso: O(N^2)
 * - Espaço Auxiliar: O(log N) na pilha de recursão.
 */

#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[50];
    float preco;
} Produto;

int particionar(Produto v[], int low, int high) {
    float pivo = v[high].preco;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (v[j].preco <= pivo) {
            i++;
            Produto temp = v[i]; v[i] = v[j]; v[j] = temp;
        }
    }
    Produto temp = v[i + 1]; v[i + 1] = v[high]; v[high] = temp;
    return i + 1;
}

void quickSort(Produto v[], int low, int high) {
    if (low < high) {
        int pi = particionar(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

int main() {
    Produto catalogo[MAX];
    int total = 0, op;
    do {
        printf("\n=== CATALOGO E-COMMERCE ===\n1. Cadastrar Produto\n2. Ordenar Catalogo por Preco\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        if (op == 1 && total < MAX) {
            printf("Nome do Produto: "); fgets(catalogo[total].nome, 50, stdin); catalogo[total].nome[strcspn(catalogo[total].nome, "\n")] = '\0';
            printf("Preco (ex: 12.40): "); scanf("%f", &catalogo[total].preco); getchar();
            total++;
        } else if (op == 2 && total > 0) {
            quickSort(catalogo, 0, total - 1);
            printf("\n--- CATALOGO ORDENADO POR PRECO ---\n");
            for (int i = 0; i < total; i++)
                printf("%s - R$ %.2f\n", catalogo[i].nome, catalogo[i].preco);
        }
    } while (op != 0);
    return 0;
}
