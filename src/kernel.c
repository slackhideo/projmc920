/*
 * kernel.c
 * Contém funções que operam com kernels
 */

#include "common.h"
#include "adjacency.h"
#include "kernel.h"

/* Cria um novo kernel
 *
 * depth: número de bandas (profundidade)
 * ar:    relação de adjacência */
Kernel *newKernel(int depth, AdjRel *ar) {
    Kernel *new;
    int i;

    /* Aloca memória para o novo kernel */
    new = palloc(1, sizeof(Kernel), false, "newKernel");
    new->depth = depth;
    new->ar = newAdjRel(ar->n);
    new->w = palloc(ar->n, sizeof(double *), false, "newKernel");
    for(i = 0; i < ar->n; i++) {
        new->w[i] = palloc(depth, sizeof(double), false, "newKernel");
    }

    /* Copia a relação de adjacência */
    for(i = 0; i < ar->n; i++) {
        new->ar->adj[i] = ar->adj[i];
    }

    return new;
}


/* Apaga um kernel
 *
 * k: kernel */
void delKernel(Kernel **k) {
    Kernel *tmp;
    int i;

    tmp = *k;

    if(tmp != NULL) {
        for(i = 0; i < tmp->ar->n; i++) {
            free(tmp->w[i]);
        }
        free(tmp->w);
        delAdjRel(&tmp->ar);
        free(tmp);
        *k = NULL;
    }
}


/* Lê um kernel de um arquivo 
 *
 * path: caminho do arquivo contendo o kernel */
Kernel *readKernel(char *path) {
    FILE *fp;
    AdjRel *ar;
    Kernel *new;
    int na, nb;
    int i, j;

    fp = fopen(path, "r");

    /* Lê a quantidade de adjacentes por banda e de bandas */
    fscanf(fp, "%d %d", &na, &nb);

    ar = newAdjRel(na);
    new = newKernel(nb, ar);

    /* Lê os elementos adjacentes */
    for(i = 0; i < na; i++) {
        for(j = 0; j < nb; j++) {
            fscanf(fp, "%d %d %lf",
                    &new->ar->adj[i].dx, &new->ar->adj[i].dy, &new->w[i][j]);
        }
    }

    fclose(fp);

    delAdjRel(&ar);

    return new;
}
