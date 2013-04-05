/* imagem.h */
#define INF 0x7FFFFFFF

typedef struct _imagemPGM {
    int largura;
    int altura;
    int numEls;
    int valMax;
    int *vals;
    int menor;
    int maior;
} imagemPGM;
