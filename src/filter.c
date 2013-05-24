/*
 * filter.c
 * Contém funções relacionadas à filtragem linear
 */

#include "common.h"
#include <math.h>
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
    int i;
    double val;

    /* Cria imagem de saída */
    out = newImage(img->width, img->height, 1);

    for(yp = 0; yp < img->height; yp++) {
        for(xp = 0; xp < img->width; xp++) {
            p = xp + yp * out->width;
            val = 0.0;

            for(i = 0; i < k->ar->n; i++) {
                xq = xp + k->ar->adj[i].dx;
                yq = yp + k->ar->adj[i].dy;

                if((xq >= 0) && (xq < img->width) &&
                   (yq >= 0) && (yq < img->height)) {
                    q = xq + yq * img->width;
                    val += img->vals[q] * k->w[i][0];
                }
            }

            out->vals[p] = (int)round(val);
        }
    }

    //fazer pegar menor e maior

    return out;
}
