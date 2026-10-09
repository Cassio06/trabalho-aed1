package bst;

import apoio.Validacao;

public class Aluno {

    private final int matricula;
    private final String nome;
    private final String curso;

    public Aluno(int matricula, String nome, String curso) {
        this.matricula = Validacao.positivo(matricula, "Matrícula");
        this.nome = Validacao.texto(nome, "Nome");
        this.curso = Validacao.texto(curso, "Curso");
    }

    public int getMatricula() {
        return matricula;
    }

    public String getNome() {
        return nome;
    }

    public String getCurso() {
        return curso;
    }

    @Override
    public String toString() {
        return matricula + " - " + nome + " - " + curso;
    }
}
