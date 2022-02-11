OBJS	= libconjunto.o libfila.o liblef.o mundo.o
SOURCE	= libconjunto.c libfila.c liblef.c mundo.c
HEADER	= libconjunto.h libfila.h liblef.h
OUT	= mundo
CC	 = gcc
FLAGS	 = -g3 -c -Wall
LFLAGS	 = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

mundo: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)
libconjunto.o: libconjunto.c
	$(CC) $(FLAGS) libconjunto.c -std=c90

libfila.o: libfila.c
	$(CC) $(FLAGS) libfila.c -std=c90

liblef.o: liblef.c
	$(CC) $(FLAGS) liblef.c -std=c90

mundo.o: mundo.c
	$(CC) $(FLAGS) mundo.c -std=c90


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind -s --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)