package mergesort;

import apoio.Validacao;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Locale;
import java.util.Objects;

public class Transacao {

    private final LocalDateTime dataHora;
    private final double valor;
    private final String descricao;

    public Transacao(LocalDateTime dataHora, double valor, String descricao) {
        this.dataHora = Objects.requireNonNull(dataHora, "Data/hora obrigatória");
        this.valor = validarValor(valor);
        this.descricao = Validacao.texto(descricao, "Descrição");
    }

    public LocalDateTime getDataHora() {
        return dataHora;
    }

    public double getValor() {
        return valor;
    }

    public String getDescricao() {
        return descricao;
    }

    @Override
    public String toString() {
        String dataFormatada = dataHora.format(DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm", Locale.forLanguageTag("pt-BR")));
        String valorFormatado = String.format(Locale.forLanguageTag("pt-BR"), "%,.2f", valor);
        return dataFormatada + " - R$ " + valorFormatado + " - " + descricao;
    }

    private static double validarValor(double valor) {
        // Saídas bancárias são negativas; somente valores não finitos são rejeitados.
        if (!Double.isFinite(valor)) {
            throw new IllegalArgumentException("Valor da transação deve ser finito.");
        }
        return valor;
    }
}
