package mergesort;

import apoio.Testes;
import java.time.LocalDateTime;
import java.util.Comparator;

public class TesteMergeSort {

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
        executar("quantidade da simulação: 50", () -> {
            Transacao[] dados = TransacoesBancarias.criarTransacoesDemonstracao();
            Testes.verificar(dados.length == 50, "Quantidade exigida da simulação.");
            for (Transacao dado : dados) Testes.verificar(dado != null, "Registro não pode ser null.");
        });
        executar("comparador decrescente", () -> {
            Integer[] valores = {2, 1, 3, 2};
            MergeSort.ordenar(valores, Comparator.reverseOrder());
            verificarMesmaOrdem(valores, new Integer[]{3, 2, 2, 1});
        });
        executar("estabilidade de valores iguais", () -> {
            String[] valores = {"b1", "a1", "b2", "a2"};
            MergeSort.ordenar(valores, Comparator.comparing(texto -> texto.substring(0, 1)));
            String[] esperado = {"a1", "a2", "b1", "b2"};
            for (int i = 0; i < valores.length; i++) {
                Testes.verificar(esperado[i].equals(valores[i]),
                        "Estabilidade: esperado " + esperado[i] + "; obtido " + valores[i]);
            }
        });
        executar("transações no mesmo instante mantêm ordem de registro", () -> {
            LocalDateTime data = LocalDateTime.of(2026, 8, 1, 8, 0);
            Transacao primeira = new Transacao(data, 20, "PIX recebido");
            Transacao segunda = new Transacao(data, -10, "Compra");
            Transacao anterior = new Transacao(data.minusHours(1), -5, "Tarifa");
            Transacao[] transacoes = {primeira, segunda, anterior};
            MergeSort.ordenar(transacoes, Comparator.comparing(Transacao::getDataHora));
            Testes.verificar(transacoes[0] == anterior && transacoes[1] == primeira && transacoes[2] == segunda,
                    "Esperado: Tarifa, PIX recebido, Compra.");
        });
        executar("contatos: duas bases ordenadas com 20 registros", () -> {
            for (String id : new String[]{"A", "B"}) {
                Contato[] contatos = MesclagemContatos.criarLista(id, 20);
                Testes.verificar(contatos.length == 20, "Cada departamento deve ter 20 contatos.");
                for (int i = 1; i < contatos.length; i++) {
                    Testes.verificar(contatos[i - 1].getNome().compareToIgnoreCase(contatos[i].getNome()) < 0,
                            "As entradas precisam chegar ordenadas e sem duplicatas internas.");
                }
            }
        });
        executar("mesclar contatos: duas listas vazias", () -> verificarContatos(
                MergeSort.mesclarContatos(new Contato[0], new Contato[0]), new Contato[0]));
        executar("mesclar contatos: uma lista vazia", () -> {
            Contato ana = new Contato("Ana", "ana@exemplo.com");
            verificarContatos(MergeSort.mesclarContatos(new Contato[0], new Contato[]{ana}), new Contato[]{ana});
            verificarContatos(MergeSort.mesclarContatos(new Contato[]{ana}, new Contato[0]), new Contato[]{ana});
        });
        executar("mesclar contatos: intercalar e remover duplicatas", () -> {
            Contato ana = new Contato("Ana", "ana@exemplo.com");
            Contato bruno = new Contato("Bruno", "bruno@exemplo.com");
            Contato carla = new Contato("Carla", "carla@exemplo.com");
            Contato duplicado = new Contato("ANA", "outro@exemplo.com");
            verificarContatos(MergeSort.mesclarContatos(new Contato[]{ana, carla}, new Contato[]{duplicado, bruno}),
                    new Contato[]{ana, bruno, carla});
        });
        executar("mesclar contatos: duplicatas internas", () -> {
            Contato ana = new Contato("Ana", "ana@exemplo.com");
            verificarContatos(MergeSort.mesclarContatos(new Contato[]{ana, ana}, new Contato[]{ana}),
                    new Contato[]{ana});
        });
        executar("mesclar contatos: base completa resulta em 30 contatos", () -> {
            Contato[] primeira = MesclagemContatos.criarLista("A", 20);
            Contato[] segunda = MesclagemContatos.criarLista("B", 20);
            Contato[] primeiraOriginal = primeira.clone();
            Contato[] segundaOriginal = segunda.clone();
            Contato[] resultado = MergeSort.mesclarContatos(primeira, segunda);
            Testes.verificar(resultado.length == 30, "Esperados 30 contatos únicos, não 40.");
            String[] nomesEsperados = {
                    "Alice Teixeira", "Ana Lima", "Bernardo Castro", "Bruno Costa", "Camila Fernandes",
                    "Carla Alves", "Daniel Rocha", "Diego Moura", "Eduarda Lopes", "Elisa Sousa",
                    "Fabio Santos", "Felipe Correia", "Gabriela Nunes", "Giovana Cardoso", "Heitor Melo",
                    "Henrique Vieira", "Iara Mendes", "Isabela Dias", "Joao Silva", "Julio Farias",
                    "Karen Ribeiro", "Lucas Martins", "Marina Barros", "Nicolas Freitas", "Olivia Gomes",
                    "Paulo Araujo", "Rafaela Torres", "Samuel Pinto", "Tais Carvalho", "Victor Braga"
            };
            for (int i = 0; i < resultado.length; i++) {
                Testes.verificar(resultado[i] != null && nomesEsperados[i].equals(resultado[i].getNome()),
                        "Esperado " + nomesEsperados[i] + " na posição " + i);
            }
            verificarContatos(primeira, primeiraOriginal);
            verificarContatos(segunda, segundaOriginal);
            for (int i = 1; i < resultado.length; i++) {
                Testes.verificar(resultado[i - 1].getNome().compareToIgnoreCase(resultado[i].getNome()) < 0,
                        "Resultado deve ser ordenado sem duplicatas.");
            }
        });
        TESTES.concluir();
    }

    private static void testar(Integer[] valores, Integer[] esperado) {
        MergeSort.ordenar(valores, Comparator.naturalOrder());
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
    private static void verificarContatos(Contato[] atual, Contato[] esperado) {
        Testes.verificar(atual.length == esperado.length, "Quantidade incorreta de contatos.");
        for (int i = 0; i < atual.length; i++) {
            Testes.verificar(atual[i] == esperado[i], "Contato incorreto na posição " + i);
        }
    }

}
