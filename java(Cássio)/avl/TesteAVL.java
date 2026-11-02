package avl;

import apoio.Testes;

public class TesteAVL {

    private static final Testes TESTES = new Testes();

    public static void main(String[] args) {
        executar("árvore vazia", TesteAVL::testarArvoreVazia);
        executar("um elemento", TesteAVL::testarUmElemento);
        executar("ordem normal", TesteAVL::testarOrdemNormal);
        executar("ordem inversa", TesteAVL::testarOrdemInversa);
        executar("chave repetida", TesteAVL::testarChaveRepetida);
        executar("busca e remoção inexistentes", TesteAVL::testarChaveInexistente);
        executar("remoção e balanceamento", TesteAVL::testarRemocao);
        executar("rotação LL: 30, 20, 10", () -> testarRotacao(new int[]{30, 20, 10}));
        executar("rotação RR: 10, 20, 30", () -> testarRotacao(new int[]{10, 20, 30}));
        executar("rotação LR: 30, 10, 20", () -> testarRotacao(new int[]{30, 10, 20}));
        executar("rotação RL: 10, 30, 20", () -> testarRotacao(new int[]{10, 30, 20}));
        executar("remoções sucessivas e reutilização", () -> {
            AVL<Integer, String> arvore = new AVL<>();
            for (int i = 1; i <= 25; i++) arvore.inserir(i, "valor " + i);
            verificar(arvore.altura() <= 7 && arvore.estaBalanceada(), "25 chaves crescentes não devem degenerar.");
            for (int i = 1; i <= 25; i++) {
                verificar(("valor " + i).equals(arvore.remover(i)), "Remoção deve devolver o valor da chave " + i);
                verificar(arvore.buscar(i) == null && arvore.estaBalanceada(), "Remoção deve preservar balanceamento.");
                for (int j = i + 1; j <= 25; j++) verificar(("valor " + j).equals(arvore.buscar(j)), "Preservar chave " + j);
            }
            verificar(arvore.altura() == 0, "Remover tudo deve zerar a altura.");
            arvore.inserir(50, "novo");
            verificar("novo".equals(arvore.buscar(50)), "AVL vazia deve ser reutilizável.");
        });
        executar("Top-K com empate e atualização de pontuação", () -> {
            AVL<String, Jogador> ranking = new AVL<>();
            Jogador ana = new Jogador("Ana", 100);
            Jogador bruno = new Jogador("Bruno", 100);
            ranking.inserir(RankingJogadores.chave(ana), ana);
            ranking.inserir(RankingJogadores.chave(bruno), bruno);
            verificar(ranking.buscar(RankingJogadores.chave(ana)) == ana, "Empate não deve sobrescrever Ana.");
            verificar(ranking.buscar(RankingJogadores.chave(bruno)) == bruno, "Empate não deve sobrescrever Bruno.");
            Testes.saidaEsperada("Bruno - 100 ponto(s)\nAna - 100 ponto(s)", () -> ranking.listarMaiores(10));
            verificar(ranking.remover(RankingJogadores.chave(ana)) == ana, "Remover chave antiga antes de atualizar.");
            Jogador atualizada = new Jogador("Ana", 200);
            ranking.inserir(RankingJogadores.chave(atualizada), atualizada);
            verificar(ranking.buscar(RankingJogadores.chave(ana)) == null, "Chave antiga deve desaparecer.");
            Testes.saidaEsperada("Ana - 200 ponto(s)", () -> ranking.listarMaiores(1));
            Testes.saidaEsperada("", () -> ranking.listarMaiores(0));
        });
        executar("Top-K vazio", () -> Testes.saidaEsperada("", () -> new AVL<Integer, String>().listarMaiores(5)));
        executar("bases: 25 CPFs e 30 jogadores", () -> {
            Funcionario[] funcionarios = IndiceCpf.criarFuncionariosDemonstracao();
            verificar(funcionarios.length == 25, "Esperados 25 funcionários.");
            for (int i = 0; i < funcionarios.length; i++) {
                for (int j = i + 1; j < funcionarios.length; j++) {
                    verificar(!funcionarios[i].getCpf().equals(funcionarios[j].getCpf()), "CPFs distintos.");
                }
            }
            verificar(RankingJogadores.criarJogadoresDemonstracao().length == 30, "Esperados 30 jogadores.");
        });
        TESTES.concluir();
    }

