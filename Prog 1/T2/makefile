# Escrito por mim, debugado por Deus...
OBJS	= libconjunto.o testa_conjunto.o libfila.o testa_fila.o liblista.o testa_lista.o
OUT	= testa_conjunto,testa_fila,testa_lista

OBJS0	= libconjunto.o testa_conjunto.o
SOURCE0	= libconjunto.c testa_conjunto.c
HEADER0	= libconjunto.h
OUT0	= testa_conjunto

OBJS1	= libfila.o testa_fila.o
SOURCE1	= libfila.c testa_fila.c
HEADER1	= libfila.h
OUT1	= testa_fila

OBJS2	= liblista.o testa_lista.o
SOURCE2	= liblista.c testa_lista.c
HEADER2	= liblista.h
OUT2	= testa_lista

CC	 = gcc
FLAGS	 = -g3 -c -Wall -std=c90
LFLAGS	 = 

all: testa_conjunto testa_fila testa_lista

testa_conjunto: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

testa_fila: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

testa_lista: $(OBJS2) $(LFLAGS)
	$(CC) -g $(OBJS2) -o $(OUT2)

libconjunto.o: libconjunto.c
	$(CC) $(FLAGS) libconjunto.c -std=c90

testa_conjunto.o: testa_conjunto.c
	$(CC) $(FLAGS) testa_conjunto.c -std=c90

libfila.o: libfila.c
	$(CC) $(FLAGS) libfila.c -std=c90

testa_fila.o: testa_fila.c
	$(CC) $(FLAGS) testa_fila.c -std=c90

liblista.o: liblista.c
	$(CC) $(FLAGS) liblista.c -std=c90

testa_lista.o: testa_lista.c
	$(CC) $(FLAGS) testa_lista.c -std=c90

# clean
clean:
	rm -f $(OBJS) $(OUT)

# run
run: $(OUT)
	./$(OUT)

# debug
debug: $(OUT)
	valgrind $(OUT)

# valgrind
valgrind: $(OUT)
	valgrind $(OUT)

# valgrind leak checks
valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

# valgrind leak checks (extreme)
valgrind_extreme: $(OUT)
	valgrind -s --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT