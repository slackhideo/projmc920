/* image.h */

#ifndef __IMAGE_H__
#define __IMAGE_H__

#define INF 0x7FFFFFFF

typedef struct {
    int width;
    int height;
    int numEls;
    int maxVal;
    int *vals;
    int lower;
    int higher;
} ImagePGM;

#endif /* __IMAGE_H__ */
