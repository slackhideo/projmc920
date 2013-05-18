# Compilador
CC = gcc
AR = ar

# Flags para o compilador
CFLAGS = -Wall -W #-O2

# Diretório padrão para os cabeçalhos
INCLUDE = ../include

# Diretório padrão para a biblioteca criada
LIB = ../lib


all: libproj

libproj: $(LIB)/libproj.a

$(LIB)/libproj.a: common.o image.o adjacency.o kernel.o
	$(AR) csr $(LIB)/libproj.a common.o image.o adjacency.o kernel.o
	@echo "Compilação da biblioteca completa"

common.o: common.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) common.c

image.o: image.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) image.c

adjacency.o: adjacency.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) adjacency.c

kernel.o: kernel.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) kernel.c

test: $(LIB)/libproj.a
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) -o test test.c -lproj

.PHONY: clean
clean:
	rm -rf $(LIB)/libproj.a test *.o *~
