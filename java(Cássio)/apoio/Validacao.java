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
        String entrada = texto(valor, "CPF");
        String cpf;
        if (entrada.matches("[0-9]{11}")) {
            cpf = entrada;
        } else if (entrada.matches("[0-9]{3}\\.[0-9]{3}\\.[0-9]{3}-[0-9]{2}")) {
            cpf = entrada.replace(".", "").replace("-", "");
        } else {
            throw new IllegalArgumentException(
                    "CPF deve conter 11 dígitos, sem pontuação ou no formato 000.000.000-00."
            );
        }
        // Valida apenas a sintaxe; CPFs fictícios não têm dígitos verificadores conferidos.
        return cpf.substring(0, 3) + "." + cpf.substring(3, 6) + "."
                + cpf.substring(6, 9) + "-" + cpf.substring(9);
    }
}
