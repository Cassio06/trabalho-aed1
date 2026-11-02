package bubblesort;

import apoio.Entrada;
import apoio.Pendencia;
import java.util.Comparator;
import java.util.Scanner;

public class ProdutosPreco {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        ProdutoPreco[] produtos = criarProdutosDemonstracao();

        System.out.println("Vitrine inicial: " + produtos.length + " produtos");
        for (ProdutoPreco produto : produtos) System.out.println(produto);
        int ordem = entrada.inteiro("1 - Preço crescente; 2 - Preço decrescente; 0 - Sair: ", 0, 2);
        if (ordem == 0) return;
        Comparator<ProdutoPreco> comparador = Comparator.comparingDouble(ProdutoPreco::getPreco);
        if (ordem == 2) comparador = comparador.reversed();
        try {
            BubbleSort.ordenar(produtos, comparador);

            System.out.println(ordem == 1 ? "Preços crescentes:" : "Preços decrescentes:");
            for (ProdutoPreco produto : produtos) {
                System.out.println(produto);
            }
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static ProdutoPreco[] criarProdutosDemonstracao() {
        return new ProdutoPreco[]{
                new ProdutoPreco("Teclado", 120.00),
                new ProdutoPreco("Mouse", 65.90),
                new ProdutoPreco("Monitor", 899.90),
                new ProdutoPreco("Cabo HDMI", 32.50),
                new ProdutoPreco("Webcam", 210.00),
                new ProdutoPreco("Fone", 149.90),
                new ProdutoPreco("Hub USB", 75.00),
                new ProdutoPreco("Suporte", 89.90),
                new ProdutoPreco("Pendrive", 44.90),
                new ProdutoPreco("Caixa de Som", 180.00),
                new ProdutoPreco("Adaptador", 39.90),
                new ProdutoPreco("Microfone", 250.00)
        };
    }
}
