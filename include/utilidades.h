#ifndef MACRO_H
#define MACRO_H
#include "baralho.h"

//TIPOS DE AÇÂO
#define DISCARD 1
#define TURN 2
#define BUY 3
#define SAY 4

int guardarPlayers(char *str, char mat[][20]);

void my_strcpy(char *destino, char *origem, int n);

void quebra_complemento(char* entrada, Carta* carta);

int analisa_acao(char* acao);

void guardar_cartas(Baralho* baralho, char* string_de_cartas);

Carta converte_string_para_carta(char* str);

int converte_string_para_naipe(char* str);

void debug(char *message);
#endif