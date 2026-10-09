package avl;

/** Busca/remoção ausentes retornam null; chave repetida atualiza valor.
 * Altura em nós: vazia = 0, folha = 1. Fator = altura esquerda - altura direita. */
public class AVL<K extends Comparable<K>, V> {

    public void inserir(K chave, V valor) {
        // TODO: inserir a chave e manter a árvore balanceada.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public V buscar(K chave) {
        // TODO: buscar o valor associado à chave.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public V remover(K chave) {
        // TODO: remover a chave e manter a árvore balanceada.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public int altura() {
        // TODO: devolver a altura atual da árvore.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public int fatorBalanceamento() {
        // TODO: devolver o fator de balanceamento da raiz.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public boolean estaBalanceada() {
        // TODO: verificar altura e fator de balanceamento em TODOS os nós, não só na raiz.
        throw new UnsupportedOperationException("TODO: implementar AVL.estaBalanceada por Cássio");
    }

    /** Exibe até quantidade valores, um por linha, em ordem decrescente das chaves. */
    public void listarMaiores(int quantidade) {
        // TODO: percorrer a AVL em ordem decrescente, limitando a quantidade (zero não imprime).
        throw new UnsupportedOperationException("TODO: implementar AVL.listarMaiores por Cássio");
    }
}
