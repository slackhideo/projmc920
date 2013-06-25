/* testReadWrite.c
 *
 * Testa funções de ler e escrever imagens */

#include "projlib.h"
#include <string.h>

int main(void) {
    ImagePGM *img, *img2;
    char * path = "flower_001.pgm";
    
    img = readImage(path);
    img2 = newImage(10, 10, 1, "Testando_Classe");
    
    printf("classe img1: '%s'\t classe img2: '%s'\t testando tamanho: '%s', '%d' ", img->imgClass, img2->imgClass, "_XXX.XXX", (int)strlen("_XXX.XXX"));

    writeImage(img, "flower_out.pgm", 1);  
    
    return EXIT_SUCCESS;
}
