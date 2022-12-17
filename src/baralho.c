#include "../include/baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no {
  Carta carta;
  struct no *proximo;
  struct no *anterior;
} No;

struct baralho {
  No *cabeca;
  No *cauda;
  int tam;
};

Baralho *cria_baralho() {
  Baralho *novo_baralho = (Baralho *)malloc(sizeof(Baralho));
  if (novo_baralho != NULL) { // se o baralho foi alocado com sucesso
    novo_baralho->cabeca =
        NULL; // aponta para nada pq não foi adicionada nenhuma carta
    novo_baralho->cauda = NULL;
    novo_baralho->tam = 0; // autoexplicativo
  }
  return novo_baralho;
}

int tamanho_baralho(Baralho *baralho) {
  if (baralho == NULL)
    return 0;
  return baralho->tam;
}

int adiciona_carta(Baralho *baralho, Carta carta) {
  if (baralho == NULL)
    return 0; // Baralho passado não existe

  No *novo_no = (No *)malloc(sizeof(No));
  if (novo_no == NULL)
    return 0; // Não foi possível alocar um novo nó

  novo_no->carta = carta;
  novo_no->proximo = NULL; // vai pro fim da lista

  if (baralho->tam == 0) {
    novo_no->anterior = NULL;
    baralho->cabeca = novo_no;
  } else {
    novo_no->anterior = baralho->cauda;
    baralho->cauda->proximo = novo_no;
  }

  baralho->cauda = novo_no;

  baralho->tam++; // atualiza a quantidade de cartas do baralho
  return 1;       // nada pegou fogo
}

int adiciona_carta_no_inicio(Baralho *baralho, Carta carta) {
  if (baralho == NULL)
    return 0; // Baralho passado não existe

  No *novo_no = (No *)malloc(sizeof(No));
  if (novo_no == NULL)
    return 0; // Não foi possível alocar um novo nó

  novo_no->carta = carta;
  novo_no->proximo = baralho->cabeca;
  novo_no->anterior = NULL;

  baralho->cabeca = novo_no;

  if (novo_no->proximo != NULL) {
    novo_no->proximo->anterior = novo_no;
  }

  if (baralho->tam == 0) {
    baralho->cauda = novo_no;
  }

  baralho->tam++; // atualiza a quantidade de cartas do baralho
  return 1;       // nada pegou fogo
}

int acessa_carta(Baralho *baralho, int index,Carta *carta) { // fotocópia de cartas ou método getter da deep web
  if (baralho == NULL || index >= baralho->tam)
    return 0; // baralho não existe ou índice passado excede a quantidade de
              // cartas que existem no baralho

  No *procurador = baralho->cabeca; //"entra" pro baralho
  for (int i = 0; i < index; i++) { // avança na estrutura de nós até chegar no
                                    // nó que corresponde ao index
    procurador = procurador->proximo; // esse é o jeito :/
  }
  *carta = procurador->carta; //"copia" a informação da carta encontrada para
                              //uma carta em branco.
  return 1;                   // esperamos que nada tenha pego fogo
}

int descarta_carta(Baralho *baralho, int index) {
  if (baralho == NULL || index >= baralho->tam)
    return 0; // baralho não existe ou índice passado excede a quantidade de
              // cartas que existem no baralho

  No *apagado = baralho->cabeca;

  if (index == 0) {
    if (baralho->tam == 1) {
      baralho->cauda = NULL;
    }
    baralho->cabeca = baralho->cabeca->proximo;
    free(apagado);
    baralho->tam--;
    return 1;
  }

  for (int i = 0; i < index; i++) {
    apagado = apagado->proximo;
  }

  if (apagado->anterior != NULL) {
    apagado->anterior->proximo = apagado->proximo;
  }

  if (apagado->proximo != NULL) {
    apagado->proximo->anterior = apagado->anterior;
  }

  free(apagado);
  baralho->tam--;
  return 1;
}

int gira_baralho(Baralho *baralho) {
  if (baralho == NULL)
    return 0;
  if (baralho->tam == 0 || baralho->tam == 1)
    return -1;

  baralho->cauda->proximo = baralho->cabeca;
  baralho->cabeca->anterior = baralho->cauda;
  baralho->cabeca->proximo->anterior = NULL;
  baralho->cabeca = baralho->cabeca->proximo;
  baralho->cauda->proximo->proximo = NULL;
  baralho->cauda = baralho->cauda->proximo;
  return 1;
}

int destroi_baralho(Baralho *baralho) {
  if (baralho == NULL)
    return 0;
  while (baralho->tam > 0)
    descarta_carta(baralho, 0);
  free(baralho);
  return 1;
}

void printa_baralho(Baralho *baralho) {
  if (baralho == NULL)
    return;
  fprintf(stderr, "\nMeu baralho [");
  No *aux = baralho->cabeca;
  for (int i = 0; i < baralho->tam; i++) {
    // printf("%c %s\n", aux->carta.valor, aux->carta.naipe);
    fprintf(stderr, " %s ", aux->carta.carta_str);
    aux = aux->proximo;
  }
  fprintf(stderr, "]\n");
}

void printa_de_tras_para_frente(Baralho *baralho) {
  if (baralho == NULL)
    return;
  No *aux = baralho->cauda;
  for (int i = 0; i < baralho->tam; i++) {
    printf("%s\n", aux->carta.carta_str);
    aux = aux->anterior;
  }
}

int compara_carta(Carta c1, Carta c2) {
    if(c1.valor_int == BARALHO_AS || c1.valor_int == BARALHO_C)return COMPATIVEL;
  if (strcmp(c1.carta_str,c2.carta_str)==0)
    return IGUAL;
  if (c1.naipe_int == c2.naipe_int || c1.valor_int == c2.valor_int)
    return COMPATIVEL;
  return INCOMPATIVEL;
}

int naipe_preferido(Baralho* baralho){
  Carta carta_fotocopia;
  int naipes[4]={0,0,0,0};
  //♥,♦, ♣, ♠.
  for(int i=0;i<tamanho_baralho(baralho);i++){
    acessa_carta(baralho, 0,&carta_fotocopia);
    if(carta_fotocopia.naipe_int==COPAS) naipes[COPAS]++;
    else if(carta_fotocopia.naipe_int==ESPADAS) naipes[ESPADAS]++;
    else if(carta_fotocopia.naipe_int==PAUS) naipes[PAUS]++;
    else if(carta_fotocopia.naipe_int== OURO) naipes[OURO]++; 
    gira_baralho(baralho);
  }
  int naipe_dominante = 0;
  for(int i=1; i<4; i++)
    if(naipes[naipe_dominante]>=naipes[i])naipe_dominante=i;

  return naipe_dominante;
  
}
