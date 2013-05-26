/* testFilter.c
 *
 * Testa filtragem linear */

#include "projlib.h"

int main(void) {
    ImagePGM *img, *out;
    Kernel *k;

    img = readImage("flower.pgm");

    k = readKernelText("kernelSharp");

    out = correlate(img, k);

    writeImage(out, "filter_out.pgm", 1);

    return EXIT_SUCCESS;
}
