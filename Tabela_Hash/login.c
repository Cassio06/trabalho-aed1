/*
 * ESTRUTURA DE DADOS: TABELA HASH COM ENCADEAMENTO EXTERNO
 * APLICAÇÃO: Cadastro de Usuários e Autenticação de Login Rápido
 * 
 * JUSTIFICATIVA: A Tabela Hash possibilita acesso em tempo médio constante O(1)
 * a partir de uma chave única (e-mail/login), tornando a verificação de credenciais instantânea.
 * Tratamento de colisões feito por lista encadeada.
 * 
 * COMPLEXIDADE:
 * - Tempo Médio de Autenticação/Inserção: O(1)
 * - Pior Caso (Colisão Total): O(N)
 * - Espaço: O(M + N), onde M é o tamanho da tabela e N o total de usuários.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

typedef struct Usuario {
    char email[50];
    char usuario[50];
    char senha[50];
    struct Usuario *proximo;
} Usuario;

typedef struct {
    Usuario *tabela[TAM_HASH];
} TabelaHash;

void inicializar(TabelaHash *th) {
    for (int i = 0; i < TAM_HASH; i++) th->tabela[i] = NULL;
}

int funcaoHash(char *str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) hash += str[i];
    return hash % TAM_HASH;
}

void cadastrarUsuario(TabelaHash *th, char *email, char *usuario, char *senha) {
    int idx = funcaoHash(email);
    
    // Verifica se e-mail ou usuario ja existem
    Usuario *aux = th->tabela[idx];
    while (aux != NULL) {
        if (strcmp(aux->email, email) == 0 || strcmp(aux->usuario, usuario) == 0) {
            printf("\n[ERRO] O e-mail ou nome de usuario ja esta cadastrado!\n");
            return;
        }
        aux = aux->proximo;
    }

    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    strcpy(novo->email, email);
    strcpy(novo->usuario, usuario);
    strcpy(novo->senha, senha);
    novo->proximo = th->tabela[idx];
    th->tabela[idx] = novo;
    
    printf("\nUsuario '%s' (@%s) cadastrado com sucesso!\n", email, usuario);
}

// Permite login passando o E-mail OU o Nome de Usuario no primeiro parametro
int autenticar(TabelaHash *th, char *login, char *senha) {
    // Busca em todos os indices para garantir suporte a login por e-mail ou username
    for (int i = 0; i < TAM_HASH; i++) {
        Usuario *aux = th->tabela[i];
        while (aux != NULL) {
            if ((strcmp(aux->email, login) == 0 || strcmp(aux->usuario, login) == 0) && strcmp(aux->senha, senha) == 0) {
                return 1; // Login bem-sucedido
            }
            aux = aux->proximo;
        }
    }
    return 0; // Falha na autenticacao
}

void removerUsuario(TabelaHash *th, char *chave) {
    for (int i = 0; i < TAM_HASH; i++) {
        Usuario *atual = th->tabela[i];
        Usuario *anterior = NULL;

        while (atual != NULL) {
            if (strcmp(atual->email, chave) == 0 || strcmp(atual->usuario, chave) == 0) {
                if (anterior == NULL) {
                    th->tabela[i] = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                free(atual);
                printf("\nConta '%s' removida com sucesso!\n", chave);
                return;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
    printf("\n[ERRO] Usuario ou e-mail '%s' nao encontrado.\n", chave);
}

// Função para listar a estrutura visual da Tabela Hash
void listarUsuarios(TabelaHash *th) {
    int total = 0;
    printf("\n=================== TELA DE USUARIOS (TABELA HASH) ===================\n");
    for (int i = 0; i < TAM_HASH; i++) {
        Usuario *aux = th->tabela[i];
        if (aux != NULL) {
            printf("[ Indice Hash %d ] -> ", i);
            while (aux != NULL) {
                printf("User: @%s (Email: %s) | ", aux->usuario, aux->email);
                total++;
                aux = aux->proximo;
            }
            printf("NULL\n");
        }
    }
    if (total == 0) {
        printf("Nenhum usuario cadastrado no sistema.\n");
    } else {
        printf("Total de usuarios ativos: %d\n", total);
    }
    printf("======================================================================\n");
}

int main() {
    TabelaHash th; inicializar(&th);
    int op; char email[50], usuario[50], senha[50], login[50];
    do {
        printf("\n=== AUTENTICACAO DE USUARIOS (TABELA HASH) ===\n1. Cadastrar Usuario\n2. Realizar Login\n3. Remover Conta de Usuario\n4. Listar Todos os Usuarios\n0. Sair\nEscolha: ");
        scanf("%d", &op); getchar();
        switch(op) {
            case 1:
                printf("Digite o e-mail: ");
                fgets(email, 50, stdin); email[strcspn(email, "\n")] = '\0';
                printf("Digite o nome de usuario (username): ");
                fgets(usuario, 50, stdin); usuario[strcspn(usuario, "\n")] = '\0';
                printf("Digite a senha: ");
                fgets(senha, 50, stdin); senha[strcspn(senha, "\n")] = '\0';
                cadastrarUsuario(&th, email, usuario, senha);
                break;

            case 2:
                printf("Digite o e-mail OU o nome de usuario: ");
                fgets(login, 50, stdin); login[strcspn(login, "\n")] = '\0';
                printf("Digite a senha: ");
                fgets(senha, 50, stdin); senha[strcspn(senha, "\n")] = '\0';
                
                if (autenticar(&th, login, senha)) {
                    printf("\n[LOGIN BEM-SUCEDIDO] Bem-vindo(a)!\n");
                } else {
                    printf("\n[FALHA NO LOGIN] Credenciais incorretas.\n");
                }
                break;

            case 3:
                printf("Digite o e-mail ou usuario a ser removido: ");
                fgets(login, 50, stdin); login[strcspn(login, "\n")] = '\0';
                removerUsuario(&th, login);
                break;

            case 4:
                listarUsuarios(&th);
                break;
        }
    } while (op != 0);
    return 0;
}
