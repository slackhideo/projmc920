/*
 * adjacency.c
 * Contém funções que operam com adjacências
 */

#include "common.h"
#include "adjacency.h"

/* Cria uma nova relação de adjacência
 *
 * n: número de pixels adjacentes */
AdjRel *newAdjRel(int n) {
    AdjRel *new;

    new = palloc(1, sizeof(AdjRel), false, "newAdjRel");
    new->n = n;
    new->adj = palloc(n, sizeof(AdjSpel), false, "newAdjRel");

    return new;
}


/* Apaga uma relação de adjacência
 *
 * ar: relação de adjacência*/
void delAdjRel(AdjRel **ar) {
    AdjRel *tmp;

    tmp = *ar;

    if(tmp != NULL) {
        free(tmp->adj);
        free(tmp);
        *ar = NULL;
    }
}
