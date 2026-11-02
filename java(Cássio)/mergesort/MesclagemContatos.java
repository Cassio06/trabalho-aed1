package mergesort;

import apoio.Dados;
import apoio.Pendencia;
import java.util.Locale;

public class MesclagemContatos {

    public static void main(String[] args) {
        Contato[] primeiraLista = criarLista("A", 20);
        Contato[] segundaLista = criarLista("B", 20);
        exibir("Departamento A (já ordenado)", primeiraLista);
        exibir("Departamento B (já ordenado)", segundaLista);
        System.out.println("Critério: nome sem distinguir caixa. Empates mantêm o contato de A.");
        try {
            Contato[] contatos = MergeSort.mesclarContatos(primeiraLista, segundaLista);
            exibir("Contatos mesclados sem duplicatas", contatos);
            System.out.println("Total resultante: " + contatos.length + " (esperado nesta base: 30).");
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
        }
    }

    static Contato[] criarLista(String identificador, int quantidade) {
        if (quantidade != 20 || !(identificador.equals("A") || identificador.equals("B"))) {
            throw new IllegalArgumentException("Demonstração usa departamentos A/B com 20 contatos cada.");
        }
        Contato[] contatos = new Contato[quantidade];
        for (int i = 0; i < contatos.length; i++) {
            int indice = identificador.equals("A") ? i : (i < 10 ? 20 + i : i);
            String nome = Dados.nome(indice);
            contatos[i] = new Contato(nome, nome.toLowerCase(Locale.ROOT).replace(' ', '.') + "@exemplo.com");
        }
        return contatos;
    }

    private static void exibir(String titulo, Contato[] contatos) {
        System.out.println("\n" + titulo + " (" + contatos.length + "):");
        for (Contato contato : contatos) System.out.println(contato);
    }
}
