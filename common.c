#include "common.h"

/* Aloca memória para um vetor de inteiros com n elementos */
int *allocIntArray(int n, bool c) {
    int *v;

    if(c == true) {
        v = calloc(n, sizeof(int));
    }
    else {
        v = malloc(n * sizeof(int));
    }

    if(v == NULL) {
        errorMsg(MEM, "allocIntArray");
    }

    return v;
}


/* Aloca memória para um vetor de caracteres sem sinal com n elementos */
uchar *allocUCharArray(int n, bool c) {
    uchar *v;

    if(c == true) {
        v = calloc(n, sizeof(uchar));
    }
    else {
        v = malloc(n * sizeof(uchar));
   }

    if(v == NULL) {
        errorMsg(MEM, "allocUCharArray");
    }

    return v;
}


/* Função que exibe uma mensagem de erro */
void errorMsg(char *msg, char *f) {
    fprintf(stderr, "Erro! %s em %s\n", msg, f);
    exit(EXIT_FAILURE);
}
