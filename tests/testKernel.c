/* testKernel.c
 *
 * Testa leitura de kernels */

#include "projlib.h"

int main(void) {
    Kernel *k;

    k = readKernel("kernelBandas");

    printf("%d %d %d %d %.1lf\n", k->ar->n, k->depth, k->ar->adj[2].dx,
            k->ar->adj[2].dy, k->w[3][1]);

    return EXIT_SUCCESS;
}
