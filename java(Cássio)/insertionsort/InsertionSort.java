package insertionsort;

import java.util.Comparator;

public class InsertionSort {

    public static <T> void ordenar(T[] elementos, Comparator<? super T> comparador) {
        // TODO: ordenar o vetor com Insertion Sort.
        for (int i = 1; i < elementos.length; i++) {
            T chave = elementos[i];
            int j = i - 1;
            while (j >= 0 && comparador.compare(elementos[j], chave) > 0) {
                elementos[j + 1] = elementos[j];
                j--;
            }
            elementos[j + 1] = chave;
        }
    }
}
