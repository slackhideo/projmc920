/*
 * adjacency.c
 * Contém funções que operam com adjacências
 */

#include "common.h"
#include "adjacency.h"

/* Cria uma nova relação de adjacência
 * n: número de pixels adjacentes */
AdjRel *newAdjRel(int n) {
    AdjRel *new;

    new = malloc(sizeof(AdjRel));
    new->n = n;
    new->adj = malloc(n * sizeof(AdjSpel));

    return new;
}
