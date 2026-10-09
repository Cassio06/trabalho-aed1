package fila;

import apoio.Entrada;
import apoio.Pendencia;
import java.util.Scanner;

public class FilaImpressao {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        TrabalhoImpressao[] trabalhos = criarTrabalhosDemonstracao();
        Fila<TrabalhoImpressao> filaImpressao = new Fila<>();
        System.out.println("Simulação: " + trabalhos.length + " trabalhos de impressão.");
        for (TrabalhoImpressao trabalho : trabalhos) System.out.println("Enviado: " + trabalho);
        try {
            for (TrabalhoImpressao trabalho : trabalhos) filaImpressao.enqueue(trabalho);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        int impressos = 0;
        int paginas = 0;
        while (true) {
            int opcao = entrada.inteiro("\n1 - Enviar; 2 - Imprimir próximo; 3 - Listar fila; "
                    + "4 - Tamanho; 5 - Imprimir todos; 0 - Sair: ", 0, 5);
            if (opcao == 0) {
                System.out.println("Relatório: " + impressos + " trabalho(s), " + paginas + " página(s). "
                        + "A sequência efetiva foi exibida a cada impressão.");
                return;
            }
            try {
                switch (opcao) {
                    case 1 -> {
                        TrabalhoImpressao trabalho = new TrabalhoImpressao(entrada.texto("Aluno: "),
                                entrada.texto("Arquivo: "), entrada.inteiro("Páginas: ", 1, 10000));
                        filaImpressao.enqueue(trabalho);
                        System.out.println("Enviado: " + trabalho);
                    }
                    case 2, 5 -> {
                        if (filaImpressao.isEmpty()) {
                            System.out.println("Não há trabalhos aguardando.");
                            break;
                        }
                        do {
                            TrabalhoImpressao trabalho = filaImpressao.dequeue();
                            impressos++;
                            paginas += trabalho.getNumeroPaginas();
                            System.out.println(impressos + " - Imprimindo: " + trabalho);
                        } while (opcao == 5 && !filaImpressao.isEmpty());
                    }
                    case 3 -> filaImpressao.listar();
                    case 4 -> System.out.println("Aguardando: " + filaImpressao.size());
                    default -> throw new IllegalStateException("Opção inesperada.");
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    static TrabalhoImpressao[] criarTrabalhosDemonstracao() {
        return new TrabalhoImpressao[]{
                new TrabalhoImpressao("Ana", "algoritmos.pdf", 8),
                new TrabalhoImpressao("Bruno", "resumo.docx", 3),
                new TrabalhoImpressao("Carla", "atividade-01.pdf", 5),
                new TrabalhoImpressao("Daniel", "grafo.png", 1),
                new TrabalhoImpressao("Elisa", "relatorio.pdf", 12),
                new TrabalhoImpressao("Fabio", "codigo.txt", 4),
                new TrabalhoImpressao("Gabriela", "pesquisa.pdf", 7),
                new TrabalhoImpressao("Heitor", "trabalho-final.pdf", 15),
                new TrabalhoImpressao("Isabela", "exercicios.pdf", 6),
                new TrabalhoImpressao("Joao", "capa.docx", 2),
                new TrabalhoImpressao("Karen", "tabela.pdf", 3),
                new TrabalhoImpressao("Lucas", "seminario.pdf", 9)
        };
    }
}