    private static void testarArvoreVazia() {
        AVL<Integer, String> arvore = new AVL<>();
        verificar(arvore.buscar(10) == null, "a busca vazia deve devolver null");
        verificar(arvore.remover(10) == null, "a remoção vazia deve devolver null");
        verificar(arvore.altura() == 0, "Altura da árvore vazia deve ser zero.");
        verificar(arvore.fatorBalanceamento() == 0, "Fator da árvore vazia deve ser zero.");
        verificar(arvore.estaBalanceada(), "Árvore vazia deve ser balanceada.");
    }

    private static void testarUmElemento() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(10, "dez");
        verificar("dez".equals(arvore.buscar(10)), "o único elemento deve ser encontrado");
        verificar(arvore.altura() == 1, "Altura da folha deve ser 1.");
        verificar(arvore.fatorBalanceamento() == 0 && arvore.estaBalanceada(), "Folha deve ser balanceada.");
    }

    private static void testarOrdemNormal() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(1, "um");
        arvore.inserir(2, "dois");
        arvore.inserir(3, "três");
        verificar("três".equals(arvore.buscar(3)), "a maior chave deve ser encontrada");
        verificar(Math.abs(arvore.fatorBalanceamento()) <= 1, "a raiz deve permanecer balanceada");
        verificar(arvore.estaBalanceada(), "Todos os nós precisam estar balanceados.");
    }

    private static void testarOrdemInversa() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(3, "três");
        arvore.inserir(2, "dois");
        arvore.inserir(1, "um");
        verificar("um".equals(arvore.buscar(1)), "a menor chave deve ser encontrada");
        verificar(Math.abs(arvore.fatorBalanceamento()) <= 1, "a raiz deve permanecer balanceada");
        verificar(arvore.estaBalanceada(), "Todos os nós precisam estar balanceados.");
    }

    private static void testarChaveRepetida() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(5, "primeiro");
        arvore.inserir(5, "segundo");
        verificar("segundo".equals(arvore.buscar(5)), "Chave repetida deve atualizar seu valor.");
    }

    private static void testarChaveInexistente() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(5, "cinco");
        verificar(arvore.buscar(99) == null, "uma chave inexistente deve devolver null");
        verificar(arvore.remover(99) == null, "remover uma chave inexistente deve devolver null");
    }

    private static void testarRemocao() {
        AVL<Integer, String> arvore = new AVL<>();
        arvore.inserir(2, "dois");
        arvore.inserir(1, "um");
        arvore.inserir(3, "três");
        verificar("dois".equals(arvore.remover(2)), "a remoção deve devolver o valor removido");
        verificar(arvore.buscar(2) == null, "a chave removida não deve ser encontrada");
        verificar(Math.abs(arvore.fatorBalanceamento()) <= 1, "a raiz deve permanecer balanceada");
        verificar(arvore.estaBalanceada(), "Todos os nós precisam estar balanceados.");
    }

    private static void executar(String nome, Runnable casoDeTeste) {
        TESTES.executar(nome, casoDeTeste);
    }

    private static void verificar(boolean condicao, String mensagem) {
        if (!condicao) {
            throw new AssertionError(mensagem);
        }
    }

    private static void testarRotacao(int[] chaves) {
        AVL<Integer, String> arvore = new AVL<>();
        for (int chave : chaves) arvore.inserir(chave, "valor " + chave);
        verificar(arvore.altura() == 2 && arvore.fatorBalanceamento() == 0 && arvore.estaBalanceada(),
                "Três nós devem formar AVL de altura 2 com raiz balanceada.");
        for (int chave : chaves) verificar(("valor " + chave).equals(arvore.buscar(chave)), "Rotação deve preservar os valores.");
        Testes.saidaEsperada("valor 30\nvalor 20\nvalor 10", () -> arvore.listarMaiores(3));
    }
}
