CC = gcc
CFLAGS = -g -Wall -std=c99

puzzle: puzzle.o command.o board.o

puzzle.o: command.h board.h

command.o: command.h board.h

board.o: board.h

clean:
	rm -f puzzle puzzle.o command.o board.o
	rm -f output.txt
	rm -f output.ppm
