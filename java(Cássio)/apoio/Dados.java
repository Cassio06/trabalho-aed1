package apoio;

public class Dados {

    private static final String[] NOMES = {
            "Ana Lima", "Bruno Costa", "Carla Alves", "Daniel Rocha", "Elisa Sousa",
            "Fabio Santos", "Gabriela Nunes", "Heitor Melo", "Isabela Dias", "Joao Silva",
            "Karen Ribeiro", "Lucas Martins", "Marina Barros", "Nicolas Freitas", "Olivia Gomes",
            "Paulo Araujo", "Rafaela Torres", "Samuel Pinto", "Tais Carvalho", "Victor Braga",
            "Alice Teixeira", "Bernardo Castro", "Camila Fernandes", "Diego Moura", "Eduarda Lopes",
            "Felipe Correia", "Giovana Cardoso", "Henrique Vieira", "Iara Mendes", "Julio Farias"
    };

    public static String nome(int indice) {
        return NOMES[indice % NOMES.length];
    }
}
