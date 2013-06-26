/* deeplearning.c
 *
 * Execução do projeto de aprendizado de características em profundidade */

/* Parâmetros */
#define N_LEVELS 3 /* Número de níveis de operações */
#define L1 1
#define L2 32 //64
#define L3 64 //128
#define L4 128 //256

#define STRIDEX 2
#define STRIDEY 2

#define FILENAME_LEN 20

#include "projlib.h"

int main(int argc, char *argv[]) {
    ImagePGM *img, *in, *tmp, *imgFilter, *imgPool, *imgNorm;
    AdjRel *ar, **arlist;
    Kernel **karray;
    int parray[N_LEVELS+1];
    int i, j, k;
    char * imgClass;
    char vectorFileName[FILENAME_LEN], tmpStr[FILENAME_LEN];

    if(argc < 4) {
        printf("Erro! Uso: deeplearning <imagem> <gerar_kernels?> \
<arquivo_de_kernels>\n");
        printf("<gerar_kernels?>: 0 não gera, 1 gera\n");
        printf("<arquivo_de_kernels>: se <gerar_kernels?> for 0, é o arquivo \
de onde serão lidos os kernels; se <gerar_kernels?> for 1, é o arquivo onde \
serão salvos os kernels\n");
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
    
    imgClass = img->imgClass;
    
    ar = arlist[0];

    in = normalization(img, ar);
    /* Fim de L0 */

    /* Realiza as operações de cada nível L(i+1) */
    for(i = 0; i < N_LEVELS; i++) {

        /* Relação de adjacência a ser utilizada */
        ar = arlist[i];

        /* Gera os kernels (neurônios) aleatoriamente para o nível atual */
        if(atoi (argv[2]) == 0) {
            karray = readKernelsBinary(argv[3]);
        }
        else if(atoi (argv[2]) == 1) {
            randKernelsFile(parray[i+1], parray[i], ar, argv[3]);
            karray = readKernelsBinary(argv[3]);
        }
        else {
            printf("Erro! Parâmetro <gerar_kernels?> inválido\n");
            exit(EXIT_FAILURE);
        }

        /* Cria imagem para armazenar o resultado das filtragens */
        imgFilter = newImage(in->width, in->height, parray[i+1], imgClass);

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

    /* Salva o vetor de atributos resultante em uma pasta separada. */
    writeAttribVector(imgNorm, argv[4]);

    return EXIT_SUCCESS;
}
