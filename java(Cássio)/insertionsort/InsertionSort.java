package insertionsort;

import java.util.Comparator;

public class InsertionSort {

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
        long deslocamentos = 0;

        for (int i = 1; i < elementos.length; i++) {
            T chave = elementos[i];
            int j = i - 1;

            while (j >= 0) {
                comparacoes++;

                if (comparador.compare(elementos[j], chave) > 0) {
                    elementos[j + 1] = elementos[j];
                    deslocamentos++;
                    j--;
                } else {
                    break;
                }
            }

            elementos[j + 1] = chave;
        }

        return new Estatisticas(comparacoes, deslocamentos);
    }
    public static class Estatisticas {

        private final long comparacoes;
        private final long deslocamentos;

        public Estatisticas(long comparacoes, long deslocamentos) {
            this.comparacoes = comparacoes;
            this.deslocamentos = deslocamentos;
        }

        public long getComparacoes() {
            return comparacoes;
        }

        public long getDeslocamentos() {
            return deslocamentos;
        }
    }

}
