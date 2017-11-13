CC = gcc
CFLAGS = -g -Wall -std=c99

un-utf8: un-utf8.o codepoints.o

codepoints.o: codepoints.h

clean:
	rm -f un-utf8 un-utf8.o
	rm -f output.txt
	rm -f output.ppm
