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

.PHONY: test clean
test: test.o common.o image.o
	$(CC) -o test test.o common.o image.o

test.o: test.c
	$(CC) $(CFLAGS) test.c

clean:
	rm -rf image test *.o *~
