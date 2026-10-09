package bubblesort;

import apoio.Validacao;

public class ProdutoPreco {

    private final String nome;
    private final double preco;

    public ProdutoPreco(String nome, double preco) {
        this.nome = Validacao.texto(nome, "Nome");
        this.preco = Validacao.naoNegativo(preco, "Preço");
    }

    public String getNome() {
        return nome;
    }

    public double getPreco() {
        return preco;
    }

    @Override
    public String toString() {
        return nome + " - R$ " + String.format("%.2f", preco);
    }
}
