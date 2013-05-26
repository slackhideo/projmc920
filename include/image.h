/* image.h */

#ifndef __IMAGE_H__
#define __IMAGE_H__

/* Estrutura para imagens PGM (níveis de cinza)
 *
 * width:  largura da imagem
 * height: altura da imagem
 * depth:  número de bandas (profundidade)
 * numEls: quantidade de pixels por banda
 * vals:   vetor de brilhos da imagem
 * lower:  menor brilho dos pixels
 * higher: maior brilho dos pixels */
typedef struct {
    int width;
    int height;
    int depth;
    int numEls;
    double *vals;
    double lower;
    double higher;
} ImagePGM;


/* Funções que operam com imagens PGM */

/* Função que cria uma nova imagem */
ImagePGM *newImage(int width, int height, int depth);

/* Função que apaga uma imagem */
void delImage(ImagePGM **img);

/* Função que lê uma imagem */
ImagePGM *readImage(char *imgPath);

/* Função que escreve uma imagem em arquivo */
void writeImage(ImagePGM *img, char *path, int factor);

/* Função que encontra o menor e o maior valor de brilho da imagem */
void findLowerHigher(ImagePGM *img);

/* Função que adiciona novas bandas à imagem */
void addNewLayer(ImagePGM *img, int addLayers, double *vals);

/* Função que escreve um vetor de atributos em arquivo */
void writeAttribVector(ImagePGM *img, char *path);

#endif /* __IMAGE_H__ */
