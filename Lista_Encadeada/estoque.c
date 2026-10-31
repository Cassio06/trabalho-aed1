/*
 * ESTRUTURA DE DADOS: LISTA ENCADEADA SIMPLES
 * APLICAÇÃO: Controle de Estoque de uma Loja
 * 
 * JUSTIFICATIVA: Suporta variação dinâmica de produtos (cadastro, alteração e remoção)
 * sem limitação fixa de tamanho e sem necessidade de realocação contínua de memória.
 * Suporta leitura com decimais (ex: 12.40).
 * 
 * COMPLEXIDADE:
 * - Cadastrar / Atualizar / Listar: O(N)
 * - Espaço: O(N)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Produto *proximo;
} Produto;

typedef struct {
    Produto *inicio;
} Estoque;

void inicializar(Estoque *e) { e->inicio = NULL; }

void cadastrar(Estoque *e) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    
    printf("Codigo: "); 
    scanf("%d", &novo->codigo); 
    getchar();

    printf("Nome: "); 
    fgets(novo->nome, 50, stdin); 
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Quantidade: "); 
    scanf("%d", &novo->quantidade); 
    getchar();

    printf("Preco (utilize ponto para decimais, ex: 12.40): "); 
    scanf("%f", &novo->preco); 
    getchar();

    novo->proximo = e->inicio;
    e->inicio = novo;
    printf("Produto cadastrado com sucesso!\n");
}

void atualizarQtd(Estoque *e, int cod, int novaQtd) {
    Produto *aux = e->inicio;
    while (aux != NULL) {
        if (aux->codigo == cod) { aux->quantidade = novaQtd; printf("Quantidade atualizada!\n"); return; }
        aux = aux->proximo;
    }
    printf("Produto nao encontrado!\n");
}

void listarEstoqueBaixo(Estoque *e, int min) {
    Produto *aux = e->inicio;
    printf("\n--- PRODUTOS COM ESTOQUE < %d ---\n", min);
    while (aux != NULL) {
        if (aux->quantidade < min)
            printf("Cod: %d | Nome: %s | Qtd: %d | R$%.2f\n", aux->codigo, aux->nome, aux->quantidade, aux->preco);
        aux = aux->proximo;
    }
}

void listarTudo(Estoque *e) {
    Produto *aux = e->inicio;
    printf("\n--- ESTOQUE COMPLETO ---\n");
    while (aux != NULL) {
        printf("Cod: %d | Nome: %s | Qtd: %d | R$%.2f\n", aux->codigo, aux->nome, aux->quantidade, aux->preco);
        aux = aux->proximo;
    }
}

int main() {
    Estoque e; inicializar(&e);
    int op, cod, qtd, min;
    do {
        printf("\n=== CONTROLE DE ESTOQUE ===\n1. Cadastrar Produto\n2. Atualizar Quantidade\n3. Alerta Estoque Minimo\n4. Listar Todos\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1: cadastrar(&e); break;
            case 2: printf("Codigo: "); scanf("%d", &cod); printf("Nova Qtd: "); scanf("%d", &qtd); getchar(); atualizarQtd(&e, cod, qtd); break;
            case 3: printf("Limite minimo: "); scanf("%d", &min); getchar(); listarEstoqueBaixo(&e, min); break;
            case 4: listarTudo(&e); break;
        }
    } while (op != 0);
    return 0;
}
