/*
 * image.c
 * Contém funções relacionadas a imagens
 */

#include "common.h"
#include <limits.h>
#include <string.h>
#include "image.h"

/* Cria uma nova imagem PGM
 *
 * width:  largura da nova imagem
 * height: altura da nova imagem
 * depth:  número de bandas (profundidade) da nova imagem */
ImagePGM *newImage(int width, int height, int depth) {
    ImagePGM *new;
    
    new = palloc(1, sizeof(ImagePGM), false, "newImage");

    /* Configura as propriedades da imagem */
    new->width = width;
    new->height = height;
    new->depth = depth;
    new->numEls = width * height;
    new->vals = palloc(depth * width * height, sizeof(double), false,
            "newImage");

    new->lower = INT_MAX;
    new->higher = 0;

    return new;
}


/* Apaga uma imagem PGM
 *
 * img: imagem a ser apagada */
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


/* Lê uma imagem PGM
 *
 * path: caminho do arquivo de imagem */
ImagePGM *readImage(char *path) {
    char magicNumber[5], buffer[256];
    uchar *vals;
    int width, height, i, n, lower = INT_MAX, higher = 0;
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

        /* Obtém a largura e a altura da imagem */
        sscanf(buffer, "%d %d\n", &width, &height);
        fgets(buffer, 255, fp);

        /* Cria uma nova imagem na representação interna */
        img = newImage(width, height, 1);

        /* Lê os brilhos dos pixels da imagem */
        n = width * height;
        for(i = 0; i < n; i++) {
            fscanf(fp, "%lf", &(img->vals[i]));

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

        /* Obtém a largura e a altura da imagem */
        sscanf(buffer, "%d %d\n", &width, &height);
        fgets(buffer, 255, fp);

        n = width * height;
        fgetc(fp);

        vals = palloc(n, sizeof(uchar), false, "readImage");

        /* Lê os brilhos dos pixels da imagem */
        fread(vals, sizeof(uchar), n, fp);

        fclose(fp);

        /* Cria uma nova imagem na representação interna */
        img = newImage(width, height, 1);

        /* Passa os valores dos brilhos dos pixels para a estrutura da imagem */
        for(i = 0; i < n; i++) {
            img->vals[i] = (double)vals[i];

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


/* Escreve uma imagem PGM
 *
 * path: caminho onde será salva a imagem */
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
    fprintf(fp, "%d\n", (int)round(img->higher - img->lower));

    /* Escreve o conteúdo da imagem no arquivo */
    for(i = 0; i < img->height; i++) {
        for(j = 0; j < img->width; j++) {
            fprintf(fp, "%d ", (int)round(img->vals[i*img->width + j]
                        - img->lower));
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


/* Encontra o menor e o maior valor de brilho da imagem
 *
 * img: imagem de interesse */
void findLowerHigher(ImagePGM *img) {
    double lower = INT_MAX, higher = 0;
    int i;

    for(i = 0; i < img->numEls; i++) {
        if(img->vals[i] < lower) {
            lower = img->vals[i];
        }
        if(img->vals[i] > higher) {
            higher = img->vals[i];
        }
    }

    img->lower = lower;
    img->higher = higher;
}


/* Adiciona novas bandas à imagem
 *
 * img:       imagem que terá bandas adicionandas
 * addLayers: número de bandas a serem adicionadas
 * vals:      vetor de valores a serem copiados para as novas bandas
 *            (deve ser do tamanho (addLayers * img->numEls) */
void addNewLayer(ImagePGM *img, int addLayers, double *vals) {
    int i, j;

    /* Altera o tamanho do vetor de brilhos da imagem */
    img->vals = realloc(img->vals, (img->depth + addLayers) *
            img->width * img->height * sizeof(double));

    if(img->vals == NULL) {
        errorMsg(MEM, "addNewLayer");
    }

    /* Copia os novos valores para a imagem */
    for(i = 0; i < addLayers * img->numEls; i++) {
        j = img->depth * img->numEls + i;
        img->vals[j] = vals[i];
    }
    
    /* Atualiza a profundidade da imagem */
    img->depth = img->depth + addLayers;

    return;
}
