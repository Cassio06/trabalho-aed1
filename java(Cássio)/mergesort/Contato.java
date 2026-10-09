package mergesort;

import apoio.Validacao;

public class Contato {

    private final String nome;
    private final String informacaoContato;

    public Contato(String nome, String informacaoContato) {
        this.nome = Validacao.texto(nome, "Nome");
        this.informacaoContato = Validacao.texto(informacaoContato, "Informação de contato");
    }

    public String getNome() {
        return nome;
    }

    public String getInformacaoContato() {
        return informacaoContato;
    }

    @Override
    public String toString() {
        return nome + " - " + informacaoContato;
    }
}
