package bst;

import apoio.Testes;

public class TesteBST {

    private static final Testes TESTES = new Testes();

    public static void main(String[] args) {
        executar("árvore vazia", TesteBST::testarArvoreVazia);
        executar("um elemento", TesteBST::testarUmElemento);
        executar("ordem normal", TesteBST::testarOrdemNormal);
        executar("ordem inversa", TesteBST::testarOrdemInversa);
        executar("chave repetida", TesteBST::testarChaveRepetida);
        executar("busca e remoção inexistentes", TesteBST::testarChaveInexistente);
        executar("remoção existente", TesteBST::testarRemocaoExistente);
        executar("percurso vazio", () -> Testes.saidaEsperada("", new BST<Integer, String>()::listarEmOrdem));
        executar("remoção de folha e nó com um filho", () -> {
            BST<Integer, String> arvore = new BST<>();
            arvore.inserir(4, "quatro");
            arvore.inserir(2, "dois");
            arvore.inserir(1, "um");
            arvore.inserir(3, "três");
            verificar("três".equals(arvore.remover(3)), "Remover folha deve devolver três.");
            verificar("dois".equals(arvore.remover(2)), "Remover nó com filho deve devolver dois.");
            verificar("um".equals(arvore.buscar(1)) && "quatro".equals(arvore.buscar(4)), "Preservar demais nós.");
            Testes.saidaEsperada("um\nquatro", arvore::listarEmOrdem);
        });
        executar("remover último elemento", () -> {
            BST<Integer, String> arvore = new BST<>();
            arvore.inserir(1, "um");
            verificar("um".equals(arvore.remover(1)) && arvore.buscar(1) == null, "Árvore deve ficar vazia.");
            Testes.saidaEsperada("", arvore::listarEmOrdem);
        });
        executar("autocomplete: prefixo ca e normalização", () -> {
            BST<String, Produto> catalogo = catalogo();
            Testes.saidaEsperada("Caderno\nCalculadora\nCaneta Azul\nCaneta Preta\nCaneta Vermelha\nCartolina",
                    () -> catalogo.listarPorPrefixo(AutocompleteProdutos.normalizar(" CA ")));
        });
        executar("autocomplete: prefixo inexistente", () -> {
            BST<String, Produto> catalogo = catalogo();
            Testes.saidaEsperada("", () -> catalogo.listarPorPrefixo("zzz"));
        });
        executar("autocomplete vazio e prefixo vazio", () -> {
            BST<String, String> catalogo = new BST<>();
            Testes.saidaEsperada("", () -> catalogo.listarPorPrefixo("ca"));
            catalogo.inserir("caneta", "Caneta");
            catalogo.inserir("caderno", "Caderno");
            Testes.saidaEsperada("Caderno\nCaneta", () -> catalogo.listarPorPrefixo(""));
        });
        executar("bases: 20 matrículas distintas e 30 produtos", () -> {
            Aluno[] alunos = CadastroAlunos.criarAlunosDemonstracao();
            verificar(alunos.length == 20, "Esperados 20 alunos.");
            for (int i = 0; i < alunos.length; i++) {
                for (int j = i + 1; j < alunos.length; j++) {
                    verificar(alunos[i].getMatricula() != alunos[j].getMatricula(), "Matrículas precisam ser distintas.");
                }
            }
            verificar(AutocompleteProdutos.criarProdutosDemonstracao().length == 30, "Esperados 30 produtos.");
        });
        TESTES.concluir();
    }

    private static void testarArvoreVazia() {
        BST<Integer, String> arvore = new BST<>();
        verificar(arvore.buscar(10) == null, "a busca vazia deve devolver null");
        verificar(arvore.remover(10) == null, "a remoção vazia deve devolver null");
    }

    private static void testarUmElemento() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(10, "dez");
        verificar("dez".equals(arvore.buscar(10)), "o único elemento deve ser encontrado");
    }

    private static void testarOrdemNormal() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(1, "um");
        arvore.inserir(2, "dois");
        arvore.inserir(3, "três");
        verificar("três".equals(arvore.buscar(3)), "a maior chave deve ser encontrada");
        Testes.saidaEsperada("um\ndois\ntrês", arvore::listarEmOrdem);
    }

    private static void testarOrdemInversa() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(3, "três");
        arvore.inserir(2, "dois");
        arvore.inserir(1, "um");
        verificar("um".equals(arvore.buscar(1)), "a menor chave deve ser encontrada");
        Testes.saidaEsperada("um\ndois\ntrês", arvore::listarEmOrdem);
    }

    private static void testarChaveRepetida() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(5, "primeiro");
        arvore.inserir(5, "segundo");
        verificar("segundo".equals(arvore.buscar(5)), "Chave repetida deve atualizar o valor.");
    }

    private static void testarChaveInexistente() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(5, "cinco");
        verificar(arvore.buscar(99) == null, "uma chave inexistente deve devolver null");
        verificar(arvore.remover(99) == null, "remover uma chave inexistente deve devolver null");
    }

    private static void testarRemocaoExistente() {
        BST<Integer, String> arvore = new BST<>();
        arvore.inserir(2, "dois");
        arvore.inserir(1, "um");
        arvore.inserir(3, "três");
        verificar("dois".equals(arvore.remover(2)), "a remoção deve devolver o valor removido");
        verificar(arvore.buscar(2) == null, "a chave removida não deve ser encontrada");
        verificar("um".equals(arvore.buscar(1)) && "três".equals(arvore.buscar(3)), "Subárvores devem ser preservadas.");
        Testes.saidaEsperada("um\ntrês", arvore::listarEmOrdem);
    }

    private static void executar(String nome, Runnable casoDeTeste) {
        TESTES.executar(nome, casoDeTeste);
    }

    private static void verificar(boolean condicao, String mensagem) {
        if (!condicao) {
            throw new AssertionError(mensagem);
        }
    }

    private static BST<String, Produto> catalogo() {
        BST<String, Produto> catalogo = new BST<>();
        for (Produto produto : AutocompleteProdutos.criarProdutosDemonstracao()) {
            catalogo.inserir(AutocompleteProdutos.normalizar(produto.getNome()), produto);
        }
        return catalogo;
    }
}
