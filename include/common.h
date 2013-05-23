/* common.h */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>
#include <locale.h>

/* Deixando o uso de gettext mais prático */
#define _(STRING) gettext(STRING)
#define N_(STRING) gettext_noop(STRING)
#define gettext_noop(STRING) (STRING)

/* Mensagens de erro */
#define MEM _("Não foi possível alocar o espaço em memória solicitado")
#define OPEN _("Não foi possível abrir o arquivo")


/* Definições comuns */
typedef unsigned char uchar;
typedef enum boolean {false, true} bool;


/* Funções comuns */

/* Invólucro para malloc e calloc */
void *palloc(size_t n, size_t size, bool c, char *func);

/* Mostra mensagem de erro e sai */
void errorMsg(char *msg, char *f);

#endif /* __COMMON_H__ */
