// Verificação C11: compilação, simulações do edital e regressões da auditoria.
import { spawnSync } from 'node:child_process';
import { mkdtempSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import path from 'node:path';
import { fileURLToPath } from 'node:url';
import assert from 'node:assert/strict';

const raiz = path.dirname(fileURLToPath(import.meta.url));
process.chdir(raiz);
const indiceCC = process.argv.indexOf('--cc');
const cc = indiceCC < 0 ? (process.env.CC || 'gcc') : process.argv[indiceCC + 1];
if (!cc) throw new Error('Informe o executável após --cc.');
const prefixo = /^zig(?:\.exe)?$/i.test(path.basename(cc)) ? ['cc'] : [];
const pasta = mkdtempSync(path.join(tmpdir(), 'aed1-c-'));
const executaveis = new Map();
let falhas = 0, aprovados = 0;
function testar(nome, acao) {
    try { acao(); aprovados++; console.log(`[OK] ${nome}`); }
    catch (erro) { falhas++; console.error(`[FALHOU] ${nome}: ${erro.message}`); }
}
function compilar(fonte, nome) {
    const exe = path.join(pasta, nome + (process.platform === 'win32' ? '.exe' : ''));
    const r = spawnSync(cc, [...prefixo, '-std=c11', '-Wall', '-Wextra', '-pedantic',
        '-Werror', fonte, '-o', exe], { encoding: 'utf8', timeout: 180000 });
    assert.ifError(r.error);
    assert.equal(r.status, 0, r.stderr || r.stdout);
    return exe;
}
function rodar(nome, entrada) {
    assert.ok(executaveis.has(nome), `Compilação indisponível: ${nome}`);
    const r = spawnSync(executaveis.get(nome), [], {
        input: entrada, encoding: 'utf8', timeout: 10000, maxBuffer: 4 * 1024 * 1024,
    });
    assert.ifError(r.error);
    assert.equal(r.status, 0, `exit=${r.status}\n${r.stderr}\n${r.stdout}`);
    return r.stdout;
}
const simulacoes = [
    ['Pilha/Sistema de Undo.c', 'undo', 7, /ESTADO FINAL DA SIMULACAO/],
    ['Pilha/Verificação de Sistemas.c', 'expressoes', 2, /CORRETA.*INCORRETA/s],
    ['Lista_Encadeada/playlist.c', 'playlist', 8, /56\.91 min/],
    ['Lista_Encadeada/estoque.c', 'estoque', 8, /Dia 7 - Domingo/],
    ['Grafo/Entregas.c', 'entregas', 4, /Custo minimo total: 22 km/],
    ['Grafo/rede_social.c', 'rede', 6, /BFS/],
    ['Tabela_Hash/login.c', 'login', 5, /SUCESSO.*FALHA \(Esperado\)/s],
    ['Tabela_Hash/frequencia.c', 'frequencia', 2, /Total de palavras distintas/],
    ['Selection_Sort/processo_seletivo.c', 'seletivo', 3, /105 comparacoes e 13 trocas/],
    ['Selection_Sort/tarefas.c', 'tarefas', 3, /91 comparacoes e 10 trocas/],
    ['Quick_Sort/ecommerce.c', 'ecommerce', 3, /999 comparacoes, 493 trocas/],
    ['Quick_Sort/competicao.c', 'competicao', 3, /121 comparacoes e 88/],
];
try {
    for (const [fonte, nome, opcao, esperado] of simulacoes) {
        testar(`compilar ${nome} sem avisos`, () => executaveis.set(nome,
            compilar(path.join('c(Lukas)', fonte), nome)));
        testar(`simulacao ${nome}`, () => assert.match(rodar(nome, `${opcao}\n0\n`), esperado));
    }
    testar('compilar testes do contador', () => executaveis.set('teste_frequencia',
        compilar('testes/teste_frequencia.c', 'teste_frequencia')));
    testar('regressoes UTF-8, texto longo e hash', () => {
        const saida = rodar('teste_frequencia', '');
        assert.equal((saida.match(/\[OK\]/g) || []).length, 8);
    });
    testar('Dijkstra: custo de um milhao continua alcancavel', () =>
        assert.match(rodar('entregas', '1\nA\nB\n1000000\n2\nA\nB\n0\n'),
            /Custo minimo total: 1000000 km/));
    testar('Dijkstra: soma acima de INT_MAX nao estoura', () =>
        assert.match(rodar('entregas', '1\nA\nB\n1\n1\nB\nC\n2147483647\n2\nA\nC\n0\n'),
            /Custo minimo total: 2147483648 km/));
    testar('Dijkstra: pontos desconectados nao produzem caminho falso', () =>
        assert.match(rodar('entregas', '1\nA\nB\n2\n1\nC\nD\n3\n2\nA\nD\n0\n'),
            /Nao ha rota disponivel/));
    for (const numero of ['nan', 'inf', '-inf']) {
        const entradas = [
            ['estoque', `1\n1\nTeste\n1\n${numero}\n7\n0\n`, /Preco invalido/],
            ['seletivo', `1\nTeste\n${numero}\n2\n0\n`, /Pontuacao invalida/],
            ['competicao', `1\nTeste\n${numero}\n2\n0\n`, /Tempo invalido/],
            ['ecommerce', `1\nTeste\n${numero}\n2\n0\n`, /Preco invalido/],
            ['playlist', `1\nTeste\nArtista\n${numero}\n3.5\n7\n0\n`, /Valor invalido/],
        ];
        for (const [nome, entrada, esperado] of entradas)
            testar(`${nome}: rejeitar ${numero}`, () => {
                const saida = rodar(nome, entrada);
                assert.match(saida, esperado);
                if (nome === 'playlist') {
                    assert.match(saida, /3\.50 min/);
                    assert.doesNotMatch(saida, /\((?:nan|[-+]?inf) min\)/i);
                }
            });
    }
    testar('ecommerce: popularidade acima de 1000 e rejeitada', () =>
        assert.match(rodar('ecommerce', '1\nTeste\n10\n1001\n0\n'), /Popularidade invalida/));
    testar('contador: simulacao identifica fonte literaria real', () =>
        assert.match(rodar('frequencia', '2\n0\n'), /Dom Casmurro.*Wikisource/s));
    testar('contador: texto real tem contagens conferidas independentemente', () => {
        const saida = rodar('frequencia', '2\n0\n');
        assert.match(saida, /Total de palavras processadas\s*:\s*89/);
        assert.match(saida, /Total de palavras distintas\s*:\s*69/);
        assert.match(saida, /que\s*-> 4 ocorrencia/);
    });
    testar('contador: console le linha acima de 1024 bytes completa', () =>
        assert.match(rodar('frequencia', `1\n${'a '.repeat(3000)}\n0\n`),
            /Total de palavras processadas\s*:\s*3000/));
} finally {
    console.log(`Resumo C: ${aprovados} OK, ${falhas} falhas.`);
    assert.equal(path.dirname(path.resolve(pasta)), path.resolve(tmpdir()),
        'A limpeza deve permanecer na pasta temporária usada pela verificação.');
    rmSync(pasta, { recursive: true, force: true });
}
process.exitCode = falhas ? 1 : 0;
