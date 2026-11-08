/*
 * ESTRUTURA DE DADOS: TABELA HASH COM ENCADEAMENTO EXTERNO
 * APLICAÇÃO: Situação Problema 13 - Cadastro de Usuários com Login Rápido
 *
 * JUSTIFICATIVA: A Tabela Hash possibilita acesso, inserção e remoção em tempo médio
 * constante O(1) a partir da chave de login (e-mail), armazenando o hash da senha e
 * resolvendo colisões por listas encadeadas nos buckets.
 *
 * COMPLEXIDADE:
 * - Tempo Médio (Inserção, Autenticação e Remoção por chave): O(1 + N/M) = O(1)
 * - Pior Caso (Colisão Total): O(N)
 * - Espaço: O(M + N), onde M é o tamanho da tabela e N o total de usuários.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 11

typedef struct Usuario {
    char email[50];
    char usuario[50];
    unsigned long senhaHash;
    struct Usuario *proximo;
} Usuario;

typedef struct {
    Usuario *tabela[TAM_HASH];
} TabelaHash;

void inicializar(TabelaHash *th) {
    for (int i = 0; i < TAM_HASH; i++) th->tabela[i] = NULL;
}

void limparTabela(TabelaHash *th) {
    for (int i = 0; i < TAM_HASH; i++) {
        Usuario *atual = th->tabela[i];
        while (atual != NULL) {
            Usuario *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
        th->tabela[i] = NULL;
    }
}

// Função de espalhamento (polinomial modular) a partir da chave (e-mail)
int funcaoHash(const char *chave) {
    unsigned long hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash = (hash * 31 + (unsigned char)chave[i]) % TAM_HASH;
    }
    return (int)hash;
}

// Gera hash nao-criptografico didatico (DJB2) para armazenar a senha em formato de resumo numerico
unsigned long gerarHashSenha(const char *senha) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*senha++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void cadastrarUsuario(TabelaHash *th, const char *email, const char *usuario, const char *senha) {
    int idx = funcaoHash(email);

    // Verifica no bucket correspondente se o e-mail já está cadastrado (O(1) médio)
    int colisoesNoBucket = 0;
    Usuario *aux = th->tabela[idx];
    while (aux != NULL) {
        if (strcmp(aux->email, email) == 0) {
            printf("[ERRO] O e-mail '%s' ja esta cadastrado no bucket %d!\n", email, idx);
            return;
        }
        colisoesNoBucket++;
        aux = aux->proximo;
    }

    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] Falha ao alocar memoria para usuario.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->email, email, 49);
    novo->email[49] = '\0';
    strncpy(novo->usuario, usuario, 49);
    novo->usuario[49] = '\0';
    novo->senhaHash = gerarHashSenha(senha);
    novo->proximo = th->tabela[idx];
    th->tabela[idx] = novo;

    printf("[CADASTRO] %s (@%s) -> Bucket %2d | HashSenha: %lu %s\n",
           email, usuario, idx, novo->senhaHash,
           colisoesNoBucket > 0 ? "[COLISAO TRATADA POR ENCADEAMENTO]" : "");
}

// Autentica em O(1) médio calculando o índice hash diretamente pela chave (e-mail)
int autenticar(TabelaHash *th, const char *email, const char *senha) {
    int idx = funcaoHash(email);
    unsigned long hashInformado = gerarHashSenha(senha);

    Usuario *aux = th->tabela[idx];
    while (aux != NULL) {
        if (strcmp(aux->email, email) == 0) {
            return (aux->senhaHash == hashInformado) ? 1 : 0;
        }
        aux = aux->proximo;
    }
    return 0;
}

// Remove conta em O(1) médio acessando diretamente o bucket da chave (e-mail)
void removerUsuario(TabelaHash *th, const char *email) {
    int idx = funcaoHash(email);
    Usuario *atual = th->tabela[idx];
    Usuario *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            if (anterior == NULL) {
                th->tabela[idx] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("[REMOCAO] Conta '%s' removida com sucesso do bucket %d!\n", email, idx);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("[ERRO] Conta '%s' nao encontrada no bucket %d.\n", email, idx);
}

void listarUsuarios(TabelaHash *th) {
    int total = 0, bucketsComColisao = 0;
    printf("\n=================== ESTRUTURA DA TABELA HASH (%d BUCKETS) ===================\n", TAM_HASH);
    for (int i = 0; i < TAM_HASH; i++) {
        Usuario *aux = th->tabela[i];
        printf("[Bucket %2d] -> ", i);
        int contBucket = 0;
        while (aux != NULL) {
            printf("@%s (%s, hash=%lu) -> ", aux->usuario, aux->email, aux->senhaHash);
            total++;
            contBucket++;
            aux = aux->proximo;
        }
        if (contBucket > 1) bucketsComColisao++;
        printf("NULL\n");
    }
    printf("Total de usuarios ativos: %d | Buckets com colisao encadeada: %d\n",
           total, bucketsComColisao);
    printf("=============================================================================\n");
}

// Simulação com pelo menos 20 usuários, testes de colisão, autenticação e remoção
void executarSimulacao(TabelaHash *th) {
    limparTabela(th);
    printf("\n======================================================================\n");
    printf("   SIMULACAO: 20 USUARIOS, COLISOES E AUTENTICACAO RAPIDA (O(1))      \n");
    printf("======================================================================\n");

    const char *emails[20] = {
        "ana.lima@empresa.com", "bruno.costa@empresa.com", "carla.alves@empresa.com",
        "daniel.rocha@empresa.com", "elisa.sousa@empresa.com", "fabio.santos@empresa.com",
        "gabriela.nunes@empresa.com", "heitor.melo@empresa.com", "isabela.dias@empresa.com",
        "joao.silva@empresa.com", "karen.ribeiro@empresa.com", "lucas.martins@empresa.com",
        "marina.barros@empresa.com", "nicolas.freitas@empresa.com", "olivia.gomes@empresa.com",
        "paulo.araujo@empresa.com", "rafaela.torres@empresa.com", "samuel.pinto@empresa.com",
        "tais.carvalho@empresa.com", "victor.braga@empresa.com"
    };
    const char *users[20] = {
        "analima", "brunoc", "carlaa", "danielr", "elisas",
        "fabios", "gabrielan", "heitorm", "isabelad", "joaos",
        "karenr", "lucasm", "marinab", "nicolasf", "oliviag",
        "pauloa", "rafaelat", "samuelp", "taisc", "victorb"
    };
    const char *senhas[20] = {
        "Senha#01", "Senha#02", "Senha#03", "Senha#04", "Senha#05",
        "Senha#06", "Senha#07", "Senha#08", "Senha#09", "Senha#10",
        "Senha#11", "Senha#12", "Senha#13", "Senha#14", "Senha#15",
        "Senha#16", "Senha#17", "Senha#18", "Senha#19", "Senha#20"
    };

    for (int i = 0; i < 20; i++) {
        cadastrarUsuario(th, emails[i], users[i], senhas[i]);
    }

    listarUsuarios(th);

    printf("\n--- Testes de Autenticacao (Login O(1)) ---\n");
    printf("1. Login valido (ana.lima@empresa.com / Senha#01): %s\n",
           autenticar(th, "ana.lima@empresa.com", "Senha#01") ? "SUCESSO" : "FALHA");
    printf("2. Login em bucket com colisao (victor.braga@empresa.com / Senha#20): %s\n",
           autenticar(th, "victor.braga@empresa.com", "Senha#20") ? "SUCESSO" : "FALHA");
    printf("3. Senha incorreta (ana.lima@empresa.com / errada123): %s\n",
           autenticar(th, "ana.lima@empresa.com", "errada123") ? "SUCESSO" : "FALHA (Esperado)");
    printf("4. Usuario inexistente (nao.existe@empresa.com / 123): %s\n",
           autenticar(th, "nao.existe@empresa.com", "123") ? "SUCESSO" : "FALHA (Esperado)");

    printf("\n--- Teste de Remocao de Conta ---\n");
    removerUsuario(th, "carla.alves@empresa.com");
    printf("5. Login apos remocao (carla.alves@empresa.com): %s\n",
           autenticar(th, "carla.alves@empresa.com", "Senha#03") ? "SUCESSO" : "FALHA (Conta removida)");
}

int main() {
    TabelaHash th;
    inicializar(&th);
    int op;
    char email[50], usuario[50], senha[50];

    do {
        printf("\n=== AUTENTICACAO DE USUARIOS - TABELA HASH (SITUACAO 13) ===\n");
        printf("1. Cadastrar Usuario\n");
        printf("2. Realizar Login (por E-mail)\n");
        printf("3. Remover Conta de Usuario\n");
        printf("4. Listar Estrutura da Tabela Hash\n");
        printf("5. Executar Simulacao com 20 Usuarios e Colisoes\n");
        printf("0. Sair\nEscolha: ");
        if (scanf("%d", &op) != 1) break;
        getchar();

        switch (op) {
            case 1:
                printf("Digite o e-mail: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = '\0';
                printf("Digite o nome de usuario (username): ");
                fgets(usuario, 50, stdin);
                usuario[strcspn(usuario, "\n")] = '\0';
                printf("Digite a senha: ");
                fgets(senha, 50, stdin);
                senha[strcspn(senha, "\n")] = '\0';
                cadastrarUsuario(&th, email, usuario, senha);
                break;

            case 2:
                printf("Digite o e-mail: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = '\0';
                printf("Digite a senha: ");
                fgets(senha, 50, stdin);
                senha[strcspn(senha, "\n")] = '\0';

                if (autenticar(&th, email, senha)) {
                    printf("\n[LOGIN BEM-SUCEDIDO] Bem-vindo(a)!\n");
                } else {
                    printf("\n[FALHA NO LOGIN] Credenciais incorretas.\n");
                }
                break;

            case 3:
                printf("Digite o e-mail a ser removido: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = '\0';
                removerUsuario(&th, email);
                break;

            case 4:
                listarUsuarios(&th);
                break;

            case 5:
                executarSimulacao(&th);
                break;
        }
    } while (op != 0);

    limparTabela(&th);
    return 0;
}
