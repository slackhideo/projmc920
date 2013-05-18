/* adjacency.h */

#ifndef __ADJACENCY_H__
#define __ADJACENCY_H__

/* Estrutura para spels adjacentes
 * dx: deslocamento em x para se chegar ao spel adjacente
 * dy: deslocamento em y para se chegar ao spel adjacente */
typedef struct {
    int dx, dy;
} AdjSpel;


/* Estrutura para relações de adjacência
 * n:   Número de spels da relação de adjacência
 * adj: Vetor de spels adjacentes */
typedef struct {
    int n;
    AdjSpel *adj;
} AdjRel;


/* Funções que operam com adjacências */

/* Função que cria uma nova relação de adjacência */
AdjRel *newAdjRel(int n);

/* Função que apaga uma relação de adjacência */
void delAdjRel(AdjRel **ar);

#endif /* __ADJACENCY_H__ */
