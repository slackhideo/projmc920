/* testNormalization.c
 *
 * Testa funcionalidade da normalização */

#include "projlib.h"

int main() {
    AdjRel *ar;
    ImagePGM *img, *imgSaida;

    ar = readAdjRel("adjRel");

    img = readImage("flower.pgm");
    
    imgSaida = normalization(img, ar);
    
    writeImage(imgSaida, "flower_out_normalization.pgm", 255);
    
    return EXIT_SUCCESS;
}
