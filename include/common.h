/* common.h */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

/* Mensagens de erro */
#define MEM "Não foi possível alocar o espaço em memória solicitado"
#define OPEN "Não foi possível abrir o arquivo"

/* Definições comuns */
typedef unsigned char uchar;
typedef enum boolean {false, true} bool;

/* Funções comuns */
int *allocIntArray(int n, bool c); /* Aloca um vetor de inteiros */
uchar *allocUCharArray(int n, bool c); /* Aloca um vetor de caracteres */
void errorMsg(char *msg, char *f); /* Mostra mensagem de erro e sai */

#endif /* __COMMON_H__ */
