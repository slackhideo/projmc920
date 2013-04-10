/*
 * image.c
 * Contém funções relacionadas à imagens
 */

#include "common.h"
#include <limits.h>
#include <string.h>
#include "image.h"

/* Cria uma nova imagem PGM */
ImagePGM *newImage(int width, int height, int maxVal) {
    ImagePGM *new;
    
    new = malloc(sizeof(ImagePGM));

    if(new == NULL) {
        errorMsg(MEM, "newImage");
    }

    /* Configura as propriedades da imagem */
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


/* Destrói uma imagem PGM */
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


/* Lê uma imagem PGM */
ImagePGM *readImage(char *imgPath) {
    char magicNumber[5], buffer[256];
    uchar *vals;
    int width, height, maxVal, i, n, lower = INT_MAX, higher = 0;
    FILE *fp;
    ImagePGM *img = NULL;

    /* Abre o arquivo de imagem */
    fp = fopen(imgPath, "rb");
    if(fp == NULL) {
        errorMsg(OPEN, "readImage");
    }

    /* Lê o número mágico */
    fscanf(fp, "%s\n", magicNumber);

    /* Trata a imagem como sendo P2 (formato texto) */
    if(strcmp(magicNumber, "P2") == 0) {
        fgets(buffer, 255, fp);
        while(buffer[0] == '#') {
            fgets(buffer, 255, fp);
        }

        /* Obtém a largura, altura e o maior brilho da imagem */
        sscanf(buffer, "%d %d\n", &width, &height);
        fgets(buffer, 255, fp);
        sscanf(buffer, "%d\n", &maxVal);

        /* Cria uma nova imagem na representação interna */
        img = newImage(width, height, maxVal);

        /* Lê os brilhos dos pixels da imagem */
        n = width * height;
        for(i = 0; i < n; i++) {
            fscanf(fp, "%d", &(img->vals[i]));

            /* Verifica se é o menor ou maior valor */
            if(img->vals[i] < lower) {
                lower = img->vals[i];
            }
            if(img->vals[i] > higher) {
                higher = img->vals[i];
            }
        }

        fclose(fp);

        img->lower = lower;
        img->higher = higher;
    }

    /* Trata a imagem como sendo P5 (formato binário) */
    else if(strcmp(magicNumber, "P5") == 0) {
        fgets(buffer, 255, fp);
        while(buffer[0] == '#') {
            fgets(buffer, 255, fp);
        }

        /* Obtém a largura, altura e o maior brilho da imagem */
        sscanf(buffer, "%d %d\n", &width, &height);
        fgets(buffer, 255, fp);
        sscanf(buffer, "%d\n", &maxVal);

        n = width * height;
        fgetc(fp);

        vals = allocUCharArray(n, false);

        /* Lê os brilhos dos pixels da imagem */
        fread(vals, sizeof(uchar), n, fp);

        fclose(fp);

        /* Cria uma nova imagem na representação interna */
        img = newImage(width, height, maxVal);

        /* Passa os valores dos brilhos dos pixels para a estrutura da imagem */
        for(i = 0; i < n; i++) {
            img->vals[i] = (int)vals[i];

            /* Verifica se é o menor ou maior valor */
            if(img->vals[i] < lower) {
                lower = img->vals[i];
            }
            if(img->vals[i] > higher) {
                higher = img->vals[i];
            }
        }
        free(vals);

        img->lower = lower;
        img->higher = higher;
    }
    else {
        fprintf(stderr, "A imagem de entrada deve ser P2 ou P5\n");
        exit(EXIT_FAILURE);
    }

    return img;
}

