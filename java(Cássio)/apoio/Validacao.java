package apoio;

public class Validacao {

    public static String texto(String valor, String campo) {
        if (valor == null || valor.trim().isEmpty()) {
            throw new IllegalArgumentException(campo + " não pode ficar vazio.");
        }
        return valor.trim();
    }

    public static double naoNegativo(double valor, String campo) {
        if (!Double.isFinite(valor) || valor < 0) {
            throw new IllegalArgumentException(campo + " deve ser finito e não negativo.");
        }
        return valor;
    }

    public static int positivo(int valor, String campo) {
        if (valor <= 0) {
            throw new IllegalArgumentException(campo + " deve ser positivo.");
        }
        return valor;
    }

    public static String cpf(String valor) {
        String cpf = texto(valor, "CPF").replace(".", "").replace("-", "");
        // Valida somente o formato. Os CPFs das simulações são fictícios.
        if (!cpf.matches("[0-9]{11}")) {
            throw new IllegalArgumentException("CPF deve conter 11 dígitos, com ou sem pontuação.");
        }
        return cpf.substring(0, 3) + "." + cpf.substring(3, 6) + "."
                + cpf.substring(6, 9) + "-" + cpf.substring(9);
    }
}
