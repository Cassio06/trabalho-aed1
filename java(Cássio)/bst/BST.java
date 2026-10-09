package bst;

/** Busca/remoção ausentes retornam null; inserir chave repetida atualiza seu valor.
 * Listagens imprimem um valor por linha; árvore vazia não imprime valores. */
public class BST<K extends Comparable<K>, V> {

    public void inserir(K chave, V valor) {
        // TODO: inserir a chave e o valor na árvore.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public V buscar(K chave) {
        // TODO: buscar o valor associado à chave.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public V remover(K chave) {
        // TODO: remover a chave e devolver o valor removido.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    public void listarEmOrdem() {
        // TODO: exibir os valores seguindo a ordem das chaves.
        throw new UnsupportedOperationException("TODO: implementar por Cássio");
    }

    /** Usado com chaves String normalizadas; prefixo vazio lista todos. */
    public void listarPorPrefixo(String prefixo) {
        // TODO: realizar percurso limitado da BST e exibir somente os valores do prefixo, em ordem.
        throw new UnsupportedOperationException("TODO: implementar BST.listarPorPrefixo por Cássio");
    }
}
