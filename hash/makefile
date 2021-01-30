EXEC = hash
CFILES = hash.c  testing.c main.c hash_pruebas.c
HFILES = hash.h testing.h 

CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Werror -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 -v

all: $(EXEC)

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC)

valgrind: all
	valgrind $(VFLAGS) ./$(EXEC)

$(EXEC): $(OFILES) $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) $(OFILES) $(CFILES) -o $(EXEC)