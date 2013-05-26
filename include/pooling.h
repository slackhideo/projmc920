/* pooling.h */

#ifndef __POOLING_H__
#define __POOLING_H__

/* Função para fazer pooling de imagens */
ImagePGM *pooling(ImagePGM *img, int strideX, int strideY, AdjRel *ar, double (*f)(double *, int));
double max(double *valList, int n);
double min(double *valList, int n);
double mean(double *valList, int n);
double norm2(double *valList, int n);

#endif /* __POOLING_H__ */
