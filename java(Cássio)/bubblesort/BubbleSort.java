package bubblesort;

import java.util.Comparator;

public class BubbleSort {

    public static <T> void ordenar(
            T[] elementos,
            Comparator<? super T> comparador
    ) {
        ordenarComEstatisticas(elementos, comparador);
    }

    public static <T> Estatisticas ordenarComEstatisticas(
            T[] elementos,
            Comparator<? super T> comparador
    ) {
        long comparacoes = 0;
        long trocas = 0;

        for (int i = 0; i < elementos.length - 1; i++) {
            boolean trocou = false;

            for (int j = 0; j < elementos.length - 1 - i; j++) {
                comparacoes++;

                if (comparador.compare(elementos[j], elementos[j + 1]) > 0) {
                    T temporario = elementos[j];
                    elementos[j] = elementos[j + 1];
                    elementos[j + 1] = temporario;

                    trocas++;
                    trocou = true;
                }
            }

            if (!trocou) {
                break;
            }
        }

        return new Estatisticas(comparacoes, trocas);
    }

    public static class Estatisticas {

        private final long comparacoes;
        private final long trocas;

        public Estatisticas(long comparacoes, long trocas) {
            this.comparacoes = comparacoes;
            this.trocas = trocas;
        }

        public long getComparacoes() {
            return comparacoes;
        }

        public long getTrocas() {
            return trocas;
        }
    }
}