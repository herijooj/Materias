tp4: libconjunto.o testa.o
	gcc -o tp4 libconjunto.o testa.o
libconjunto.o : libconjunto.c libconjunto.h
	gcc -g -std=c90 -Wall libconjunto.c libconjunto.h -c 
testa.o : testa.c libconjunto.h
	gcc -g -std=c90 -Wall testa.c libconjunto.h -c

clean: 
	rm -f *.o tp4