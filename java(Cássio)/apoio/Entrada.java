package apoio;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.Scanner;

public class Entrada {

    private final Scanner scanner;

    public Entrada(Scanner scanner) {
        this.scanner = scanner;
    }

    public String texto(String mensagem) {
        while (true) {
            System.out.print(mensagem);
            if (!scanner.hasNextLine()) {
                throw new FimEntrada();
            }
            String valor = scanner.nextLine().trim();
            if (!valor.isEmpty()) {
                return valor;
            }
            System.out.println("Digite um valor não vazio.");
        }
    }

    public int inteiro(String mensagem, int minimo, int maximo) {
        while (true) {
            try {
                int valor = Integer.parseInt(texto(mensagem));
                if (valor >= minimo && valor <= maximo) {
                    return valor;
                }
            } catch (NumberFormatException excecao) {
                // Solicitar novamente apenas quando a entrada não é um inteiro.
            }
            System.out.println("Digite um inteiro entre " + minimo + " e " + maximo + ".");
        }
    }

    public double decimal(String mensagem, double minimo, double maximo) {
        while (true) {
            try {
                double valor = Double.parseDouble(texto(mensagem).replace(',', '.'));
                if (Double.isFinite(valor) && valor >= minimo && valor <= maximo) {
                    return valor;
                }
            } catch (NumberFormatException excecao) {
                // Aceita ponto ou vírgula como separador decimal, sem milhar.
            }
            System.out.println("Digite um número finito entre " + minimo + " e " + maximo + ".");
        }
    }

    public String horario(String mensagem) {
        DateTimeFormatter formato = DateTimeFormatter.ofPattern("HH:mm")
                .withResolverStyle(ResolverStyle.STRICT);
        while (true) {
            String valor = texto(mensagem);
            try {
                return LocalTime.parse(valor, formato).format(formato);
            } catch (DateTimeParseException excecao) {
                System.out.println("Use um horário válido no formato HH:mm (exemplo: 08:05).");
            }
        }
    }

    public String cpf(String mensagem) {
        while (true) {
            try {
                return Validacao.cpf(texto(mensagem));
            } catch (IllegalArgumentException excecao) {
                System.out.println(excecao.getMessage());
            }
        }
    }

    public static void executar(Runnable aplicacao) {
        try {
            aplicacao.run();
        } catch (FimEntrada excecao) {
            System.out.println("\nEntrada encerrada. Programa finalizado.");
        }
    }

    private static class FimEntrada extends RuntimeException {
        private static final long serialVersionUID = 1L;
    }
}
