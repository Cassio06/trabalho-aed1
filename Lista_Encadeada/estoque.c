/*
 * ESTRUTURA DE DADOS: LISTA ENCADEADA SIMPLES
 * APLICAÇÃO: Situação Problema 6 - Controle de Estoque de uma Pequena Loja
 *
 * JUSTIFICATIVA: Suporta variação dinâmica de produtos em estoque (cadastro de novos itens,
 * atualização de quantidades e remoção imediata de itens esgotados/descontinuados)
 * sem limitação fixa de tamanho e sem realocações caras de memória.
 *
 * COMPLEXIDADE:
 * - Cadastrar no início: O(1)
 * - Atualizar quantidade / Buscar por código ou nome / Remover produto / Listar: O(N)
 * - Espaço: O(N) proporcional ao número de produtos ativos no estoque.
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

void inicializar(Estoque *e) {
    e->inicio = NULL;
}

void cadastrarDados(Estoque *e, int codigo, const char *nome, int quantidade, float preco) {
    Produto *aux = e->inicio;
    while (aux != NULL) {
        if (aux->codigo == codigo) {
            aux->quantidade += quantidade;
            aux->preco = preco;
            printf("[ESTOQUE] Codigo %d (%s) ja existente; quantidade somada para %d.\n",
                   codigo, aux->nome, aux->quantidade);
            return;
        }
        aux = aux->proximo;
    }

    Produto *novo = (Produto*) malloc(sizeof(Produto));
    novo->codigo = codigo;
    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';
    novo->quantidade = quantidade;
    novo->preco = preco;
    novo->proximo = e->inicio;
    e->inicio = novo;
    printf("[+] Produto cadastrado: Cod %d | %s | Qtd: %d | R$ %.2f\n",
           codigo, nome, quantidade, preco);
}

void cadastrarConsole(Estoque *e) {
    int codigo, quantidade;
    char nome[50];
    float preco;

    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();

    printf("Nome: ");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &quantidade);
    getchar();

    printf("Preco unitario (ex: 12.40): ");
    scanf("%f", &preco);
    getchar();

    cadastrarDados(e, codigo, nome, quantidade, preco);
}

void removerProduto(Estoque *e, int cod) {
    Produto *atual = e->inicio, *anterior = NULL;
    while (atual != NULL && atual->codigo != cod) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("[ERRO] Produto de codigo %d nao encontrado para remocao.\n", cod);
        return;
    }
    if (anterior == NULL) e->inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    printf("[-] Produto removido da lista ativa: Cod %d (%s)\n", atual->codigo, atual->nome);
    free(atual);
}

void atualizarQtd(Estoque *e, int cod, int novaQtd) {
    Produto *aux = e->inicio;
    while (aux != NULL) {
        if (aux->codigo == cod) {
            aux->quantidade = novaQtd;
            printf("[ATUALIZACAO] Cod %d (%s) -> Nova quantidade: %d\n",
                   aux->codigo, aux->nome, novaQtd);
            if (aux->quantidade <= 0) {
                printf("[ESGOTADO] Produto '%s' zerado; removendo da lista ativa...\n", aux->nome);
                removerProduto(e, cod);
            }
            return;
        }
        aux = aux->proximo;
    }
    printf("Produto de codigo %d nao encontrado!\n", cod);
}

void buscarPorCodigo(Estoque *e, int cod) {
    Produto *aux = e->inicio;
    while (aux != NULL) {
        if (aux->codigo == cod) {
            printf("[BUSCA CODIGO] Encontrado: Cod: %d | Nome: %s | Qtd: %d | R$ %.2f\n",
                   aux->codigo, aux->nome, aux->quantidade, aux->preco);
            return;
        }
        aux = aux->proximo;
    }
    printf("[BUSCA CODIGO] Produto de codigo %d nao encontrado.\n", cod);
}

void buscarPorNome(Estoque *e, const char *nome) {
    Produto *aux = e->inicio;
    int encontrados = 0;
    while (aux != NULL) {
        if (strstr(aux->nome, nome) != NULL) {
            printf("[BUSCA NOME] Encontrado: Cod: %d | Nome: %s | Qtd: %d | R$ %.2f\n",
                   aux->codigo, aux->nome, aux->quantidade, aux->preco);
            encontrados++;
        }
        aux = aux->proximo;
    }
    if (!encontrados) {
        printf("[BUSCA NOME] Nenhum produto contendo '%s' foi encontrado.\n", nome);
    }
}

void listarEstoqueBaixo(Estoque *e, int min) {
    Produto *aux = e->inicio;
    int cont = 0;
    printf("\n--- PRODUTOS ABAIXO DO ESTOQUE MINIMO (< %d unidades) ---\n", min);
    while (aux != NULL) {
        if (aux->quantidade < min) {
            printf("Cod: %d | Nome: %-22s | Qtd: %3d | R$ %.2f\n",
                   aux->codigo, aux->nome, aux->quantidade, aux->preco);
            cont++;
        }
        aux = aux->proximo;
    }
    if (cont == 0) printf("Nenhum produto abaixo do estoque minimo.\n");
}

void listarTudo(Estoque *e) {
    Produto *aux = e->inicio;
    if (aux == NULL) {
        printf("\nEstoque vazio.\n");
        return;
    }
    printf("\n--- ESTOQUE ATIVO COMPLETO ---\n");
    while (aux != NULL) {
        printf("Cod: %d | Nome: %-22s | Qtd: %3d | R$ %.2f\n",
               aux->codigo, aux->nome, aux->quantidade, aux->preco);
        aux = aux->proximo;
    }
}

void limparEstoque(Estoque *e) {
    Produto *atual = e->inicio;
    while (atual != NULL) {
        Produto *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    e->inicio = NULL;
}

// Simulação com entrada e saída de mercadorias ao longo de uma semana (7 dias)
void executarSimulacaoSemana(Estoque *e) {
    limparEstoque(e);
    printf("\n=================================================================\n");
    printf("   SIMULACAO SEMANAL: LOJA DE MATERIAIS DE CONSTRUCAO (7 DIAS)   \n");
    printf("=================================================================\n");

    printf("\n[Dia 1 - Segunda] Carga inicial de produtos:\n");
    cadastrarDados(e, 101, "Cimento CP-II 50kg", 40, 38.90f);
    cadastrarDados(e, 102, "Argamassa AC-III 20kg", 25, 29.50f);
    cadastrarDados(e, 103, "Tinta Acrilica 18L", 12, 219.90f);
    cadastrarDados(e, 104, "Tijolo Baiano Milheiro", 8, 850.00f);
    cadastrarDados(e, 105, "Caixa D'Agua 1000L", 5, 340.00f);
    cadastrarDados(e, 106, "Lampada LED 12W", 60, 9.90f);

    printf("\n[Dia 2 - Terca] Saida de cimento e argamassa para obra residencial:\n");
    atualizarQtd(e, 101, 18);
    atualizarQtd(e, 102, 7);

    printf("\n[Dia 3 - Quarta] Cadastro de novos materiais eletricos e hidraulicos:\n");
    cadastrarDados(e, 107, "Tubo PVC 100mm 6m", 30, 54.00f);
    cadastrarDados(e, 108, "Disjuntor Bipolar 40A", 15, 42.00f);

    printf("\n[Dia 4 - Quinta] Venda total do estoque de Caixas D'Agua (produto esgotado):\n");
    atualizarQtd(e, 105, 0);

    printf("\n[Dia 5 - Sexta] Buscas no sistema por codigo e por nome:\n");
    buscarPorCodigo(e, 103);
    buscarPorNome(e, "Tubo PVC");

    printf("\n[Dia 6 - Sabado] Vendas de fim de semana e reposicao de cimento:\n");
    atualizarQtd(e, 103, 4);
    atualizarQtd(e, 104, 3);
    atualizarQtd(e, 108, 6);
    atualizarQtd(e, 101, 50);

    printf("\n[Dia 7 - Domingo] Balanco final da semana e alerta de estoque minimo (< 10):\n");
    listarTudo(e);
    listarEstoqueBaixo(e, 10);
}

int main() {
    Estoque e;
    inicializar(&e);
    int op, cod, qtd, min;
    char termo[50];

    do {
        printf("\n=== CONTROLE DE ESTOQUE (SITUACAO 6) ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Atualizar Quantidade\n");
        printf("3. Remover Produto por Codigo\n");
        printf("4. Buscar por Codigo\n");
        printf("5. Buscar por Nome\n");
        printf("6. Listar Produtos Abaixo do Estoque Minimo\n");
        printf("7. Listar Estoque Completo\n");
        printf("8. Simular Movimentacao de uma Semana (7 Dias)\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1:
                cadastrarConsole(&e);
                break;
            case 2:
                printf("Codigo: ");
                scanf("%d", &cod);
                printf("Nova Qtd: ");
                scanf("%d", &qtd);
                getchar();
                atualizarQtd(&e, cod, qtd);
                break;
            case 3:
                printf("Codigo a remover: ");
                scanf("%d", &cod);
                getchar();
                removerProduto(&e, cod);
                break;
            case 4:
                printf("Codigo a buscar: ");
                scanf("%d", &cod);
                getchar();
                buscarPorCodigo(&e, cod);
                break;
            case 5:
                printf("Nome a buscar: ");
                fgets(termo, 50, stdin);
                termo[strcspn(termo, "\n")] = '\0';
                buscarPorNome(&e, termo);
                break;
            case 6:
                printf("Estoque minimo: ");
                scanf("%d", &min);
                getchar();
                listarEstoqueBaixo(&e, min);
                break;
            case 7:
                listarTudo(&e);
                break;
            case 8:
                executarSimulacaoSemana(&e);
                break;
        }
    } while (op != 0);

    limparEstoque(&e);
    return 0;
}
