# Name: Thomas Green
# ID: 1048389
# Assignment #: 2

CC = gcc
CFLAGS = -ansi -Wall -pedantic -Iincludes

default: main

main: main.o P11.o P12.o P21.o P22.o
	$(CC) P11.o P12.o P21.o P22.o main.o -o main -lm

main.o: main.c
		$(CC) $(CFLAGS) -c -o main.o main.c

P11.o: P11.c
	$(CC) $(CFLAGS) -c -o P11.o P11.c

P12.o: P12.c
	$(CC) $(CFLAGS) -c -o P12.o P12.c

P21.o: P21.c
	$(CC) $(CFLAGS) -c -o P21.o P21.c

P22.o: P22.c
	$(CC) $(CFLAGS) -c -o P22.o P22.c

clean:
	rm -f main main.o P11.o P12.o P21.o P22.o
