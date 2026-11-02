package bst;

import apoio.Dados;
import apoio.Entrada;
import apoio.Pendencia;
import java.util.Scanner;

public class CadastroAlunos {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        Aluno[] alunos = criarAlunosDemonstracao();
        BST<Integer, Aluno> cadastro = new BST<>();
        System.out.println("Base inicial: " + alunos.length + " alunos.");
        for (Aluno aluno : alunos) System.out.println(aluno);
        try {
            for (Aluno aluno : alunos) cadastro.inserir(aluno.getMatricula(), aluno);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        while (true) {
            int opcao = entrada.inteiro("\n1 - Cadastrar/atualizar; 2 - Buscar; 3 - Remover; "
                    + "4 - Listar em ordem; 0 - Sair: ", 0, 4);
            if (opcao == 0) return;
            try {
                if (opcao == 4) cadastro.listarEmOrdem();
                else {
                    int matricula = entrada.inteiro("Matrícula: ", 1, Integer.MAX_VALUE);
                    if (opcao == 1) {
                        Aluno aluno = new Aluno(matricula, entrada.texto("Nome: "), entrada.texto("Curso: "));
                        cadastro.inserir(matricula, aluno);
                        System.out.println("Cadastro salvo: " + aluno);
                    } else {
                        Aluno aluno = opcao == 2 ? cadastro.buscar(matricula) : cadastro.remover(matricula);
                        System.out.println(aluno == null ? "Matrícula não encontrada."
                                : (opcao == 2 ? "Encontrado: " : "Removido: ") + aluno);
                    }
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    static Aluno[] criarAlunosDemonstracao() {
        Aluno[] alunos = new Aluno[20];
        String[] cursos = {"Computação", "Engenharia", "Matemática", "Administração"};

        for (int i = 0; i < alunos.length; i++) {
            int matricula = 1001 + ((i * 7) % alunos.length);
            alunos[i] = new Aluno(matricula, Dados.nome(i), cursos[i % cursos.length]);
        }

        return alunos;
    }
}
