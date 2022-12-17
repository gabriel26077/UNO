#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "../include/baralho.h"
#include "../include/utilidades.h"

void corta_string(char* str, char* delimitadores){
    for(int i=0;str[i]!='\0' && i<4;i++){
        for(int j=0;delimitadores[j]!='\0' && j<4;j++){
            if(str[i]==delimitadores[j])str[i]='\0';
        }
    }
}

Carta converte_string_para_carta(char* str){
    char strcopy[strlen(str)];
    strcpy(strcopy, str);
    Carta carta;
    strcpy(carta.carta_str,strcopy);
    //♥, 7♦, 7♣, 7♠


    if(strstr(strcopy,"♥")){

        carta.naipe_int = COPAS;
        strcpy(carta.valor_str, "♥");

    }else if(strstr(strcopy,"♦")){

        carta.naipe_int = OURO;
        strcpy(carta.valor_str, "♦");

    }else if(strstr(strcopy,"♣")){

        carta.naipe_int = PAUS;
        strcpy(carta.valor_str, "♣");

    }else if(strstr(strcopy,"♠")){

        carta.naipe_int = ESPADAS;
        strcpy(carta.valor_str, "♠");

    }else{

        carta.naipe_int = NAIPE_ERRO;
        strcpy(carta.valor_str, "ERRO");
        strcpy(carta.carta_str, "CARTA_ERRO");

    }
    
    strtok(strcopy,"♠");
    if(carta.naipe_int != NAIPE_ERRO){
      
      printf("'%s'", strcopy);
      //Aqui a função strtok está servindo somente para por um /0 quando aparecer um naipe na _srt. O que faz com que isso seja possível é o fato de que todos os naipes começam com os mesmos bytes
      
      
      strcpy(carta.valor_str,strcopy);
      if(str[0]=='A')carta.valor_int = BARALHO_AS;
      else if(str[0]=='J')carta.valor_int = BARALHO_J;
      else if(str[0]=='Q')carta.valor_int = BARALHO_Q;
      else if(str[0]=='K')carta.valor_int = BARALHO_K;
      else if(str[0]=='D')carta.valor_int = BARALHO_D;
      else if(str[0]=='V')carta.valor_int = BARALHO_V;
      else if(str[0]=='R')carta.valor_int = BARALHO_R;
      else if(str[0]=='C')carta.valor_int = BARALHO_C;

      else carta.valor_int = atoi(strcopy);
  

  }

    return carta;

}

//4♥
int main(){
    Carta c = converte_string_para_carta("4♥");

    printf("\n%s\n", c.carta_str);
    printf("valor: %d\n", c.valor_int);
    printf("naipe: %d\n", c.naipe_int);

}