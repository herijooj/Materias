#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

int main () 
{
  int i;
  conjunto_t *c, *d, *e, *f;

  printf("\ninicializando conjuntos\n");

  /* Inicializar conjuntos */
  c = cria_conjunto(10);
  d = cria_conjunto(10);
  e = cria_conjunto(10);
  f = cria_conjunto(10);

  if (c == NULL || d == NULL || e == NULL || f == NULL) 
    printf("\nErro ao alocar memoria para os conjuntos.\n");
  
  printf("\ninserindo elementos nos conjuntos\n");

  /* Inserir elemento aleatorio nos conjuntos*/
  for (i = 0; i < 10; i++) 
  {
    insere(rand() % 100, c);
    insere(rand() % 100, d);
    insere(rand() % 100, e);
    insere(rand() % 100, f);
  }

  printf("\nimprimindo conjuntos\n");

  printf("\nconjunto c: ");
  imprime(c);
  printf("\nconjunto d: ");
  imprime(d);
  printf("\nconjunto e: ");
  imprime(e);
  printf("\nconjunto f: ");
  imprime(f);

  printf("\ntestando se os conjuntos são iguais\n");

  /* testa se os conjuntos são iguais */
  if (sao_iguais(c, d))
    printf("\nConjuntos iguais.\n");
  else
    printf("\nConjuntos diferentes.\n");

  printf("\ndestruindo os conjuntos\n");


 /* destroi os conjuntos */
  destroi_conjunto(c);
  destroi_conjunto(d);
  destroi_conjunto(e);
  destroi_conjunto(f);

  printf("\nverificando se os conjuntos foram destruidos\n");


  /* Verifica se os conjuntos foram destruidos */
    if (c != NULL || d != NULL || e != NULL || f != NULL)
    printf("\nErro ao destruir os conjuntos.\n");

    printf("\n inicializando novos conjuntos\n");


  /* Inicializa os conjuntos novamente */
  c = cria_conjunto(10);
  d = cria_conjunto(10);
  e = cria_conjunto(10);
  f = cria_conjunto(10);

  printf("\ninserindo elementos nos conjuntos\n");


  /* insere elementos nos conjuntos */
  for (i = 1; i < 9; i++) 
  {
    insere(i, c);
    insere(i, d);
    insere(i, e);
    insere(i, f);
  }
 
  printf("\ntestando se os conjuntos são iguais\n");

  imprime(c);
  imprime(d);
  imprime(e);
  imprime(f);

  /* testa se os conjuntos são iguais */
  if (sao_iguais(c, d))
    printf("\nConjuntos iguais.\n");
  else
    printf("\nConjuntos diferentes.\n");

  printf("\ntestando se um elemento já existe no conjunto\n");

 /* testa se o elemento esta no conjunto */
    if (insere(c -> v[1], c) == 0) 
      printf("\nElemento ja esta no conjunto.\n");
    
  printf("\ntestando se existe espaço no conjunto\n");

  /* testa se tem espaço para inserir mais elementos */
    for (i = 0; i < 2; i++) 
    {
      if (insere(i, c) == -1) 
        printf("\nConjunto cheio.\n");
    }

  printf("\n testando se o conjunto esta vazio\n");

  /* testa se o conjunto esta vazio */
    printf("\nconjunto c: ");
    imprime(c);
    if (eh_vazio(c) == 0) 
      printf("\nConjunto nao esta vazio.\n");
    
    for (i = 0; i < 10; i++) 
      retira(i,c);

    printf("\nconjunto c: ");
    imprime(c);
    if (eh_vazio(c) == 1) 
      printf("\nConjunto esta vazio.\n");

  printf("\ndestruindo conjuntos\n");

  /* destroi os conjuntos */
  destroi_conjunto(c);
  destroi_conjunto(d);
  destroi_conjunto(e);
  destroi_conjunto(f);

  /* Verifica se os conjuntos foram destruidos */
    if (c != NULL || d != NULL || e != NULL || f != NULL)
    printf("\nErro ao destruir os conjuntos.\n");

  printf("\ncriando novos conjuntos\n");


/* Inicializar conjuntos */
  c = cria_conjunto(10);
  d = cria_conjunto(10);
  e = cria_conjunto(10);
  f = cria_conjunto(10);

  if (c == NULL || d == NULL || e == NULL || f == NULL) 
    printf("\nErro ao alocar memoria para os conjuntos.\n");
  
  printf("\n inserindo elementos nos conjuntos\n");

  /* Inserir elemento aleatorio nos conjuntos*/
  for (i = 0; i < 10; i++) 
  {
    insere(rand() % 100, c);
    insere(rand() % 100, d);
    insere(rand() % 100, e);
    insere(rand() % 100, f);
  }

  imprime(c);
  imprime(d);
  imprime(e);
  imprime(f);

  printf("\nimprimindo a união dos conjuntos\n");

  /* cria os conjuntos que recebem as funcoes */
  conjunto_t *unicd = cria_interseccao(c, d);
  conjunto_t *unief = cria_interseccao(e, f);


  /* imprime a uniao dos conjuntos */
  printf("\nconjunto c e d: ");
  imprime(unicd);
  printf("\nconjunto e e f: ");
  imprime(unief);

  printf("\nimprimindo a interseccao dos conjuntos\n");

  /* cria os conjuntos que recebem as funcoes */
  conjunto_t *intercd = cria_interseccao(c, d);
  conjunto_t *interef = cria_interseccao(e, f);

  /* imprime a interseccao dos conjuntos */
  printf("\nconjunto c e d: ");
  imprime(intercd);
  printf("\nconjunto e e f: ");
  imprime(interef);

printf("\nimprimindo a diferença dos conjuntos\n");

  /* cria os conjuntos que recebem as funcoes */
  conjunto_t *difcd = cria_diferenca(c, d);
  conjunto_t *difef = cria_diferenca(e, f);

  /* imprime os conjuntos */
  printf("\nconjunto c e d: ");
  imprime(difcd);
  printf("\nconjunto e e f: ");
  imprime(difef);

printf("\ndestroi os conjuntos\n");

/* destroi os conjuntos */
  destroi_conjunto(c);
  destroi_conjunto(d);
  destroi_conjunto(e);
  destroi_conjunto(f);
  destroi_conjunto(unicd);
  destroi_conjunto(unief);
  destroi_conjunto(intercd);
  destroi_conjunto(interef);
  destroi_conjunto(difcd);
  destroi_conjunto(difef);
  
  return 0;
}