/* deeplearning.c
 *
 * Execução do projeto de aprendizado de características em profundidade */

/* Parâmetros */
#define N_LEVELS 3 /* Número de níveis de operações */
#define L1 1
#define L2 64
#define L3 128
#define L4 256

#define STRIDEX 2
#define STRIDEY 2

#include "projlib.h"

int main(int argc, char *argv[]) {
    ImagePGM *img, *in, *tmp, *imgFilter, *imgPool, *imgNorm;
    AdjRel *ar, **arlist;
    Kernel **karray;
    int parray[N_LEVELS+1];
    int i, j, k;

    if(argc < 3) {
        printf("Erro! Uso: deeplearning <imagem> <gerar_kernels?>\n");
        printf("<gerar_kernels?>: 0 não gera, 1 gera\n");
        exit(EXIT_FAILURE);
    }

    /* Vetor de parâmetros */
    parray[0] = L1;
    parray[1] = L2;
    parray[2] = L3;
    parray[3] = L4;

    /* Vetor de relações de adjacência */
    arlist = palloc(N_LEVELS, sizeof(AdjRel *), false, "main");

    arlist[0] = readAdjRel("adjs/adj3");
    arlist[1] = readAdjRel("adjs/adj5");
    arlist[2] = readAdjRel("adjs/adj7");

    /* Início de L0 */
    img = readImage(argv[1]);

    ar = arlist[0];

    in = normalization(img, ar);
    /* Fim de L0 */

    /* Realiza as operações de cada nível L(i+1) */
    for(i = 0; i < N_LEVELS; i++) {

        /* Relação de adjacência a ser utilizada */
        ar = arlist[i];

        /* Gera os kernels (neurônios) aleatoriamente para o nível atual */
        if(atoi (argv[2]) == 1) {
            karray = randKernelsMemory(parray[i+1], parray[i], ar);
        }

        /* Cria imagem para armazenar o resultado das filtragens */
        imgFilter = newImage(in->width, in->height, parray[i+1]);

        /* Processo de filtragem */
        for(j = 0; j < parray[i+1]; j++) {
            tmp = correlate(in, karray[j]);

            /* Copia o resultado da filtragem com o kernel atual para a
             * imagem de saída do processo */
            for(k = 0; k < tmp->numEls; k++) {
                imgFilter->vals[j*tmp->numEls + k] = tmp->vals[k];
            }
        }


        /* Processo de pooling */
        imgPool = pooling(imgFilter, STRIDEX, STRIDEY, ar, norm2);


        /* Processo de normalização */
        imgNorm = normalization(imgPool, ar);
    }

    /* Salva o vetor de atributos resultante */
    writeAttribVector(imgNorm, "vector.out");

    return EXIT_SUCCESS;
}
