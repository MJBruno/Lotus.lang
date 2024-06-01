CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: interpreter

interpreter: main.o lexer.o parser.o compiler.o vm.o
	$(CC) $(CFLAGS) -o interpreter main.o lexer.o parser.o compiler.o vm.o

main.o: main.c lexer.h parser.h compiler.h vm.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h lexer.h
	$(CC) $(CFLAGS) -c parser.c

compiler.o: compiler.c compiler.h parser.h
	$(CC) $(CFLAGS) -c compiler.c

vm.o: vm.c vm.h compiler.h
	$(CC) $(CFLAGS) -c vm.c

clean:
	rm -f *.o interpreter
