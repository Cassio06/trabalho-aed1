package avl;

import apoio.Validacao;

public class Funcionario {

    private final String cpf;
    private final String nome;
    private final String cargo;

    public Funcionario(String cpf, String nome, String cargo) {
        this.cpf = Validacao.cpf(cpf);
        this.nome = Validacao.texto(nome, "Nome");
        this.cargo = Validacao.texto(cargo, "Cargo");
    }

    public String getCpf() {
        return cpf;
    }

    public String getNome() {
        return nome;
    }

    public String getCargo() {
        return cargo;
    }

    @Override
    public String toString() {
        return cpf + " - " + nome + " - " + cargo;
    }
}
