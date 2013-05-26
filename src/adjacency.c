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
 * ar: relação de adjacência a ser apagada */
void delAdjRel(AdjRel **ar) {
    AdjRel *tmp;

    tmp = *ar;

    if(tmp != NULL) {
        free(tmp->adj);
        free(tmp);
        *ar = NULL;
    }
}


/* Lê uma relação de adjacência de um arquivo
 *
 * path: caminho do arquivo contendo a relação de adjacência */
AdjRel *readAdjRel(char *path) {
    FILE *fp;
    AdjRel *ar;
    int n, i;

    /* Abre o arquivo de relação de adjacências */
    fp = fopen(path, "r");
    if(fp == NULL) {
        errorMsg(OPEN, "readAdjRel");
    }

    /* Lê quantidade de adjacentes */
    fscanf(fp, "%d", &n);

    ar = newAdjRel(n);

    /* Lê os elementos adjacentes */
    for(i = 0; i < n; i++) {
        fscanf(fp, "%d %d", &ar->adj[i].dx, &ar->adj[i].dy);
    }

    fclose(fp);

    return ar;
}
