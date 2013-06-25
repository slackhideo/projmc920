/*
 * normalization.c
 * Contém funções relacionadas à normalização
 */

#include "common.h"
#include "image.h"
#include "adjacency.h"


/* normaliza uma imagem e retorna a imagem gerada
 *
 * img: imagem de entrada
 * *ar: ponteiro para uma relação de adjacência que será considerada ao tratar a imagem */

ImagePGM *normalization(ImagePGM *img, AdjRel *ar){
    ImagePGM *out;
    int xp, yp, zp; /*variáveis uzadas para marcar o passo em cada for*/
    int xq, yq, zq; /*variáveis uzadas para marcar o passo em cada for para a relação de adjacência*/
    int q, p; /*variáveis para representar o spel em um vetor*/
    
    double val; /*variável receberá o valor a ser adicionado no spel de saída*/
    
    int imgX = img->width; /*tamanho x da imagem */
    int imgY = img->height; /*tamanho y da imagem */
    int imgLayers = img->depth; /*tamanho z (número de bandas/layers) da imagem */
    char * imgClass = img->imgClass; /*classe da imagem*/
    
    int i; /*variável auxiliar para 'for' de adjacências*/

    /* Cria imagem de saída */
    out = newImage(imgX, imgY, imgLayers, imgClass);

    /* Aplica pooling na imagem original e coloca o valor na imagem de saída */
    for(yp = 0; yp < imgY; yp++) {
	for(xp = 0; xp < imgX; xp++) {
	  
	    val = 0.0;
	    /*Este laço cria o valor que vai ser usado para dividir cada valor de spel conforme slide 15 da aula 7-8*/
	    for(zp = 0; zp < imgLayers; zp++){

		p = xp + yp*imgX + zp*imgX*imgY;
		
		for(i = 0; i < ar->n; i++) {

		    xq = (xp + ar->adj[i].dx);
		    yq = (yp + ar->adj[i].dy);
		    zq = zp; /*Essa linha é inútil, eu sei, mas resolvi colocar pra manter o paadrão e clareza do código;*/
		    
		    q = xq + yq*imgX + zq*imgX*imgY;
		    
		    /* verifica se a adjacência é válida ou está fora da imagem e adiciona na lista de luminescências*/
		    if((xq >= 0) && (xq < imgX) &&
		      (yq >= 0) && (yq < imgY)) {

			val += img->vals[q]*img->vals[q];
		      
		    }
		    
		}
		val = sqrt(val);

	    /* Este laço adiciona os valores dos spels na lista que será alocada na
         * imagem de saída */
	    for(zp = 0; zp < imgLayers; zp++){
            p = xp + yp*imgX + zp*imgX*imgY;

            /* Se o denominador for zero, faz valor do brilho de saída receber
             * o valor do brilho de entrada, evitando problemas de 'nan' e
             * 'inf' */
            if(val == 0) {
                out->vals[p] = img->vals[p];
            }

            /* Coloca o valor do brilho na imagem */
            else {
                out->vals[p] = img->vals[p]/val;
            }
	    }


	    }
	    
	    
	}
    }

    /* Atualiza os brilhos mínimo e máximo da imagem */
    findLowerHigher(out);

    return out;
}
