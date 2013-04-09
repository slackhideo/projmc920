#include "common.h"
#include "image.h"

int main(int argc, char *argv[]) {
    uchar *v;
    long long int n, i;
    ImagePGM *img;

    if(argc > 1) {
        n = atoll(argv[1]);

        v = allocUCharArray(n, false);

        printf("%ld %lld\n",sizeof(uchar),n);
        for(i=0; i<n; i++) v[i] = 't';
    }
    else {
        img = readImage("flower.pgm");
        printf("Largura: %d, altura: %d e brilho máximo: %d\n",
                img->width, img->height, img->maxVal);
    }


    return EXIT_SUCCESS;
}
