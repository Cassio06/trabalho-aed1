package avl;

import apoio.Validacao;

public class Jogador {

    private final String nome;
    private final int pontuacao;

    public Jogador(String nome, int pontuacao) {
        this.nome = Validacao.texto(nome, "Nome");
        this.pontuacao = validarPontuacao(pontuacao);
    }

    public String getNome() {
        return nome;
    }

    public int getPontuacao() {
        return pontuacao;
    }

    @Override
    public String toString() {
        return nome + " - " + pontuacao + " ponto(s)";
    }

    private static int validarPontuacao(int valor) {
        if (valor < 0) {
            throw new IllegalArgumentException("Pontuação não pode ser negativa.");
        }
        return valor;
    }
}
