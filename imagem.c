#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "imagem.h"

imagemPGM *criarImagem(int largura, int altura, int valMax) {
    imagemPGM *nova = (imagemPGM *)malloc(sizeof(imagemPGM));

    if(nova == NULL) {
        printf("Ferrou!\n");
        exit(1);
    }

    nova->largura = largura;
    nova->altura = altura;
    nova->numEls = largura * altura;
    nova->valMax = valMax;
    nova->vals = (int *)malloc(largura * altura * sizeof(int));

    if(nova->vals == NULL) {
        printf("Agora, ferrou\n");
    }

    nova->menor = INT_MAX;
    nova->maior = 0;
}
