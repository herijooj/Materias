#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"

/* --- \/ definição de constantes \/ --- */

#define temp_min 0
#define temp_maximo 34944
#define quant_lugares 8
#define quant_rumores 30
#define quant_pessoas 100
#define tamanho_mundo 20000

#define extro_min 0
#define extro_max 100
#define pac_min 0
#define pac_max 100
#define idade_min 18
#define idade_max 100
#define lotacao_min 5
#define lotacao_max 30

#define caso_chegada 1
#define caso_saida 2
#define caso_disseminacao 3
#define caso_fim 4

/* --- \/ structs \/ --- */

/* posicao */
typedef struct posicao {
  int x;
  int y;
} posicao_m;

/* pessoa */
typedef struct pessoa {
  int id;
  int extroversao;
  int paciencia;
  int idade;
  conjunto_t *crc;
} pessoa_m;

/* local */
typedef struct local {
  int id;
  int lotacao_maxima;
  conjunto_t *pessoas_lugar;
  fila_t *fila;
  posicao_m localizacao;
} local_m;

/* mundo */
typedef struct mundo {
  int tempo_atual;
  pessoa_m pessoas[quant_pessoas];
  local_m locais[quant_lugares];
  conjunto_t *rumores;
  int n_pessoas;
  int n_locais;
  posicao_m n_tamanho_mundo;
} mundo_m;

/* dados de chegada */
typedef struct dados_chegada {
  int id_pessoa;
  int id_local;
} dados_chegada_m;

/* dados de saida */
typedef struct dados_saida {
  int id_pessoa;
  int id_local;
} dados_saida_m;

/* dados de disseminacao */
typedef struct dados_disseminacao {
  conjunto_t *conj_rumores;
  int id_pessoa_origem;
  int id_local;
} dados_disseminacao_m;

/* --- \/ funções secundárias \/ --- */

/* função que calcula a distancia entre dois pontos */
int distancia(int x, int y)
{
  return (int)sqrt(pow(x, 2) + pow(y, 2));
}

/* função que gera um número aleatório entre um intervalo */
int rng(int min, int max)
{
  return rand() % (max - min + 1) + min;
}

/* --- \/ funções de eventos de criação \/ --- */

/* função que gera um evento de chegada */
void gera_chegada(int tempo, pessoa_m pessoa, local_m local, lef_t *eventos)
{
  evento_t evento;
  dados_chegada_m chegada;

  chegada.id_pessoa = pessoa.id;
  chegada.id_local = local.id;

  evento.tempo = tempo;
  evento.tipo = caso_chegada;
  evento.tamanho = sizeof(dados_chegada_m);
  evento.dados = (void *)&chegada;

  adiciona_ordem_lef(eventos, (void *)&evento);
}

/* função que gera um evento de saída */
void gera_saida(int tempo, pessoa_m pessoa, local_m local, lef_t *eventos)
{
  evento_t evento;
  dados_saida_m saida;

  saida.id_pessoa = pessoa.id;
  saida.id_local = local.id;

  evento.tempo = tempo;
  evento.tipo = caso_saida;
  evento.tamanho = sizeof(dados_saida_m);
  evento.dados = (void *)&saida;

  adiciona_ordem_lef(eventos, (void *)&evento);
}

/* função que gera um evento de disseminação */
void gera_disseminacao(int tempo, pessoa_m pessoa, local_m local, lef_t *eventos)
{
  evento_t evento;
  dados_disseminacao_m disseminacao;
  int nrd = pessoa.extroversao / 10;

  disseminacao.id_pessoa_origem = pessoa.id;
  disseminacao.id_local = local.id;
  disseminacao.conj_rumores = cria_subconjunto(pessoa.crc, nrd);

  evento.tempo = tempo;
  evento.tipo = caso_disseminacao;
  evento.tamanho = sizeof(dados_disseminacao_m);
  evento.dados = (void *)&disseminacao;

  adiciona_ordem_lef(eventos, (void *)&evento);
}

/* função que gera um evento de fim */
void gera_fim(lef_t *eventos)
{
  evento_t evento;

  evento.tempo = temp_maximo;
  evento.tipo = caso_fim;
  evento.tamanho = 0;
  evento.dados = NULL;
  adiciona_ordem_lef(eventos, (void *)&evento);
}

/* --- \/ funções criadoras principais \/ --- */

/* função que gera os rumores do mundo*/
void gera_rumores(conjunto_t *rumores)
{
  int count;

  for (count = 1; count <= quant_rumores; count++)
    insere_conjunto(rumores, count);
}

