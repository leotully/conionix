CC = gcc
CFLAGS = -g -Wall

all: libconionix.a

libconionix.a: conionix.o
	ar rcs libconionix.a conionix.o

conionix.o: conionix.c conionix.h
	$(CC) $(CFLAGS) -c -o conionix.o conionix.c

clean:
	rm -f conionix.o
	rm -f libconionix.a

move:
	cp conionix.h /usr/include/
	mv libconionix.a /usr/lib/

