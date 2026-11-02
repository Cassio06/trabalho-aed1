#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

mkdir -p out
mapfile -d '' fontes < <(find 'java(Cássio)' -name '*.java' -print0)
javac -encoding UTF-8 --release 17 -Xlint:all -d out "${fontes[@]}"

falhas=0
for teste in apoio.TesteApoio fila.TesteFila bubblesort.TesteBubbleSort \
             insertionsort.TesteInsertionSort bst.TesteBST mergesort.TesteMergeSort avl.TesteAVL; do
    printf '\nExecutando %s\n' "$teste"
    if ! java -cp out "$teste"; then
        falhas=1
    fi
done

if (( falhas > 0 )); then
    echo 'Verificação terminou com falhas reais. Consulte os casos [FALHOU].'
else
    echo 'Sem falhas reais nas verificações executadas; [PENDENTE] não significa algoritmo aprovado.'
fi
exit "$falhas"
