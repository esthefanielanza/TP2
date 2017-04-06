CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99

all: main

main: main.o busca.o fila.o leitura.o
	$(CC) $(CFLAGS) main.o busca.o fila.o leitura.o -o main

main.o: main.c busca.h fila.h leitura.h
	$(CC) $(CFLAGS) -c main.c

busca.o: busca.c busca.h
	$(CC) $(CFLAGS) -c busca.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

leitura.o: leitura.c leitura.h
	$(CC) $(CFLAGS) -c leitura.c

clean:
	rm *.o main