/*
 * common.c
 * Contém funções comuns ao projeto
 */

#include "common.h"

/* Invólucro para o malloc e o calloc
 *
 * n:    número de elementos a serem alocados
 * size: tamanho de cada elemento
 * c:    se true, inicializa a memória com zeros; se false, não inicializa
 * func: nome da função que fez a chamada */
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


/* Função que exibe uma mensagem de erro
 *
 * msg:  mensagem a ser exibida
 * func: nome da função que fez a chamada */
void errorMsg(char *msg, char *func) {
    setlocale(LC_ALL, "");
    bindtextdomain("projmc920", "po");
    textdomain("projmc920");

    fprintf(stderr, _("Erro! %s em %s\n"), msg, func);
    exit(EXIT_FAILURE);
}
