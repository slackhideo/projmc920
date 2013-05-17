#include "common.h"

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

void errorMsg(char *msg, char *f) {
    fprintf(stderr, "Erro! %s em %s\n", msg, f);
    exit(EXIT_FAILURE);
}


void teste3 {
    pasjlfajçsdljfsd
}

void teste1 {
    return;
}

void teste2 {
    printf("teste\n");
}

void teste5 {
    printf ("eita mah!\n");
}
