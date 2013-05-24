/*testReadKernels.c
 *Testa a aleatoriedade dos kernels gerados por "readKernels()"*/

#include "projlib.h"

int main (void) {
    Kernel ** kerns;
    AdjRel * a;
    int x, y;
    int i, j, k;

    a = newAdjRel(9);
    
    i = 0;
    for (x = -1; x <= 1; x++) {
        for (y = -1; y <= 1; y++) {
            a->adj[i].dx = x;
            a->adj[i].dy = y;
            i++;
        }
    }

    kerns = randKernels (5, 3, a);
     
    printf ("\nPesos: "); 
    for (i = 0; i < 5; i++) {
        printf ("\nKernel %d: ", i);
        for (j = 0; j < 3; j++) {
            printf ("\nCamada %d: ", j);
            for (k = 0; k < 9; k++) {
                printf("%lf ", kerns[i]->w[k][j]);
            }
            printf ("\n");
        }
    }

    return 0;
}
