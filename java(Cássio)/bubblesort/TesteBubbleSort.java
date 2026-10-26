package bubblesort;

import apoio.Testes;
import java.util.Comparator;

public class TesteBubbleSort {

    private static final Testes TESTES = new Testes();

    public static void main(String[] args) {
        executar("vetor vazio", () -> testar(new Integer[]{}, new Integer[]{}));
        executar("um elemento", () -> testar(new Integer[]{7}, new Integer[]{7}));
        executar("vários elementos", () -> testar(
                new Integer[]{4, 1, 5, 2, 3},
                new Integer[]{1, 2, 3, 4, 5}
        ));
        executar("ordem normal", () -> testar(
                new Integer[]{1, 2, 3, 4, 5},
                new Integer[]{1, 2, 3, 4, 5}
        ));
        executar("ordem inversa", () -> testar(
                new Integer[]{5, 4, 3, 2, 1},
                new Integer[]{1, 2, 3, 4, 5}
        ));
        executar("elementos repetidos", () -> testar(
                new Integer[]{3, 1, 3, 2, 1},
                new Integer[]{1, 1, 2, 3, 3}
        ));
        executar("quantidade da simulação: 20", () -> {
            NotaAluno[] dados = NotasTurma.criarNotasDemonstracao();
            Testes.verificar(dados.length == 20, "Quantidade exigida da simulação.");
            for (NotaAluno dado : dados) Testes.verificar(dado != null, "Registro não pode ser null.");
        });
        executar("comparador decrescente", () -> {
            Integer[] valores = {2, 1, 3, 2};
            BubbleSort.ordenar(valores, Comparator.reverseOrder());
            verificarMesmaOrdem(valores, new Integer[]{3, 2, 2, 1});
        });
        executar("estabilidade de valores iguais", () -> {
            String[] valores = {"b1", "a1", "b2", "a2"};
            BubbleSort.ordenar(valores, Comparator.comparing(texto -> texto.substring(0, 1)));
            String[] esperado = {"a1", "a2", "b1", "b2"};
            for (int i = 0; i < valores.length; i++) {
                Testes.verificar(esperado[i].equals(valores[i]),
                        "Estabilidade: esperado " + esperado[i] + "; obtido " + valores[i]);
            }
        });
        executar("vitrine: 12 produtos", () -> Testes.verificar(
                ProdutosPreco.criarProdutosDemonstracao().length == 12, "Esperados 12 produtos."));
        executar("parada antecipada em vetor já ordenado", () -> {
            Integer[] valores = {1, 2, 3, 4, 5};
            int[] comparacoes = {0};
            BubbleSort.ordenar(valores, (a, b) -> {
                comparacoes[0]++;
                return Integer.compare(a, b);
            });
            verificarMesmaOrdem(valores, new Integer[]{1, 2, 3, 4, 5});
            Testes.verificar(comparacoes[0] == 4,
                    "Bubble Sort otimizado deve encerrar após uma passagem sem trocas: esperado 4 comparações, obtido "
                            + comparacoes[0]);
        });
        executar("estatísticas: vetor já ordenado", () -> {
            Integer[] valores = {1, 2, 3, 4, 5};

            BubbleSort.Estatisticas estatisticas =
                    BubbleSort.ordenarComEstatisticas(
                            valores,
                            Comparator.naturalOrder()
                    );

            Testes.verificar(
                    estatisticas.getComparacoes() == 4,
                    "Esperadas 4 comparações."
            );

            Testes.verificar(
                    estatisticas.getTrocas() == 0,
                    "Esperadas 0 trocas."
            );
        });
        executar("estatísticas: vetor desordenado", () -> {
            Integer[] valores = {3, 1, 2};

            BubbleSort.Estatisticas estatisticas =
                    BubbleSort.ordenarComEstatisticas(
                            valores,
                            Comparator.naturalOrder()
                    );

            Testes.verificar(
                    estatisticas.getComparacoes() == 3,
                    "Esperadas 3 comparações."
            );

            Testes.verificar(
                    estatisticas.getTrocas() == 2,
                    "Esperadas 2 trocas."
            );

            Testes.verificar(
                    valores[0] == 1 && valores[1] == 2 && valores[2] == 3,
                    "O vetor deve terminar ordenado."
            );
        });
        TESTES.concluir();
    }

    private static void testar(Integer[] valores, Integer[] esperado) {
        BubbleSort.ordenar(valores, Comparator.naturalOrder());
        verificarMesmaOrdem(valores, esperado);
    }

    private static void verificarMesmaOrdem(Integer[] atual, Integer[] esperado) {
        if (atual.length != esperado.length) {
            throw new AssertionError("o tamanho do vetor foi alterado");
        }

        for (int i = 0; i < atual.length; i++) {
            if (!atual[i].equals(esperado[i])) {
                throw new AssertionError("posição " + i + ": esperado " + esperado[i] + "; obtido " + atual[i]);
            }
        }
    }

    private static void executar(String nome, Runnable casoDeTeste) {
        TESTES.executar(nome, casoDeTeste);
    }
}
