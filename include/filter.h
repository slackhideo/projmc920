/* filter.h */

#ifndef __FILTER_H__
#define __FILTER_H__

/* Funções relacionadas à filtragem linear */
ImagePGM *correlate(ImagePGM *img, Kernel *k);

/* Função de ativação */
void activationFunction(ImagePGM *img);

#endif /* __FILTER_H__ */
