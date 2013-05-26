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
 * k: kernel a ser apagado */
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


/* Lê um kernel de um arquivo em formato texto
 *
 * path: caminho do arquivo em formato texto contendo o kernel */
Kernel *readKernelText(char *path) {
    FILE *fp;
    AdjRel *ar;
    Kernel *new;
    int na, nl;
    int i, j;

    /* Abre o arquivo de kernel */
    fp = fopen(path, "r");
    if(fp == NULL) {
        errorMsg(OPEN, "readKernelText");
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

/* Lê kernels de um arquivo em formato binário.
 *
 * path: Caminho do arquivo em formato binário contendo o kernel. 
 * Retorna vetor (alocado dinamicamente) com apontadores para os
 * kernels lidos.*/
Kernel ** readKernelsBinary(char *path) {
    FILE * kern_file;
    //Kernel gerado aleatoriamente.
    Kernel * k;
    //Adjacência (lida do arquivo).
    AdjRel * adjacency;
    //Quantidade de spels na adjacência.
    int number_adj;
    int numKernels, depth;
    //Variáveis para percorrer a adjacência e as camadas.
    int adjSpel, layer;
    //Vetor de kernels.
    Kernel ** kerns;
    //Auxiliares.
    int i, j;

    //Inicializa o arquivo onde estão armazenados os kernels.
    kern_file = fopen (path, "rb");
    if(kern_file == NULL) {
        errorMsg(OPEN, "readKernelsBinary");
    }

    //Lê cabeçalho com informações importantes: número total de kernels,
    //adjacência e profundidade.
    fread(&numKernels, sizeof(int), 1, kern_file);
    fread(&number_adj, sizeof(int), 1, kern_file);
    adjacency = newAdjRel (number_adj);
    fread(adjacency->adj, sizeof(AdjSpel), number_adj, kern_file);
    fread(&depth, sizeof(int), 1, kern_file);

    //Aloca memória para o vetor de kernels resultantes.
    kerns = palloc (numKernels, sizeof (Kernel *), false, "readKernelsBinary");

    //Atribui os kernels para o vetor de saída, levando em consideração que 
    //os pesos estão armazenados no arquivo seqüencialmente.
    for (i = 0; i < numKernels; i++) {
        k = newKernel (depth, adjacency);

        //Obtém todos os pesos do kernel atual.
        layer = 0;
        adjSpel = 0;
        for (j = 0; j < (adjacency->n * depth); j++) {
            //Lê um peso.
            fread (&(k->w[adjSpel][layer]), sizeof(double), 1, kern_file);
            //Passa para o spel seguinte na adjacência.
            adjSpel++;
            //Passa para a banda seguinte.
            if (adjSpel == adjacency->n) {
                adjSpel = 0;
                layer++;
            }
        }

        //Adiciona o novo elemento ao vetor de kernels.
        kerns[i] = k;
    }

    //delAdjRel (&adjacency);

    fclose (kern_file);

    return kerns;
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

/*Cria novos kernels, em uma distribuição com média 0 e desvio padrão 1, 
 *e os armazena em memória.
 *numKernels: Quantidade de kernels a serem criados.
 *depth: Número de bandas dos kernels.
 *adjacency: Relação de adjacência (2D) do kernel.
 *Retorna vetor (alocado dinamicamente) com apontadores para os
 *kernels gerados.*/
Kernel ** randKernelsMemory (int numKernels, int depth, AdjRel * adjacency) {
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
    kerns = palloc (numKernels, sizeof (Kernel *), false, "randKernelsMemory");

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

/*Cria novos kernels, em uma distribuição com média 0 e desvio padrão 1, 
 *e os armazena em arquivo.
 *
 *numKernels: Quantidade de kernels a serem criados.
 *depth: Número de bandas dos kernels.
 *adjacency: Relação de adjacência (2D) do kernel.
 *path: caminho do arquivo onde serão armazenados os resultados.
 *
 *Formato do arquivo de saída: Quantidade de kernels (inteiro); quantidade de 
 *spels da adjacência(inteiro); adjacência em si (várias structs "AdjSpel", 
 *seguindo a quantidade de spels da adjacência); profundidade (inteiro); pesos 
 *(número de kernels * quantidade de spels na adjacência * profundidade 
 *elementos no formato double).
 */
void randKernelsFile (int numKernels, int depth, AdjRel * adjacency, 
char * path) {
    //Peso gerado aleatoriamente.
    double rand_weight;
    //Variáveis para percorrer a adjacência e as camadas.
    int layer, adjSpel;
    //Kernel gerado aleatoriamente.
    Kernel * k;
    //Arquivo de saída.
    FILE * kern_file;
    //Média e norma dos pesos de um kernel.
    double average;
    double norm;
    //Auxiliares.
    int i, j;

    //Inicializa arquivo.
    kern_file = fopen(path, "wb");
    if(kern_file == NULL) {
        errorMsg(OPEN, "randKernelsFile");
    }

    //Escreve parâmetros iniciais (número de kernels a serem escritos,
    //tamanho da adjacência, spels da adjacência e número de bandas).
    fwrite (&numKernels, sizeof(int), 1, kern_file);  
    fwrite (&(adjacency->n), sizeof(int), 1, kern_file);
    fwrite(adjacency->adj, sizeof(AdjSpel), (adjacency->n), kern_file );
    fwrite(&depth, sizeof(int), 1, kern_file);

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

        //Adiciona o kernel gerado ao arquivo (na verdade, somente seus pesos,
        //pois a adjacência e a profundidade são iguais para todos os kernels e
        //podem ser obtidas no início do arquivo).
        layer = 0;
        adjSpel = 0;
        for (j = 0; j < (adjacency->n * depth); j++) {
            //Escreve um peso.
            fwrite (&(k->w[adjSpel][layer]), sizeof(double), 1, kern_file);
            //Passa para o spel seguinte na adjacência.
            adjSpel++;
            //Passa para a banda seguinte.
            if (adjSpel == adjacency->n) {
                adjSpel = 0;
                layer++;
            }
        }

        delKernel (&k);
    }

    fclose (kern_file);

    return;
}
