/*
 * common.c
 * Contém funções comuns ao projeto
 */

#include "common.h"

/* Invólucro para o malloc e o calloc */
void *palloc(size_t n, size_t size, bool c, char *func) {
    void *p;

    if(c == true) {
        p = calloc(n, size);
    }
    else {
        p = malloc(n * size);
    }

    if(p == NULL) {
        errorMsg(MEM, func);
    }

    return p;
}


/* Função que exibe uma mensagem de erro */
void errorMsg(char *msg, char *f) {
    fprintf(stderr, "Erro! %s em %s\n", msg, f);
    exit(EXIT_FAILURE);
}
