/* testAdjRel.c
 *
 * Testa leitura de relações de adjacência */

#include "projlib.h"

int main(void) {
    AdjRel *ar;

    ar = readAdjRel("adjRel");

    printf("%d %d %d\n", ar->n, ar->adj[6].dx, ar->adj[6].dy);

    return EXIT_SUCCESS;
}
