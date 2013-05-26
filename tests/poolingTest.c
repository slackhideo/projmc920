/* poolingTest.c
 *
 * Testa funcionalidade do pooling */

#include "projlib.h"

int main() {
    int strideX = 2; 
    int strideY = 2;
    AdjRel *ar;
    ImagePGM *img, *imgSaida;

    ar = readAdjRel("adjRel");

    img = readImage("flower.pgm");

    //printf("\nEntre com o stride X: ");
    //scanf("%d", &strideX);
    //printf("\nEntre com o stride Y: ");
    //scanf("%d", &strideY);
    
    imgSaida = pooling(img, strideX, strideY, ar, min);
    
    writeImage(imgSaida, "flower_out_pooling_min.pgm");
    
    imgSaida = pooling(img, strideX, strideY, ar, max);
    
    writeImage(imgSaida, "flower_out_pooling_max.pgm");
    
    imgSaida = pooling(img, strideX, strideY, ar, mean);
    
    writeImage(imgSaida, "flower_out_pooling_mean.pgm");
    
    imgSaida = pooling(img, strideX, strideY, ar, norm2);
    
    writeImage(imgSaida, "flower_out_pooling_norm2.pgm");
    
    return EXIT_SUCCESS;
}
