/*
 * image.c
 * Contém funções relacionadas a imagens
 */

#include "common.h"
#include <limits.h>
#include <string.h>
#include "image.h"

/* Cria uma nova imagem PGM */
ImagePGM *newImage(int width, int height, int depth, int maxVal) {
    ImagePGM *new;
    
    new = palloc(1, sizeof(ImagePGM), false, "newImage");

    /* Configura as propriedades da imagem */
    new->width = width;
    new->height = height;
    new->depth = depth;
    new->numEls = width * height;
    new->maxVal = maxVal;
    new->vals = palloc(width * height, sizeof(int), false, "newImage");

    new->lower = INT_MAX;
    new->higher = 0;

    return new;
}


/* Apaga uma imagem PGM */
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
ImagePGM *readImage(char *path) {
    char magicNumber[5], buffer[256];
    uchar *vals;
    int width, height, maxVal, i, n, lower = INT_MAX, higher = 0;
    FILE *fp;
    ImagePGM *img = NULL;

    /* Abre o arquivo de imagem */
    fp = fopen(path, "rb");
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
        img = newImage(width, height, 1, maxVal);

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

        vals = palloc(n, sizeof(uchar), false, "readImage");

        /* Lê os brilhos dos pixels da imagem */
        fread(vals, sizeof(uchar), n, fp);

        fclose(fp);

        /* Cria uma nova imagem na representação interna */
        img = newImage(width, height, 1, maxVal);

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
        fprintf(stderr, _("A imagem de entrada deve ser P2 ou P5\n"));
        exit(EXIT_FAILURE);
    }

    return img;
}


/* Escreve uma imagem PGM */
void writeImage(ImagePGM *img, char *path) {
    FILE *fp;
    int i, j;

    /* Abre o arquivo de imagem para escrita */
    fp = fopen(path, "wb");
    if(fp == NULL) {
        errorMsg(OPEN, "writeImage");
    }

    /* Escreve o cabeçalho da imagem no arquivo */
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "%d\n", img->higher - img->lower);

    /* Escreve o conteúdo da imagem no arquivo */
    for(i = 0; i < img->height; i++) {
        for(j = 0; j < img->width; j++) {
            fprintf(fp, "%d ", img->vals[i*img->width + j] - img->lower);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

