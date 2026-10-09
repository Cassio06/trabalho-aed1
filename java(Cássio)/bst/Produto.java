package bst;

import apoio.Validacao;

public class Produto {

    private final String nome;

    public Produto(String nome) {
        this.nome = Validacao.texto(nome, "Nome");
    }

    public String getNome() {
        return nome;
    }

    @Override
    public String toString() {
        return nome;
    }
}
