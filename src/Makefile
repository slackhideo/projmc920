include ../make.inc

# Ajusta variáveis de caminhos
INCLUDE := ../$(INCLUDE)
LIB := ../$(LIB)

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

.PHONY: clean
clean:
	rm -f $(LIB)/libproj.a *.o *~
