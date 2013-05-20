/* image.h */

#ifndef __IMAGE_H__
#define __IMAGE_H__

/* Estrutura para imagens PGM (níveis de cinza)
 *
 * width:  largura da imagem
 * height: altura da imagem
 * depth:  número de bandas (profundidade)
 * numEls: quantidade de pixels
 * maxVal: brilho máximo dos pixels
 * vals:   vetor de brilhos da imagem
 * lower:  menor brilho dos pixels
 * higher: maior brilho dos pixels */
typedef struct {
    int width;
    int height;
    int depth;
    int numEls;
    int maxVal;
    int *vals;
    int lower;
    int higher;
} ImagePGM;


/* Funções que operam com imagens PGM */

/* Função que cria uma nova imagem */
ImagePGM *newImage(int width, int height, int depth, int maxVal);

/* Função que apaga uma imagem */
void delImage(ImagePGM **img);

/* Função que lê uma imagem */
ImagePGM *readImage(char *imgPath);

/* Função que escreve uma imagem */
void writeImage(ImagePGM *img, char *path);

#endif /* __IMAGE_H__ */
