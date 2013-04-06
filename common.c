#include "common.h"

uchar *allocUCharArray(int n, bool c) {
    uchar *v;

    if(c == true) {
        v = (uchar *)calloc(n, sizeof(uchar));
    }
    else {
        v = (uchar *)malloc(n * sizeof(uchar));
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
