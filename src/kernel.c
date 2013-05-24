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
    int na, nl;
    int i, j;

    /* Abre o arquivo de kernel */
    fp = fopen(path, "r");
    if(fp == NULL) {
        errorMsg(OPEN, "readKernel");
    }

    /* Lê a quantidade de adjacentes por banda e de bandas */
    fscanf(fp, "%d %d", &na, &nl);

    ar = newAdjRel(na);
    new = newKernel(nl, ar);

    /* Lê os elementos adjacentes */
    for(i = 0; i < na; i++) {
        for(j = 0; j < nl; j++) {
            fscanf(fp, "%d %d %lf",
                    &new->ar->adj[i].dx, &new->ar->adj[i].dy, &new->w[i][j]);
        }
    }

    fclose(fp);

    delAdjRel(&ar);

    return new;
}


/* Reflete um kernel
 *
 * k: kernel a ser refletido */
Kernel *reflectKernel(Kernel *k) {
    Kernel *new;
    int na;
    int i;

    new = newKernel(k->depth, k->ar);
    na = k->ar->n;

    for(i = 0; i < na; i++) {
        new->ar->adj[i].dx = -k->ar->adj[i].dx;
        new->ar->adj[i].dy = -k->ar->adj[i].dy;
        new->w[i] = k->w[i];
    }

    return new;
}

/*Cria novos kernels, em uma distribuição com média 0 e desvio padrão 1.
  numKernels: Quantidade de kernels a serem criados.
  depth: Número de bandas dos kernels.
  adjacency: Relação de adjacência (2D) do kernel.
  Retorna vetor (alocado dinamicamente) com apontadores para os kernels gerados.
*/
Kernel ** randKernels (int numKernels, int depth, AdjRel * adjacency) {
    //Peso gerado aleatoriamente.
    double rand_weight;
    //Variáveis para percorrer a adjacência e as camadas.
    int layer, adjSpel;
    //Kernel gerado aleatoriamente.
    Kernel * k;
    //Vetor de kernels.
    Kernel ** kerns;
    //Média e norma dos pesos de um kernel.
    double average;
    double norm;
    //Auxiliares.
    int i, j;

    //Aloca memória para o vetor de kernels resultantes.
    kerns = palloc (numKernels, sizeof (Kernel *), false, "randKernels");

    //Inicializa semente da função "rand()".
    srand(time(NULL));

    //Loop para conseguir todos os kernels.
    for (i = 0; i < numKernels; i++) {
        //Inicializa um novo kernel, começando da primeira banda (layer) 
        //e do primeiro spel adjacente.
        k = newKernel(depth, adjacency);
        layer = 0;
        adjSpel = 0;
        for (j = 0; j < (adjacency->n * depth); j++) {
            //Obtém número aleatório entre 0 e 1 com distribuição uniforme.
            rand_weight = ((double) rand()) / RAND_MAX;
            
            //Atribui esse número a um dos pesos do kernel.
            k->w[adjSpel][layer] = rand_weight;

            //Passa para o spel seguinte na adjacência.
            adjSpel++;
            //Passa para a banda seguinte.
            if (adjSpel == adjacency->n) {
                adjSpel = 0;
                layer++;
            }
        }
        //Calcula a média e a norma dos pesos encontrados.
        average = 0.0;
        norm = 0.0;
        layer = 0;
        adjSpel = 0;
        for (j = 0; j < (adjacency->n * depth); j++) {
            average += k->w[adjSpel][layer];
            norm += k->w[adjSpel][layer] * k->w[adjSpel][layer];
            //Passa para o spel seguinte na adjacência.
            adjSpel++;
            //Passa para a banda seguinte.
            if (adjSpel == adjacency->n) {
                adjSpel = 0;
                layer++;
            }
        }
        average = average / (double) ((adjacency->n * depth));
        norm = sqrt (norm);
 
        //Subtrai a média de cada peso (garantindo que a nova média será 0)
        //e divide cada peso pela norma (garantindo que a nova norma será 1).
        layer = 0;
        adjSpel = 0;
        for (j = 0; j < (adjacency->n * depth); j++) {
            k->w[adjSpel][layer] = k->w[adjSpel][layer] - average;
            k->w[adjSpel][layer] = k->w[adjSpel][layer] / norm;    
            //Passa para o spel seguinte na adjacência.
            adjSpel++;
            //Passa para a banda seguinte.
            if (adjSpel == adjacency->n) {
                adjSpel = 0;
                layer++;
            }
        }

        //Adiciona o kernel gerado ao vetor.
        kerns[i] = k;
    }

    return kerns;
}
