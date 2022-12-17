#ifndef LISTA_DE_EVENTOS_H
#define LISTA_DE_EVENTOS_H

#include "baralho.h"

/// @brief
struct evento {
  char action[15];
  char complemento[20];
  char complemento2[20];
  int evento_de_carta; // 0 ou 1
};

typedef struct evento Evento;
typedef struct lista_de_eventos Lista_de_eventos;

Lista_de_eventos *cria_lista_de_eventos();

int adiciona_evento(Lista_de_eventos *lista_de_eventos, Evento evento);

int tamanho_lista_de_eventos(Lista_de_eventos *lista_de_eventos);

int adiciona_evento_no_inicio(Lista_de_eventos *lista_de_eventos,
                              Evento evento);

int acessa_evento(Lista_de_eventos *lista_de_eventos, int index,
                  Evento *evento);

int descarta_evento(Lista_de_eventos *lista_de_eventos, int index);

int gira_lista_de_eventos(Lista_de_eventos *lista_de_eventos);

int destroi_lista_de_eventos(Lista_de_eventos *lista_de_eventos);

#endif