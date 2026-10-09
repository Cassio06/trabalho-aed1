package bubblesort;

import apoio.Dados;
import apoio.Entrada;
import apoio.Pendencia;
import java.util.Comparator;
import java.util.Scanner;

public class NotasTurma {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        int modo = entrada.inteiro("1 - Simular 20 notas; 2 - Digitar notas (até 30); 0 - Sair: ", 0, 2);
        if (modo == 0) return;
        NotaAluno[] notas;
        if (modo == 1) notas = criarNotasDemonstracao();
        else {
            notas = new NotaAluno[entrada.inteiro("Quantidade de alunos: ", 1, 30)];
            for (int i = 0; i < notas.length; i++) {
                notas[i] = new NotaAluno(entrada.texto("Nome do aluno " + (i + 1) + ": "),
                        entrada.decimal("Nota (0 a 10): ", 0, 10));
            }
        }
        System.out.println("Notas recebidas:");
        double soma = 0;
        for (NotaAluno nota : notas) {
            System.out.println(nota);
            soma += nota.getNota();
        }
        System.out.printf("Média da turma (independente da ordenação): %.2f%n", soma / notas.length);

        try {
            BubbleSort.ordenar(notas, Comparator.comparingDouble(NotaAluno::getNota));

            System.out.println("Notas em ordem crescente:");
            for (NotaAluno notaAluno : notas) {
                System.out.println(notaAluno);
            }
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static NotaAluno[] criarNotasDemonstracao() {
        NotaAluno[] notas = new NotaAluno[20];

        for (int i = 0; i < notas.length; i++) {
            double nota = ((i * 13) % 21) / 2.0;
            notas[i] = new NotaAluno(Dados.nome(i), nota);
        }

        return notas;
    }
}