/* função que gera os locais do mundo */
void cria_locais(local_m locais[])
{
  local_m local;
  int count;

  for (count = 1; count <= quant_lugares; count++)
    {
      local.id = count;
      local.lotacao_maxima = rng(5, 30);
      local.localizacao.x = rng(0, tamanho_mundo - 1);
      local.localizacao.y = rng(0, tamanho_mundo - 1);
      local.pessoas_lugar = cria_conjunto(local.lotacao_maxima);
      local.fila = cria_fila();

      locais[count - 1] = local;
    }
}

/* função que gera as pessoas do mundo */
void cria_pessoas(pessoa_m pessoas[], local_m locais[], conjunto_t rumores[], lef_t *eventos)
{
  pessoa_m pessoa;
  int count;

  for (count = 1; count <= quant_pessoas; count++)
    {
      pessoa.id = count;
      pessoa.extroversao = rng(extro_min, extro_max);
      pessoa.paciencia = rng(pac_min, pac_max);
      pessoa.idade = rng(idade_min, idade_max + 1);
      pessoa.crc = cria_subconjunto(rumores, rng(1, 5));

      pessoas[count - 1] = pessoa;

      gera_chegada(rng(0, 96 * 7), pessoa, locais[rng(1, quant_lugares) - 1], eventos);
    }
}

/* função que gera o mundo */
mundo_m cria_mundo(lef_t *eventos)
{
  mundo_m mundo;

  mundo.tempo_atual = 0;
  mundo.n_pessoas = quant_pessoas;
  mundo.n_locais = quant_lugares;
  mundo.n_tamanho_mundo.x = tamanho_mundo;
  mundo.n_tamanho_mundo.y = tamanho_mundo;

  mundo.rumores = cria_conjunto(quant_rumores);
  gera_rumores(mundo.rumores);
  cria_locais(mundo.locais);
  cria_pessoas(mundo.pessoas, mundo.locais, mundo.rumores, eventos);

  gera_fim(eventos);

  return mundo;
}

/* --- \/ funções de evento de execução \/ --- */

/* função que executa um evento de chegada */
void evento_chegada(mundo_m mundo, lef_t *eventos, int id_pessoa, int id_local)
{
  local_m local = mundo.locais[id_local - 1];
  pessoa_m pessoa = mundo.pessoas[id_pessoa - 1];
  int tempo_permanencia;

  if (cardinalidade(local.pessoas_lugar) == local.lotacao_maxima)
    {
      if ((pessoa.paciencia / 4 - tamanho_fila(local.fila)) > 0)
        {
          insere_fila(local.fila, id_pessoa);
          printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), FILA %2d\n", mundo.tempo_atual, pessoa.id, local.id, cardinalidade(local.pessoas_lugar), local.lotacao_maxima, tamanho_fila(local.fila));
        }
      else
        {
          gera_saida(mundo.tempo_atual, pessoa, local, eventos);
          printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), DESISTE\n", mundo.tempo_atual, pessoa.id, local.id, cardinalidade(local.pessoas_lugar), local.lotacao_maxima);
        }
    }
  else
    {
      insere_conjunto(local.pessoas_lugar, id_pessoa);
      printf("%6d:CHEGA Pessoa %4d Local %2d (%2d/%2d), ENTRA\n", mundo.tempo_atual, pessoa.id, local.id, cardinalidade(local.pessoas_lugar), local.lotacao_maxima);
      tempo_permanencia = 1 + (pessoa.paciencia / 10 + rng(2, 6));
      gera_disseminacao(mundo.tempo_atual + rng(0, tempo_permanencia), pessoa, local, eventos);
      gera_saida(mundo.tempo_atual + tempo_permanencia, pessoa, local, eventos);
    }
}

