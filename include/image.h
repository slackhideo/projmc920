/* image.h */

#ifndef __IMAGE_H__
#define __IMAGE_H__

typedef struct {
    int width;
    int height;
    int numEls;
    int maxVal;
    int *vals;
    int lower;
    int higher;
} ImagePGM;

ImagePGM *newImage(int width, int height, int maxVal);
void delImage(ImagePGM **img);
ImagePGM *readImage(char *imgPath);

#endif /* __IMAGE_H__ */
