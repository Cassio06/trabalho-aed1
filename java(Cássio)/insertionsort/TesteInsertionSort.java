package insertionsort;

import apoio.Testes;
import java.util.Comparator;

public class TesteInsertionSort {

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
        executar("quantidade da simulação: 13", () -> {
            Carta[] dados = JogoCartas.criarMaoDemonstracao();
            Testes.verificar(dados.length == 13, "Quantidade exigida da simulação.");
            for (Carta dado : dados) Testes.verificar(dado != null, "Registro não pode ser null.");
        });
        executar("comparador decrescente", () -> {
            Integer[] valores = {2, 1, 3, 2};
            InsertionSort.ordenar(valores, Comparator.reverseOrder());
            verificarMesmaOrdem(valores, new Integer[]{3, 2, 2, 1});
        });
        executar("estabilidade de valores iguais", () -> {
            String[] valores = {"b1", "a1", "b2", "a2"};
            InsertionSort.ordenar(valores, Comparator.comparing(texto -> texto.substring(0, 1)));
            String[] esperado = {"a1", "a2", "b1", "b2"};
            for (int i = 0; i < valores.length; i++) {
                Testes.verificar(esperado[i].equals(valores[i]),
                        "Estabilidade: esperado " + esperado[i] + "; obtido " + valores[i]);
            }
        });
        executar("vendas: 10 vendedores e 7 dias reproduzíveis", () -> {
            Vendedor[] dados = RankingVendedores.criarVendedoresDemonstracao();
            Testes.verificar(dados.length == 10, "Esperados 10 vendedores.");
            for (Vendedor vendedor : dados) {
                Testes.verificar(vendedor.getTotalVendido() == 0, "Total inicial deve ser zero.");
                for (int dia = 0; dia < 7; dia++) {
                    double venda = RankingVendedores.vendaDoDia(vendedor.getNome(), dia);
                    Testes.verificar(venda > 0 && venda == RankingVendedores.vendaDoDia(vendedor.getNome(), dia),
                            "Venda deve ser positiva e reproduzível.");
                }
            }
        });
        TESTES.concluir();
    }

    private static void testar(Integer[] valores, Integer[] esperado) {
        InsertionSort.ordenar(valores, Comparator.naturalOrder());
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
