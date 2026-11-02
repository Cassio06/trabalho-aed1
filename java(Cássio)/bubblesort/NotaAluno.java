package bubblesort;

import apoio.Validacao;

public class NotaAluno {

    private final String nome;
    private final double nota;

    public NotaAluno(String nome, double nota) {
        this.nome = Validacao.texto(nome, "Nome");
        this.nota = validarNota(nota);
    }

    public String getNome() {
        return nome;
    }

    public double getNota() {
        return nota;
    }

    @Override
    public String toString() {
        return nome + " - nota: " + nota;
    }

    private static double validarNota(double valor) {
        Validacao.naoNegativo(valor, "Nota");
        if (valor > 10) {
            throw new IllegalArgumentException("Nota deve estar entre 0 e 10.");
        }
        return valor;
    }
}
