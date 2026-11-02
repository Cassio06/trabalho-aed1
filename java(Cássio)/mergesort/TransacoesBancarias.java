package mergesort;

import apoio.Pendencia;
import java.time.LocalDateTime;
import java.util.Comparator;

public class TransacoesBancarias {

    public static void main(String[] args) {
        Transacao[] transacoes = criarTransacoesDemonstracao();

        System.out.println("Histórico recebido: " + transacoes.length + " transações fictícias");
        for (Transacao transacao : transacoes) System.out.println(transacao);
        try {
            MergeSort.ordenar(transacoes, Comparator.comparing(Transacao::getDataHora));

            System.out.println("Transações em ordem de data e hora:");
            for (Transacao transacao : transacoes) {
                System.out.println(transacao);
            }
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static Transacao[] criarTransacoesDemonstracao() {
        Transacao[] transacoes = new Transacao[50];
        LocalDateTime inicio = LocalDateTime.of(2026, 8, 1, 8, 0);

        for (int i = 0; i < transacoes.length; i++) {
            int deslocamentoHoras = (i * 17) % (transacoes.length / 2);
            double valor = 25.0 + ((i * 43) % 600);
            transacoes[i] = new Transacao(
                    inicio.plusHours(deslocamentoHoras),
                    i % 2 == 0 ? valor : -valor,
                    (i % 2 == 0 ? "PIX recebido #" : "Pagamento de compra #") + (i + 1)
            );
        }

        return transacoes;
    }
}
