CC = gcc

CFLAGS = -g
OFLAGS = -O1 -march=native
LDFLAGS = -lm

all : project

project : image stencil main
	$(CC)  build/image.o build/stencil.o build/main.o -o main

image : image.c
	$(CC) -c $(CFLAGS) $(OFLAGS) image.c -o build/image.o

stencil : stencil.c
	$(CC) -c $(CFLAGS) $(OFLAGS) stencil.c -o build/stencil.o


main : main.c
	$(CC) -c $(CFLAGS) $(OFLAGS) main.c -o build/main.o

