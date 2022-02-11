#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

int main () 
{
  conjunto_t *c, *d, *e, *f;
  int i;
  printf("\ninicializando conjuntos\n");

  c = cria_conjunto(10);
  d = cria_conjunto(10);
  e = cria_conjunto(10);
  f = cria_conjunto(10);

  printf("\ntesta se os conjuntos estão vazios\n");

  if (conjunto_vazio(c))
    printf("\nConjunto c vazio\n");
  if (conjunto_vazio(d))
    printf("\nConjunto d vazio\n");
  if (conjunto_vazio(e))
    printf("\nConjunto e vazio\n");
  if (conjunto_vazio(f))
    printf("\nConjunto f vazio\n");

  printf("\ntesta a cardinalidade dos conjuntos\n");
  printf("\nConjunto c: %d\n", cardinalidade(c));
  printf("\nConjunto d: %d\n", cardinalidade(d));
  printf("\nConjunto e: %d\n", cardinalidade(e));
  printf("\nConjunto f: %d\n", cardinalidade(f));


  printf("\ninserindo elementos em c\n");
  
  for (i = 0; i < 20; i++)
  { 
    insere_conjunto(c, i);
  }

  printf("\ninserindo elementos em d\n");

  for (i = 10; i > 0; i--)
  { 
    insere_conjunto(d, i);
  }

  printf("\nimprime c\n");
  imprime(c);
  printf("\nimprime d\n");
  imprime(d);

  printf("\ntesta se o elemento pertence\n");

  if (pertence(c, 5))
    printf("\nO elemento 5 pertence ao conjunto c\n");
  if (pertence(d, 5))
    printf("\nO elemento 5 pertence ao conjunto d\n");

  printf("\n tenta inserir elemento que já pertence no conjunto c\n");
  if (insere_conjunto(c, 1)==0)
    printf("\nElemento já pertence\n");

  printf("\n testa se cabe mais elementos no conjunto c\n");
  if (insere_conjunto(c, 11)==-1)
    printf("\nConjunto c está cheio\n");

  printf("\ntesta se c e d são iguais\n");
  
  if (sao_iguais(c, d))
    printf("\nc e d são iguais\n");

  printf("\ninserindo elementos em e\n");

  for (i = 10; i < 20; i++)
  { 
    insere_conjunto(e, i);
  }

  printf("\ninserindo elementos em f\n");

  for (i = 20; i < 30; i++)
  { 
    insere_conjunto(f, i);
  }

  printf("\nimprime e\n");
  imprime(e);
  printf("\nimprime f\n");
  imprime(f);

  printf("\ntesta se c e e são iguais\n");
  if (sao_iguais(c, e))
    printf("\nc e e são iguais\n");
  else
    printf("\nc e e não são iguais\n");
  
  printf("\ntesta se d e f são iguais\n");
  if (sao_iguais(d, f))
    printf("\nd e f são iguais\n");
  else
    printf("\nd e f não são iguais\n");

  printf("\ntesta a cardinalidade dos conjuntos\n");
  printf("\nConjunto c: %d\n", cardinalidade(c));
  printf("\nConjunto d: %d\n", cardinalidade(d));
  printf("\nConjunto e: %d\n", cardinalidade(e));
  printf("\nConjunto f: %d\n", cardinalidade(f));

  printf("\nretira um elemento escolhido dos conjuntos\n");

  retira_conjunto(c, 5);
  retira_conjunto(d, 15);
  retira_conjunto(e, 25);
  retira_conjunto(f, 35);


  printf("\ntenta retirar os mesmos elementos novamente\n");

  if (retira_conjunto(c, 5) == -1)
    printf("\nConjunto c não contem o elemento 5\n");
  if (retira_conjunto(d, 15) == -1)
    printf("\nConjunto d não contem o elemento 15\n");
  if (retira_conjunto(e, 25) == -1)
    printf("\nConjunto e não contem o elemento 25\n");
  if (retira_conjunto(f, 35) == -1)
    printf("\nConjunto f não contem o elemento 35\n");
  
  printf("\nretira um elemento aleatório dos conjuntos\n");

  printf("\nimprime c original\n");
  imprime(c);
  printf("\nimprime c sem o elemento aleatório\n");
  retirar_um_elemento(c);
  imprime(c);
  printf("\nimprime d original \n");
  imprime(d);
  printf("\nimprime d sem o elemento aleatório\n");
  retirar_um_elemento(d);
  imprime(d);
  printf("\nimprime e original\n");
  imprime(e);
  printf("\nimprime e sem o elemento aleatório\n");
  retirar_um_elemento(e);
  imprime(e);
  printf("\nimprime f original\n");
  imprime(f);
  printf("\nimprime f sem o elemento aleatório\n");
  retirar_um_elemento(f);
  imprime(f);

  printf("\ndestroi os conjuntos\n");

  destroi_conjunto(c);
  destroi_conjunto(d);
  destroi_conjunto(e);
  destroi_conjunto(f);

  printf("\ncria novos conjuntos conjuntos\n");

  printf("\ninicializando conjuntos\n");

  conjunto_t *dife, *inter, *uniao, *copia, *sub;

  c = cria_conjunto(5);
  d = cria_conjunto(10);
  e = cria_conjunto(5);
  f = cria_conjunto(10);

  printf("\ntesta se os conjuntos estão vazios\n");

  if (conjunto_vazio(c))
    printf("\nConjunto c vazio\n");
  if (conjunto_vazio(d))
    printf("\nConjunto d vazio\n");
  if (conjunto_vazio(e))
    printf("\nConjunto e vazio\n");
  if (conjunto_vazio(f))
    printf("\nConjunto f vazio\n");

  printf("\ninserindo elementos em c\n");

  for (i = 0; i < 5; i++)
  { 
    insere_conjunto(c, i);
  }

  printf("\ninserindo elementos em d\n"); 

  for (i = 0; i < 10; i++)
  { 
    insere_conjunto(d, i);
  }

  printf("\nimprimindo os conjuntos\n");

  printf("\nimprime c\n");
  imprime(c);
  printf("\nimprime d\n");
  imprime(d);

  printf("\ntesta se o conjunto c está contido no conjunto d\n");

  if (contido(c, d))
    printf("\nConjunto c está contido no conjunto d\n");
  else
    printf("\nConjunto c não está contido no conjunto d\n");

  printf("\nimprime a diferença entre o conjunto c e d\n");
  
  dife = cria_diferenca(d, c);

  imprime(dife);

  printf("\nimprime a interseção entre o conjunto c e d\n");

  inter = cria_interseccao(c, d);

  imprime(inter);

  printf("\nimprime a união entre o conjunto c e d\n");

  uniao = cria_uniao(d, c);

  imprime(uniao);

  printf("\nimprime a cópia do conjunto c\n");

  copia = cria_copia(c);

  imprime(copia);

  printf("\ncria subconjunto\n");

  sub = cria_subconjunto(c, 5);

  imprime(sub);

  printf("\nredimensiona os conjuntos\n");

  redimensiona(c);
  redimensiona(d);

  printf("\ninserindo elementos em c\n");

  for (i = 5; i < 10; i++)
  { 
    insere_conjunto(c, i);
  }

  printf("\ninserindo elementos em d\n"); 

  for (i = 10; i < 20; i++)
  { 
    insere_conjunto(d, i);
  }

  printf("\nimprimindo os conjuntos\n");

  printf("\nimprime c\n");
  imprime(c);
  printf("\nimprime d\n");
  imprime(d);  

  printf("\ntesta a função de iterador\n");

  iniciar_iterador(c);
  iniciar_iterador(d);
  iniciar_iterador(e);
  iniciar_iterador(f);

  printf("\nimprime os elementos do conjunto c usando o iterador\n");

  for (i = 0; i < 10; i++)
  {
    printf("%d ", incrementar_iterador(c, &i));
  }

  printf("\nimprime os elementos do conjunto d usando o iterador\n");

  for (i = 0; i < 20; i++)
  {
    printf("%d ", incrementar_iterador(d, &i));
  }

  printf("\nDestroi os conjuntos\n");

  destroi_conjunto(c);
  destroi_conjunto(d);
  destroi_conjunto(e);
  destroi_conjunto(f);
  destroi_conjunto(dife);
  destroi_conjunto(inter);
  destroi_conjunto(uniao);
  destroi_conjunto(copia);
  destroi_conjunto(sub);

  printf("\nFim do teste\n");

  return 0;
}
