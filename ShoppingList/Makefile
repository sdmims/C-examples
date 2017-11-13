CC = gcc
CFLAGS = -g -Wall -std=c99

shopping: shopping.o list.o item.o

list.o: list.h item.h

item.o: item.h

clean:
	rm -f shopping shopping.o list.o item.o
	rm -f output.txt
	rm -f output.ppm
