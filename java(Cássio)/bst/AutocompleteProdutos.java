package bst;

import apoio.Entrada;
import apoio.Pendencia;
import java.util.Locale;
import java.util.Scanner;

public class AutocompleteProdutos {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        Produto[] produtos = criarProdutosDemonstracao();
        BST<String, Produto> catalogo = new BST<>();
        System.out.println("Catálogo inicial: " + produtos.length + " produtos.");
        for (Produto produto : produtos) System.out.println(produto);
        try {
            for (Produto produto : produtos) catalogo.inserir(normalizar(produto.getNome()), produto);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        while (true) {
            int opcao = entrada.inteiro("\n1 - Buscar nome exato; 2 - Autocomplete por prefixo; "
                    + "3 - Listar todos; 0 - Sair: ", 0, 3);
            if (opcao == 0) return;
            try {
                switch (opcao) {
                    case 1 -> {
                        Produto produto = catalogo.buscar(normalizar(entrada.texto("Nome: ")));
                        System.out.println(produto == null ? "Produto não encontrado." : produto);
                    }
                    case 2 -> {
                        String prefixo = normalizar(entrada.texto("Prefixo: "));
                        System.out.println("Sugestões para " + prefixo + " (nenhuma linha se não houver):");
                        catalogo.listarPorPrefixo(prefixo);
                    }
                    case 3 -> catalogo.listarEmOrdem();
                    default -> throw new IllegalStateException("Opção inesperada.");
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    static String normalizar(String nome) {
        return nome.trim().toLowerCase(Locale.ROOT);
    }

    static Produto[] criarProdutosDemonstracao() {
        String[] nomes = {
                "Agenda", "Apontador", "Borracha", "Caderno", "Calculadora",
                "Caneta Azul", "Caneta Preta", "Caneta Vermelha", "Cartolina", "Clips",
                "Cola Bastao", "Compasso", "Corretivo", "Estojo", "Etiqueta",
                "Fichario", "Giz de Cera", "Grampeador", "Lapis", "Lapiseira",
                "Livro", "Marcador", "Mochila", "Papel A4", "Pasta",
                "Regua", "Tesoura", "Tinta Guache", "Transferidor", "Universitario"
        };
        Produto[] produtos = new Produto[nomes.length];

        for (int i = 0; i < nomes.length; i++) {
            produtos[i] = new Produto(nomes[i]);
        }

        return produtos;
    }
}
