include ../make.inc

# Ajusta variáveis de caminhos
INCLUDE := ../$(INCLUDE)
LIB := ../$(LIB)

all: libproj deeplearning

libproj: $(LIB)/libproj.a

$(LIB)/libproj.a: common.o image.o adjacency.o kernel.o filter.o pooling.o \
				normalization.o
	$(AR) csr $(LIB)/libproj.a common.o image.o adjacency.o kernel.o filter.o \
			pooling.o normalization.o
	@echo "Compilação da biblioteca completa"

deeplearning: deeplearning.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LIB) \
			-o ../deeplearning deeplearning.c -lproj -lm

common.o: common.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) common.c

image.o: image.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) image.c

adjacency.o: adjacency.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) adjacency.c

kernel.o: kernel.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) kernel.c

filter.o: filter.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) filter.c

pooling.o: pooling.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) pooling.c

normalization.o: normalization.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) normalization.c

.PHONY: clean
clean:
	rm -f $(LIB)/libproj.a *.o *~
