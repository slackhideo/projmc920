/*
 * filter.c
 * Contém funções relacionadas à filtragem linear
 */

#include "common.h"
#include "image.h"
#include "adjacency.h"
#include "kernel.h"
#include "filter.h"

/* Correlaciona uma imagem com um kernel (filtro)
 *
 * img: imagem de entrada
 * k:   kernel a ser utilizado */
ImagePGM *correlate(ImagePGM *img, Kernel *k) {
    ImagePGM *out;
    int p, xp, yp;
    int q, xq, yq;
    int i, j;
    double val;

    /* Cria imagem de saída */
    out = newImage(img->width, img->height, 1);

    /* Percorre a imagem com o kernel */
    for(yp = 0; yp < img->height; yp++) {
        for(xp = 0; xp < img->width; xp++) {
            p = xp + yp * out->width;
            val = 0.0;

            /* Para todo adjacente q de p, calcula a somatória da
             * multiplicação entre o brilho da imagem e o peso do adjacente */
            for(i = 0; i < k->ar->n; i++) {
                xq = xp + k->ar->adj[i].dx;
                yq = yp + k->ar->adj[i].dy;

                if((xq >= 0) && (xq < img->width) &&
                   (yq >= 0) && (yq < img->height)) {

                    /* Multiplica em todas as bandas da imagem */
                    for(j = 0; j < img->depth; j++) {
                        q = (xq + yq * img->width) + (j * img->numEls);
                        val += img->vals[q] * k->w[i][j];
                    }
                }
            }

            /* Coloca o valor do brilho na imagem, segundo a função de
             * ativação */
            out->vals[p] = activationFunction(val);
        }
    }

    /* Atualiza os brilhos mínimo e máximo da imagem */
    findLowerHigher(out);

    return out;
}


/* Função de ativação
 * (considera apenas os valores não negativos de brilho)
 *
 * val: valor de brilho considerado */
double activationFunction(double val) {
    if(val < 0) {
        return 0;
    }
    else {
        return val;
    }
}
