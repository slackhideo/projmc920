/*
 * image.c
 * Contém funções relacionadas à imagens
 */

#include <limits.h>
#include "common.h"
#include "image.h"

/* Cria uma nova imagem */
ImagePGM *newImage(int width, int height, int maxVal) {
    ImagePGM *new;
    
    new = malloc(sizeof(ImagePGM));

    if(new == NULL) {
        errorMsg(MEM, "newImage");
    }

    new->width = width;
    new->height = height;
    new->numEls = width * height;
    new->maxVal = maxVal;
    new->vals = allocIntArray(width * height, false);

    if(new->vals == NULL) {
        errorMsg(MEM, "newImage");
    }

    new->lower = INT_MAX;
    new->higher = 0;

    return new;
}

/* Destrói uma imagem */
void delImage(ImagePGM **img) {
    ImagePGM *tmp;

    tmp = *img;

    if(tmp != NULL) {
        if(tmp->vals != NULL) {
            free(tmp->vals);
        }
        free(tmp);
        *img = NULL;
    }
}



int main(void) {
    printf("Foi\n");
    return EXIT_SUCCESS;
}
