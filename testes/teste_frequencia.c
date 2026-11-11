#define main main_aplicacao
#include "../c(Lukas)/Tabela_Hash/frequencia.c"
#undef main

static int falhas = 0;

static void verificar(int condicao, const char *nome) {
    printf("[%s] %s\n", condicao ? "OK" : "FALHOU", nome);
    if (!condicao) falhas++;
}

static int contagem(TabelaFrequencia *tf, const char *termo) {
    Palavra *p = tf->tabela[funcaoHash(termo)];
    while (p != NULL) {
        if (strcmp(p->termo, termo) == 0) return p->contagem;
        p = p->proximo;
    }
    return 0;
}

int main(void) {
    TabelaFrequencia tf;
    inicializar(&tf);
    processarTexto(&tf, "avó avô avó ÁRVORE árvore");
    verificar(tf.totalPalavrasLidas == 5 && tf.totalDistintas == 3,
              "acentos preservam palavras distintas");
    verificar(contagem(&tf, "avó") == 2 && contagem(&tf, "avô") == 1,
              "contagens exatas de palavras acentuadas");
    verificar(contagem(&tf, "árvore") == 2,
              "maiusculas portuguesas viram minusculas sem perder acentos");
    limparTabela(&tf);
    processarTexto(&tf, "ação—ÁGUA…ação");
    verificar(tf.totalPalavrasLidas == 3 && contagem(&tf, "ação") == 2
              && contagem(&tf, "água") == 1, "pontuacao UTF-8 separa palavras");
    limparTabela(&tf);
    char longa[301];
    memset(longa, 'a', 300);
    longa[300] = '\0';
    processarTexto(&tf, longa);
    verificar(contagem(&tf, longa) == 1, "palavra longa nao e truncada");
    limparTabela(&tf);
    char texto[6001];
    for (int i = 0; i < 3000; i++) { texto[2 * i] = 'a'; texto[2 * i + 1] = ' '; }
    texto[6000] = '\0';
    processarTexto(&tf, texto);
    verificar(tf.totalPalavrasLidas == 3000 && contagem(&tf, "a") == 3000,
              "texto maior que 2048 bytes nao e truncado");
    verificar(funcaoHash("casa") != funcaoHash("mesa"),
              "espalhamento considera prefixos e nao apenas ultima letra");
    limparTabela(&tf);
    processarTexto(&tf, "... ! —");
    verificar(tf.totalDistintas == 0, "texto sem palavras mantem tabela vazia");
    limparTabela(&tf);
    return falhas ? EXIT_FAILURE : EXIT_SUCCESS;
}
