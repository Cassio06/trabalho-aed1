package mergesort;

import java.util.Arrays;
import java.util.Comparator;

public class MergeSort {

    public static <T> void ordenar(T[] elementos, Comparator<? super T> comparador) {
        T[] auxiliar = elementos.clone();

        ordenarRecursivo(elementos, auxiliar, 0, elementos.length - 1, comparador);
    }

    private static <T> void ordenarRecursivo(T[] elementos, T[] auxiliar, int inicio, int fim, Comparator<? super T> comparador) {
        if(inicio >= fim){
            return;
        }
        int meio = inicio + (fim - inicio) / 2;

        ordenarRecursivo(elementos, auxiliar, inicio, meio, comparador);

        ordenarRecursivo(elementos, auxiliar, meio + 1, fim, comparador);

        intercalar(elementos, auxiliar, inicio, meio, fim, comparador);

    }

    private static <T> void intercalar(T[] elementos, T[] auxiliar, int inicio, int meio, int fim, Comparator<? super T> comparador) {

        for (int k = inicio; k <= fim; k++) {
            auxiliar[k] = elementos[k];
        }
        int esquerda = inicio;
        int direita = meio + 1;
        int destino = inicio;
        while(esquerda <= meio && direita <= fim){
            if(comparador.compare(auxiliar[esquerda], auxiliar[direita]) <= 0){
                elementos[destino] = auxiliar[esquerda];
                esquerda++;

            }else{
                elementos[destino] = auxiliar[direita];
                direita++;

            }
            destino++;

        }
        while (esquerda <= meio) {
            elementos[destino] = auxiliar[esquerda];
            esquerda++;
            destino++;
        }

        while (direita <= fim) {
            elementos[destino] = auxiliar[direita];
            direita++;
            destino++;
        }

    }

    /** Entradas já ordenadas por nome; nomes iguais ignorando caixa são duplicatas.
     * Retém o contato da primeira lista em caso de empate, sem reordenar as entradas. */
    public static Contato[] mesclarContatos(Contato[] primeira, Contato[] segunda) {
        Contato[] resultado = new Contato[primeira.length + segunda.length];

        int i = 0;
        int j = 0;
        int quantidade = 0;
        while (i < primeira.length && j < segunda.length) {
            int comparacao = primeira[i].getNome().compareToIgnoreCase(segunda[j].getNome());
            Contato escolhido;
            if (comparacao < 0) {
                escolhido = primeira[i];
                i++;
            } else if (comparacao > 0) {
                escolhido = segunda[j];
                j++;
            } else {
                escolhido = primeira[i];
                i++;
                j++;
            }
            if (quantidade == 0 ||
                    !resultado[quantidade - 1].getNome()
                            .equalsIgnoreCase(escolhido.getNome())) {

                resultado[quantidade] = escolhido;
                quantidade++;
            }
        }
        while (i < primeira.length) {
            Contato escolhido = primeira[i];
            i++;

            if (quantidade == 0 ||
                    !resultado[quantidade - 1].getNome()
                            .equalsIgnoreCase(escolhido.getNome())) {

                resultado[quantidade] = escolhido;
                quantidade++;
            }
        }
        while (j < segunda.length) {
            Contato escolhido = segunda[j];
            j++;

            if (quantidade == 0 ||
                    !resultado[quantidade - 1].getNome()
                            .equalsIgnoreCase(escolhido.getNome())) {

                resultado[quantidade] = escolhido;
                quantidade++;
            }
        }
        return Arrays.copyOf(resultado, quantidade);
    }
}
