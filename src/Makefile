# Compilador
CC = gcc
AR = ar

# Flags para o compilador
CFLAGS = -Wall #-O2

# Diretório padrão para os cabeçalhos
INCLUDE = ../include

# Diretório padrão para a biblioteca criada
LIB = ../lib


all: libproj

libproj: $(LIB)/libproj.a

$(LIB)/libproj.a: image.o common.o
	$(AR) csr $(LIB)/libproj.a image.o common.o
	@echo "Compilação da biblioteca completa"

image.o: image.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) image.c

common.o: common.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) common.c

test: $(LIB)/libproj.a
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) -o test test.c -lproj

.PHONY: clean
clean:
	rm -rf $(LIB)/libproj.a test *.o *~
