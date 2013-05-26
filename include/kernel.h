/* kernel.h */

#ifndef __KERNEL_H__
#define __KERNEL_H__

/* Estrutura para kernels
 *
 * depth: número de bandas (profundidade)
 * ar:    relação de adjacência
 * w:     matriz de pesos das adjacências */
typedef struct {
    int depth;
    AdjRel *ar;
    double **w;
} Kernel;


/* Funções que operam com kernels */

/* Função que cria um novo kernel */
Kernel *newKernel(int depth, AdjRel *ar);

/* Função que apaga um kernel */
void delKernel(Kernel **k);

/* Função que lê um kernel a partir de um arquivo de texto */
Kernel *readKernelText(char *path);

/* Função que lê um kernel a partir de um arquivo binário. */
Kernel ** readKernelsBinary(char *path);

/* Função que reflete um kernel */
Kernel *reflectKernel(Kernel *k);

/* Função que gera kernels aleatórios com média 0 e norma 1, retornando-os
 * por meio de um apontador. */
Kernel ** randKernelsMemory (int numKernels, int depth, AdjRel * adjacency);

/* Função que gera kernels aleatórios com média 0 e norma 1, 
 * armazenando-os em arquivo. */
void randKernelsFile (int numKernels, int depth, AdjRel * adjacency, 
char * path);

#endif /* __KERNEL_H__ */
