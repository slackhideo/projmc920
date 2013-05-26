/* testReadWrite.c
 *
 * Testa funções de ler e escrever imagens */

#include "projlib.h"

int main(void) {
    ImagePGM *img;

    img = readImage("flower.pgm");

    writeImage(img, "flower_out.pgm", 1);

    return EXIT_SUCCESS;
}
