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

/* Invólucro para malloc e calloc */
void *palloc(size_t n, size_t size, bool c, char *func);

/* Mostra mensagem de erro e sai */
void errorMsg(char *msg, char *f);

#endif /* __COMMON_H__ */
