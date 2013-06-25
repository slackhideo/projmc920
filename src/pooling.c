/*
 * pooling.c
 * Contém funções relacionadas ao pooling
 */

#include "common.h"
#include "image.h"
#include "adjacency.h"


/* Aplica o pooling em uma imagem e retorna a imagem gerada
 *
 * img: imagem de entrada
 * strideX: passo do pooling em X
 * strideY: passo do pooling em Y
 * *ar: ponteiro para uma relação de adjacência que será considerada ao tratar a imagem
 * *f:   função de pooling, que recebe como entrada um vetor de valores (luminâncias) e retorna o valor a ser considerado */

ImagePGM *pooling(ImagePGM *img, int strideX, int strideY, AdjRel *ar, double (*f)(double *, int)){
    ImagePGM *out;
    int xp, yp, zp; /*variáveis uzadas para marcar o passo em cada for*/
    int xq, yq, zq; /*variáveis uzadas para marcar o passo em cada for para a relação de adjacência*/
    int imgp, imgSaidap; /*variáveis para representar o spel em um vetor*/
    
    double val; /*variável receberá o valor a ser adicionado no spel de saída*/
    double valList[ar->n]; /*Lista que será enviada à função externa*/
    
    int imgX = img->width; /*tamanho x da imagem de entrada*/
    int imgY = img->height; /*tamanho y da imagem de entrada*/
    
    int imgOutX = (img->width)/strideX; /*tamanho x da imagem de saída*/
    int imgOutY = (img->height)/strideY; /*tamanho y da imagem de saída*/
    int imgOutLayers = img->depth; /*tamanho z da imagem de saída*/
    
    int i; /*variável auxiliar para 'for' de adjacências*/
    
    char * imgClass = img->imgClass; /*classe da imagem*/

    /* Cria imagem de saída */
    out = newImage(imgOutX, imgOutY, imgOutLayers, imgClass);

    /* Aplica pooling na imagem original e coloca o valor na imagem de saída */
    for(zp = 0; zp < imgOutLayers; zp++){
	for(yp = 0; yp < imgOutY; yp++) {
	    for(xp = 0; xp < imgOutX; xp++) {

		imgSaidap = xp + yp*imgOutX + zp*imgOutX*imgOutY;
		val = 0.0;

		/* Adiciona todo adjacente q de p em lista de luminescências*/
		
		for(i = 0; i < ar->n; i++) {

		    xq = (xp*strideX + ar->adj[i].dx);
		    yq = (yp*strideY + ar->adj[i].dy);
		    zq = zp; /*Essa linha é inútil, eu sei, mas resolvi colocar pra manter o paadrão e clareza do código*/;
		    
		    imgp = xq + yq*imgX + zq*imgX*imgY;
		    
		    /* verifica se a adjacência é válida ou está fora da imagem e adiciona na lista de luminescências*/
		    if((xq >= 0) && (xq < imgX) &&
		      (yq >= 0) && (yq < imgY)) {

			valList[i] = img->vals[imgp];
		      
		    } else {
		      valList[i] = 0; 
		    }
		    
		}
		
		/* calcula o valor do pooling que será adicionado no spel da imagem de saída*/
		val = f(valList, ar->n);

		/* Coloca o valor do brilho na imagem */
		out->vals[imgSaidap] = val;
	    }
	}
    }

    /* Atualiza os brilhos mínimo e máximo da imagem */
    findLowerHigher(out);

    return out;
}

double max(double *valList, int n){
  int i;
  double s=0;
  /*essa função de teste do pooling retorna a média dos elementos da lista de luminescências*/
  for(i=0; i<n; i++){
    if(valList[i]>s){
      s = valList[i];
    }   
  }
  return s;
}
double min(double *valList, int n){
  int i;
  double s=255;
  /*essa função de teste do pooling retorna a média dos elementos da lista de luminescências*/
  for(i=0; i<n; i++){
    if(valList[i]<s){
      s = valList[i];
    }   
  }
  return s;
}
double mean(double *valList, int n){
  int i;
  double s=0;
  /*essa função de teste do pooling retorna a média dos elementos da lista de luminescências*/
  for(i=0; i<n; i++){
    s+=valList[i];   
  }
  return s/n;
}
double norm2(double *valList, int n){
  int i;
  double s=0;
  /*essa função de teste do pooling retorna a média dos elementos da lista de luminescências*/
  for(i=0; i<n; i++){
    s+=valList[i]*valList[i];   
  }
  return sqrt(s);
}
