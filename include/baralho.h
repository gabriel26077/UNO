#ifndef BARALHO_H
#define BARALHO_H

//MACROS DE CARTAS ESPECIAIS
#define BARALHO_AS 1
#define BARALHO_J  11
#define BARALHO_Q  12
#define BARALHO_K  13
#define BARALHO_V  14
#define BARALHO_D  15
#define BARALHO_R  16
#define BARALHO_C  17 

//MACROS DE COMPARAÇÃO DE CARTA
#define INCOMPATIVEL 0 
#define COMPATIVEL 1
#define IGUAL 2


#define COPAS  0
#define ESPADAS 1
#define PAUS  2
#define OURO  3
#define NAIPE_ERRO 4
/// @brief 

struct  carta{
    char carta_str[15];
    char valor_str[5];
    char naipe_str[5];
    int naipe_int;
    int valor_int;
};

typedef struct carta Carta;
typedef struct baralho Baralho;

Baralho* cria_baralho();

int naipe_preferido(Baralho* baralho);

int compara_carta(Carta c1, Carta c2);

int adiciona_carta(Baralho* baralho, Carta carta);

int tamanho_baralho(Baralho* baralho);

int adiciona_carta_no_inicio(Baralho* baralho, Carta carta);

int acessa_carta(Baralho* baralho, int index, Carta* carta);

int descarta_carta(Baralho* baralho, int index);

int gira_baralho(Baralho* baralho); 

int destroi_baralho(Baralho* baralho);

void printa_baralho(Baralho* baralho);

void printa_de_tras_para_frente(Baralho* baralho);


#endif