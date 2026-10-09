package insertionsort;

import apoio.Pendencia;
import java.util.Comparator;

public class JogoCartas {

    public static void main(String[] args) {
        Carta[] mao = criarMaoDemonstracao();
        Comparator<Carta> porValorENaipe = Comparator
                .comparingInt(JogoCartas::ordemDoValor)
                .thenComparing(Carta::getNaipe);

        Carta[] recebidas = mao;
        mao = new Carta[0];
        System.out.println("Recebimento de " + recebidas.length + " cartas. Ás vale 1; desempate por naipe.");
        try {
            for (Carta recebida : recebidas) {
                Carta[] ampliada = new Carta[mao.length + 1];
                for (int i = 0; i < mao.length; i++) ampliada[i] = mao[i];
                ampliada[mao.length] = recebida;
                System.out.println("\nRecebida: " + recebida);
                InsertionSort.ordenar(ampliada, porValorENaipe);
                mao = ampliada;
                System.out.println("Mão após a inserção:");
                for (Carta carta : mao) System.out.println(carta);
            }
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static Carta[] criarMaoDemonstracao() {
        return new Carta[]{
                new Carta("K", "Copas"),
                new Carta("3", "Paus"),
                new Carta("A", "Espadas"),
                new Carta("10", "Ouros"),
                new Carta("7", "Copas"),
                new Carta("J", "Paus"),
                new Carta("2", "Espadas"),
                new Carta("Q", "Ouros"),
                new Carta("5", "Copas"),
                new Carta("9", "Paus"),
                new Carta("4", "Espadas"),
                new Carta("8", "Ouros"),
                new Carta("6", "Copas")
        };
    }

    private static int ordemDoValor(Carta carta) {
        return switch (carta.getValor()) {
            case "A" -> 1;
            case "J" -> 11;
            case "Q" -> 12;
            case "K" -> 13;
            default -> Integer.parseInt(carta.getValor());
        };
    }
}
