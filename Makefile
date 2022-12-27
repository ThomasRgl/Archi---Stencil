CC = gcc

CFLAGS = -g
OFLAGS = -O1 -march=native
LDFLAGS = -lm

all : main

main : image stencil
	$(CC)  build/image.o build/stencil.o -o main

image : image.c
	$(CC) -c $(CFLAGS) $(OFLAGS) image.c -o build/image.o

stencil : stencil.c
	$(CC) -c $(CFLAGS) $(OFLAGS) stencil.c -o build/stencil.o

