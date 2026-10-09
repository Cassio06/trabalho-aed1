package insertionsort;

import apoio.Dados;
import apoio.Pendencia;
import java.util.Comparator;

public class RankingVendedores {

    public static void main(String[] args) {
        Vendedor[] vendedores = criarVendedoresDemonstracao();
        Comparator<Vendedor> maiorTotalPrimeiro = Comparator.comparingDouble(Vendedor::getTotalVendido).reversed();
        try {
            for (int dia = 0; dia < 7; dia++) {
                System.out.println("\nDia " + (dia + 1) + " da semana (totais acumulados):");
                // Mantém a ordem do ranking anterior; apenas os totais são atualizados.
                for (int i = 0; i < vendedores.length; i++) {
                    Vendedor anterior = vendedores[i];
                    double venda = vendaDoDia(anterior.getNome(), dia);
                    vendedores[i] = new Vendedor(anterior.getNome(), anterior.getTotalVendido() + venda);
                    System.out.printf("%s: venda do dia R$ %.2f; total R$ %.2f%n",
                            anterior.getNome(), venda, vendedores[i].getTotalVendido());
                }
                InsertionSort.ordenar(vendedores, maiorTotalPrimeiro);
                System.out.println("Ranking atualizado:");
                for (int i = 0; i < vendedores.length; i++) System.out.println((i + 1) + "º - " + vendedores[i]);
            }
            compararEntradas(vendedores, maiorTotalPrimeiro);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static Vendedor[] criarVendedoresDemonstracao() {
        Vendedor[] vendedores = new Vendedor[10];
        for (int i = 0; i < vendedores.length; i++) vendedores[i] = new Vendedor(Dados.nome(i), 0);
        return vendedores;
    }

    static double vendaDoDia(String nome, int dia) {
        int base = Math.abs(nome.hashCode() % 500);
        return 100 + ((base * (dia + 3) + dia * 173) % 900) + dia * 0.5;
    }

    private static void compararEntradas(Vendedor[] ordenados, Comparator<Vendedor> criterio) {
        Vendedor[] embaralhados = new Vendedor[ordenados.length];
        for (int i = 0; i < ordenados.length; i++) embaralhados[i] = ordenados[(i * 7) % ordenados.length];
        contarComparacoes("ranking já ordenado", ordenados, criterio);
        contarComparacoes("ranking em permutação fixa", embaralhados, criterio);
        System.out.println("Contagens são chamadas ao Comparator, não contagens de deslocamentos.");
    }

    private static void contarComparacoes(String nome, Vendedor[] valores, Comparator<Vendedor> criterio) {
        int[] chamadas = {0};
        InsertionSort.ordenar(valores, (a, b) -> {
            chamadas[0]++;
            return criterio.compare(a, b);
        });
        System.out.println(nome + ": " + chamadas[0] + " comparações observadas.");
    }
}
