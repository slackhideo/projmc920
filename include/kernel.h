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

/* Função que lê um kernel a partir de um arquivo */
Kernel *readKernel(char *kernPath);

/* Função que reflete um kernel */
Kernel *reflectKernel(Kernel *k);

#endif /* __KERNEL_H__ */
