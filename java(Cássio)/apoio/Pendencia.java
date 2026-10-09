package apoio;

public class Pendencia {

    public static boolean reconhecida(UnsupportedOperationException excecao) {
        return excecao.getMessage() != null && excecao.getMessage().startsWith("TODO:");
    }

    public static void mostrar(UnsupportedOperationException excecao) {
        if (!reconhecida(excecao)) {
            throw excecao;
        }
        System.out.println("[PENDENTE] " + excecao.getMessage());
    }
}