/* função que executa um evento de saída */
void evento_saida(mundo_m mundo, lef_t *eventos, int id_pessoa, int id_local)
{
  local_m local = mundo.locais[id_local - 1];
  pessoa_m pessoa = mundo.pessoas[id_pessoa - 1];
  int pessoa_fila;
  local_m destino;
  int tdl, dist, velocidade;

  destino = mundo.locais[rng(1, quant_lugares) - 1];
  dist = distancia(destino.localizacao.x, local.localizacao.y);
  velocidade = 100 - (pessoa.idade - 40);
  tdl = dist / velocidade;

  retira_conjunto(local.pessoas_lugar, pessoa.id);

  gera_chegada(mundo.tempo_atual + (tdl / 15), pessoa, destino, eventos);
  if (!fila_vazia(local.fila))
    {
      retira_fila(local.fila, &pessoa_fila);
      gera_chegada(mundo.tempo_atual, mundo.pessoas[pessoa_fila - 1], local, eventos);
      printf("%6d:SAIDA Pessoa %4d Local %2d (%2d/%2d), REMOVE FILA %2d\n", mundo.tempo_atual, pessoa.id, local.id, cardinalidade(local.pessoas_lugar), local.lotacao_maxima, pessoa_fila);
      return;
    }
  printf("%6d:SAIDA Pessoa %4d Local %2d (%2d/%2d)\n", mundo.tempo_atual, pessoa.id, local.id, cardinalidade(local.pessoas_lugar), local.lotacao_maxima);
}

/* função que executa um evento de disseminação */
void evento_disseminacao(mundo_m mundo, int id_pessoa, int id_local, conjunto_t *conj_rumores)
{
  local_m local = mundo.locais[id_local - 1];
  pessoa_m pessoa_origem = mundo.pessoas[id_pessoa - 1];
  int id_pessoa_destino;
  int iterador_rumor, iterador_pessoa, rumor;

  printf("%6d:RUMOR Pessoa %4d Local %2d ", mundo.tempo_atual, pessoa_origem.id, local.id);

  iniciar_iterador(conj_rumores);
  for (iterador_rumor = 0; iterador_rumor < cardinalidade(conj_rumores); iterador_rumor++)
    {
      incrementar_iterador(conj_rumores, &rumor);
      iniciar_iterador(local.pessoas_lugar);
      for (iterador_pessoa = 0; iterador_pessoa < cardinalidade(local.pessoas_lugar); iterador_pessoa++)
        {
          incrementar_iterador(local.pessoas_lugar, &id_pessoa_destino);
          if (rng(extro_min, extro_max) < mundo.pessoas[id_pessoa_destino - 1].extroversao)
            if (insere_conjunto(mundo.pessoas[id_pessoa_destino - 1].crc, rumor))
              printf("(P%d/R%d) ", mundo.pessoas[id_pessoa_destino - 1].id, rumor);
        }
    }
  printf("\n");
}

/* --- \/ main \/ --- */

int main()
{
  int fim_mundo = 0;

  mundo_m mundo;
  lef_t *eventos;
  evento_t *evento_atual;
  dados_chegada_m *dados_chegada;
  dados_saida_m *dados_saida;
  dados_disseminacao_m *dados_disseminacao;

  eventos = cria_lef();
  mundo = cria_mundo(eventos);

  while ((evento_atual = obtem_primeiro_lef(eventos)) != NULL)
    {
      mundo.tempo_atual = evento_atual->tempo;

      switch (evento_atual->tipo)
      {
        case caso_chegada:
        {
          dados_chegada = (dados_chegada_m*)evento_atual->dados;
          if (fim_mundo == 0)
            {
              evento_chegada(mundo, eventos, dados_chegada->id_pessoa, dados_chegada->id_local);
            }
          free(dados_chegada);
          free(evento_atual);
          break;
        }

        case caso_saida:
        {
          dados_saida = (dados_saida_m*)evento_atual->dados;
          if (fim_mundo == 0)
            {
              evento_saida(mundo, eventos, dados_saida->id_pessoa, dados_saida->id_local);
            }
          free(dados_saida);
          free(evento_atual);
          break;
        }

        case caso_disseminacao:
        {
          dados_disseminacao = (dados_disseminacao_m*)evento_atual->dados;
          if (fim_mundo == 0)
            {
              evento_disseminacao(mundo, dados_disseminacao->id_pessoa_origem, dados_disseminacao->id_local, dados_disseminacao->conj_rumores);
            }
          destroi_conjunto(dados_disseminacao->conj_rumores);
          free(dados_disseminacao);
          free(evento_atual);
          break;
        }

        case caso_fim:
        {
          free(evento_atual->dados);
          free(evento_atual);
          fim_mundo = 1;
          int count;

          for (count = 0; count < mundo.n_pessoas; count++)
            destroi_conjunto(mundo.pessoas[count].crc);
          for (count = 0; count < mundo.n_locais; count++)
            {
              destroi_conjunto(mundo.locais[count].pessoas_lugar);
              destroi_fila(mundo.locais[count].fila);
            }

          destroi_conjunto(mundo.rumores);

          break;
        }
      }
    }

  destroi_lef(eventos);

  return 0;
}
