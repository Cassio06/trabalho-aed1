package apoio;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;

public class Testes {

    private int sucesso;
    private int pendentes;
    private int falhas;

    public void executar(String nome, Runnable caso) {
        try {
            caso.run();
            sucesso++;
            System.out.println("[OK] " + nome);
        } catch (UnsupportedOperationException excecao) {
            if (Pendencia.reconhecida(excecao)) {
                pendentes++;
                System.out.println("[PENDENTE] " + nome + " - " + excecao.getMessage());
            } else {
                falhas++;
                System.out.println("[FALHOU] " + nome + " - " + excecao);
                excecao.printStackTrace(System.out);
            }
        } catch (AssertionError | RuntimeException erro) {
            falhas++;
            System.out.println("[FALHOU] " + nome + " - " + erro);
            erro.printStackTrace(System.out);
        }
    }

    public void concluir() {
        System.out.println("Resumo: " + sucesso + " OK, " + pendentes + " pendentes, " + falhas + " falhas.");
        if (falhas > 0) {
            throw new AssertionError("Há falhas reais nos testes.");
        }
    }

    public static void verificar(boolean condicao, String mensagem) {
        if (!condicao) {
            throw new AssertionError(mensagem);
        }
    }

    public static void rejeita(Runnable acao) {
        try {
            acao.run();
        } catch (IllegalArgumentException excecao) {
            return;
        }
        throw new AssertionError("Esperado IllegalArgumentException para valor inválido.");
    }

    public static String saida(Runnable acao) {
        PrintStream original = System.out;
        ByteArrayOutputStream buffer = new ByteArrayOutputStream();
        try (PrintStream captura = new PrintStream(buffer, true, StandardCharsets.UTF_8)) {
            System.setOut(captura);
            acao.run();
        } finally {
            System.setOut(original);
        }
        return buffer.toString(StandardCharsets.UTF_8).replace("\r\n", "\n");
    }

    public static void saidaEsperada(String esperado, Runnable acao) {
        String atual = saida(acao).trim();
        verificar(esperado.equals(atual), "Esperado [" + esperado + "]; obtido [" + atual + "]");
    }
}
