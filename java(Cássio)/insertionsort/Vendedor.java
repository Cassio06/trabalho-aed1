package insertionsort;

import apoio.Validacao;
import java.util.Locale;

public class Vendedor {

    private final String nome;
    private final double totalVendido;

    public Vendedor(String nome, double totalVendido) {
        this.nome = Validacao.texto(nome, "Nome");
        this.totalVendido = Validacao.naoNegativo(totalVendido, "Total vendido");
    }

    public String getNome() {
        return nome;
    }

    public double getTotalVendido() {
        return totalVendido;
    }

    @Override
    public String toString() {
        return nome + " - total vendido: R$ " + String.format(Locale.forLanguageTag("pt-BR"), "%,.2f", totalVendido);
    }
}
