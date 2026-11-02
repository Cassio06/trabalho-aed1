package avl;

import apoio.Dados;
import apoio.Entrada;
import apoio.Pendencia;
import java.util.Locale;
import java.util.Scanner;

public class RankingJogadores {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        Jogador[] jogadores = criarJogadoresDemonstracao();
        // A chave inclui o nome para não perder jogadores com pontuações iguais.
        AVL<String, Jogador> ranking = new AVL<>();
        System.out.println("Simulação: " + jogadores.length + " jogadores. Empates: nome decrescente no Top-K.");
        exibirBase(jogadores);
        try {
            for (Jogador jogador : jogadores) ranking.inserir(chave(jogador), jogador);
            System.out.println("\nTrês atualizações de pontuação da rodada:");
            atualizar(ranking, jogadores, 0, 750);
            atualizar(ranking, jogadores, 5, 750);
            atualizar(ranking, jogadores, 12, 920);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        while (true) {
            int opcao = entrada.inteiro("\n1 - Atualizar pontuação; 2 - Top-K; 3 - Consultar jogador; "
                    + "4 - Altura/balanceamento; 5 - Mostrar identificadores; 0 - Sair: ", 0, 5);
            if (opcao == 0) return;
            try {
                switch (opcao) {
                    case 1 -> {
                        int indice = entrada.inteiro("Número do jogador (1 a 30): ", 1, jogadores.length) - 1;
                        int pontos = entrada.inteiro("Nova pontuação: ", 0, Integer.MAX_VALUE);
                        atualizar(ranking, jogadores, indice, pontos);
                    }
                    case 2 -> ranking.listarMaiores(entrada.inteiro("K (0 a 30): ", 0, jogadores.length));
                    case 3 -> {
                        int indice = entrada.inteiro("Número do jogador (1 a 30): ", 1, jogadores.length) - 1;
                        Jogador jogador = ranking.buscar(chave(jogadores[indice]));
                        System.out.println(jogador == null ? "Jogador não encontrado na AVL." : jogador);
                    }
                    case 4 -> {
                        System.out.println("Altura: " + ranking.altura());
                        System.out.println("Fator da raiz: " + ranking.fatorBalanceamento());
                        System.out.println("Todos os nós balanceados: " + ranking.estaBalanceada());
                    }
                    case 5 -> exibirBase(jogadores);
                    default -> throw new IllegalStateException("Opção inesperada.");
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    private static void atualizar(AVL<String, Jogador> ranking, Jogador[] jogadores, int indice, int pontos) {
        Jogador anterior = jogadores[indice];
        Jogador atualizado = new Jogador(anterior.getNome(), pontos);
        Jogador removido = ranking.remover(chave(anterior));
        if (removido == null) {
            System.out.println("Jogador não encontrado; atualização não realizada: " + anterior.getNome());
            return;
        }
        ranking.inserir(chave(atualizado), atualizado);
        jogadores[indice] = atualizado;
        System.out.println(anterior + " -> " + atualizado);
    }

    static String chave(Jogador jogador) {
        // Dez dígitos cobrem todos os ints não negativos e preservam ordem numérica na String.
        return String.format(Locale.ROOT, "%010d:%s", jogador.getPontuacao(), jogador.getNome());
    }

    static Jogador[] criarJogadoresDemonstracao() {
        Jogador[] jogadores = new Jogador[30];
        for (int i = 0; i < jogadores.length; i++) {
            int pontuacao = 520 + ((i * 37) % 300);
            jogadores[i] = new Jogador(Dados.nome(i), pontuacao);
        }
        return jogadores;
    }

    private static void exibirBase(Jogador[] jogadores) {
        for (int i = 0; i < jogadores.length; i++) System.out.println((i + 1) + " - " + jogadores[i]);
    }
}
