EXEC = pila
CFILES = pila.c pruebas_alumno_pila.c testing.c main.c
HFILES = pila.h testing.h 

CC = gcc
CFLAGS = -g -std=c99 -Wall -Werror -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow
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