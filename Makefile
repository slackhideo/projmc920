# Compilador
CC=gcc

# Flags para o compilador
CFLAGS=-Wall -c

all: image

image: image.o common.o
	$(CC) -o image image.o common.o

image.o: image.c
	$(CC) $(CFLAGS) image.c

common.o: common.c
	$(CC) $(CFLAGS) common.c

clean:
	rm -rf image *.o *~
