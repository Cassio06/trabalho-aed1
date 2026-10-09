package mergesort;

import apoio.Validacao;
import java.time.LocalDateTime;
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
        return dataHora + " - R$ " + String.format("%.2f", valor) + " - " + descricao;
    }

    private static double validarValor(double valor) {
        // Saídas bancárias são negativas; somente valores não finitos são rejeitados.
        if (!Double.isFinite(valor)) {
            throw new IllegalArgumentException("Valor da transação deve ser finito.");
        }
        return valor;
    }
}
