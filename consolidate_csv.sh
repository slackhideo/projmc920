#!/bin/sh

# consolidate_csv.sh
# última modificação: 26/06/2013

# parâmetros
CSV_BASE_DIR=data
OUT_CSV=vector.csv
CLASS_START=001
CLASS_END=010
IMG_START=001
IMG_END=010


# verifica a existência do diretório de arquivos CSV
if [ ! -d ${CSV_BASE_DIR} ]; then
    echo "Diretório '${CSV_BASE_DIR}' não existe"
    echo "Por favor, execute este script no diretório base do projeto"
    exit
fi


# consolida os arquivos CSV em um único
for i in $(seq -w ${CLASS_START} ${CLASS_END}); do
    for j in $(seq -w ${IMG_START} ${IMG_END}); do
        cat ${CSV_BASE_DIR}/vector_${i}_${j}.csv >> ${OUT_CSV}
    done
done
