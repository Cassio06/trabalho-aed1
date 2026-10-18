package bubblesort;

import java.util.Comparator;

public class BubbleSort {

    public static <T> void ordenar(T[] elementos, Comparator<? super T> comparador) {
        for(int i = 0; i < elementos.length - 1; i++){
            boolean trocou = false;
            for(int j = 0; j < elementos.length - 1 - i; j++){
                if(comparador.compare(elementos[j], elementos[j+1]) > 0){
                    T temporario = elementos[j];
                    elementos[j] = elementos[j+1];
                    elementos[j+1] = temporario;
                    trocou = true;
                }

            }
            if(!trocou){
                break;
            }
        }
    }
}
