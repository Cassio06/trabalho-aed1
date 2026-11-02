package insertionsort;

import apoio.Validacao;
import java.util.Locale;

public class Carta {

    private final String valor;
    private final String naipe;

    public Carta(String valor, String naipe) {
        this.valor = validarValor(valor);
        this.naipe = validarNaipe(naipe);
    }

    public String getValor() {
        return valor;
    }

    public String getNaipe() {
        return naipe;
    }

    @Override
    public String toString() {
        return valor + " de " + naipe;
    }

    private static String validarValor(String valor) {
        String texto = Validacao.texto(valor, "Valor").toUpperCase(Locale.ROOT);
        if (!texto.matches("A|[2-9]|10|J|Q|K")) {
            throw new IllegalArgumentException("Valor da carta: A, 2 a 10, J, Q ou K.");
        }
        return texto;
    }

    private static String validarNaipe(String valor) {
        String naipe = Validacao.texto(valor, "Naipe");
        String[] naipes = {"Copas", "Espadas", "Ouros", "Paus"};
        for (String permitido : naipes) {
            if (permitido.equalsIgnoreCase(naipe)) {
                return permitido;
            }
        }
        throw new IllegalArgumentException("Naipe: Copas, Espadas, Ouros ou Paus.");
    }
}
