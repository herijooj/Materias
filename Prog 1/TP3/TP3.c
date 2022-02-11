#include <stdio.h>
int n;
int v[100];

/* essa função recebe um numero n e um vetor de tamanho 100, e escreve nesse vetor */
void ler_vetor () {
    scanf("%d", &n);
    for (int p = 0; p < n; p++)
        scanf("%d", &v[p]);
}

/* essa função recebe um numero n e um vetor, e imprime a posição i e o tamanho da sequência m */
void verificar_subsequencia () {
	int p,q,j,cont,m,i;
	
	for (p = 0; p < n ; p++) {
		for (q = p + 1; q <= n ; q++) {
			if (v[p] == v[q]) {
				i = p;
				cont = 1;
				for (j = 1; v[p + j] == v[q + j] ; j++)
					cont++;
			}
			if ((m < cont) && (cont >= 2))
				m = cont;
		}
	}
	if (m == 0)
		printf("nenhuma\n");
	else 
		printf("%d %d \n", i-1,m);
}	

/* programa principal */

int main () {
	ler_vetor ();	
	verificar_subsequencia ();
    return 0;
}

/* Faça um programa em C que leia um número natural 0 < n ≤ 100 e
em seguida leia uma sequência de n números também naturais. Seu pro-
grama deve verificar se existem duas subsequências iguais nesta sequência
com tamanho pelo menos 2. O tamanho da sequência encontrada deverá
ser máximo, se ela existir. Caso exista, seu programa deve imprimir o valor
da posição i e do tamanho máximo da sequência m, nesta ordem, onde i
é a posição da primeira ocorrência da sequência que possui uma cópia na
sequência original e m é o tamanho desta sequência que se repete. Caso
contrário seu programa deve imprimir “nenhuma”. Os casos de teste não
conterão entradas com mais de uma subsequência igual. */
