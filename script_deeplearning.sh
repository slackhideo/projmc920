#!/bin/sh

# script_deeplearning.sh
# última modificação: 26/06/2013

# parâmetros
EXEC=deeplearning
TIME=/bin/time
IMG_BASE_DIR=../projeto1s2013/faces_pubfigs
KERNELS_BASE=kernels
CLASS_START=001
CLASS_END=010
IMG_START=001
IMG_END=010


# verifica a existência do executável
if [ ! -e ${EXEC} ]; then
    echo "Arquivo '${EXEC}' não existe"
    echo "Por favor, compile o projeto"
    exit
fi


# executa o programa para cada imagem de cada classe do intervalo
for i in $(seq -w ${CLASS_START} ${CLASS_END}); do
    for j in $(seq -w ${IMG_START} ${IMG_END}); do
        echo -n "Executando para a imagem ${j} da classe ${i}: "
        ${TIME} -f '%es' ./${EXEC} ${IMG_BASE_DIR}/${i}_${j}.pgm 0 \
            ${KERNELS_BASE} data/vector_${i}_${j}.csv
    done
done
