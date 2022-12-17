// gcc main.c baralho.c lista_de_eventos.c utilidades.c -o bicho
#include "../include/baralho.h"
#include "../include/lista_de_eventos.h"
#include "../include/utilidades.h"
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10


int main() {
  int houve_compra = FALSE;
  int aux_boleano = FALSE;
  char temp[MAX_LINE];
  char my_id[MAX_ID_SIZE];
  char listaPlayers[10][20];
  int qtdPlayers;
  Baralho *minhas_cartas = cria_baralho();

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  scanf("PLAYERS %[^\n]\n", temp);
  qtdPlayers = guardarPlayers(temp, listaPlayers);

  scanf("YOU %s\n", my_id);

  scanf("HAND %[^\n]\n", temp);
  //fprintf(stderr, "!!! %s  !!!", temp);
  guardar_cartas(minhas_cartas, temp);


  Carta carta_fotocopia;

  scanf("TABLE %s\n", temp);

  char id[MAX_ID_SIZE];
  char action[MAX_ACTION];
  char complement[MAX_LINE];
  char complement2[MAX_LINE];

  Evento jogada;
  Lista_de_eventos *historico = cria_lista_de_eventos();

  strcpy(jogada.action, "TABLE");

  strcpy(jogada.complemento, temp);
  strcpy(jogada.complemento2, "NULL");
  adiciona_evento_no_inicio(historico, jogada);
  Evento testeee1;
  acessa_evento(historico, 0, &testeee1);

  while (1) {

    do {

      strcpy(complement2, "NULL");

      scanf("%s %s", action, complement);

      if (analisa_acao(action) == DISCARD &&
          (complement[0] == 'A' || complement[0] == 'C')) {
        scanf("%s", complement2);
      }
      strcpy(jogada.action, action);
      strcpy(jogada.complemento, complement);
      strcpy(jogada.complemento2, complement2);
      
      adiciona_evento_no_inicio(historico, jogada);
    } while (strcmp(action, "TURN") || strcmp(complement, my_id)); // DAKIIIIIIIII PARA BAIXO
    
    //fprintf(stderr, "Quantidade de cartas %d\n",tamanho_baralho(minhas_cartas));

    //fprintf(stderr, "tamanho do histórico %d\n",tamanho_lista_de_eventos(historico));

    Evento evento_fotocopia;
    //fprintf(stderr,"\n#########  Lista_de_Eventos ########\n");
    houve_compra = FALSE;
    do {
      descarta_evento(historico, 0); // Descarta primeiro evento
      
      acessa_evento(historico, 0, &evento_fotocopia);
      //fprintf(stderr,"\n%s %s %s\n", evento_fotocopia.action,evento_fotocopia.complemento,evento_fotocopia.complemento2);
      

      if (analisa_acao(evento_fotocopia.action)==BUY && houve_compra == FALSE){
        houve_compra = TRUE;
      }

    } while (analisa_acao(evento_fotocopia.action) != DISCARD);
    //Minha vez
    printa_baralho(minhas_cartas);

    //fprintf(stderr,"\n---------- Fim Da Lista_de_Eventos ----------\n");
    Carta carta_que_esta_na_mesa;
    Evento meu_evento;
    carta_que_esta_na_mesa = converte_string_para_carta(evento_fotocopia.complemento);

    // lida caso o oponente mande comprar 2
    Carta comprar;
    char str[10];
    
    if (strcmp("NULL", evento_fotocopia.complemento2) != 0 && (carta_que_esta_na_mesa.valor_int == BARALHO_AS || carta_que_esta_na_mesa.valor_int == BARALHO_C)) {
      carta_que_esta_na_mesa.naipe_int = converte_string_para_naipe(evento_fotocopia.complemento2);
      strcpy(carta_que_esta_na_mesa.naipe_str, evento_fotocopia.complemento2);
    }
    //fprintf(stderr, "ESTADO DO HOUVE COMPRA %s\n",houve_compra? "TRUE":"FALSE");
    if (carta_que_esta_na_mesa.valor_int == BARALHO_V && houve_compra == FALSE) {
      printf("BUY 2\n");
      strcpy(meu_evento.action,"BUY");
      strcpy(meu_evento.complemento,"2");
      for (int i = 0; i < 2; i++) {
        scanf("%s", str);
        //fprintf(stderr, "###  \"%s\"  ###", str);
        comprar = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, comprar);
      }
    }
    // lida caso o oponenete mande comprar 4
    else if (carta_que_esta_na_mesa.valor_int == BARALHO_C && houve_compra == FALSE) {
      printf("BUY 4\n");
      strcpy(meu_evento.action,"BUY");
      strcpy(meu_evento.complemento,"4");
      for (int i = 0; i < 4; i++) {
        scanf("%s", str);
        //fprintf(stderr, "###  \"%s\"  ###", str);
        comprar = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, comprar);
      }
    }else{

    // JOGAR

      Carta carta_na_mao; // fotocopia
      int comparacao = INCOMPATIVEL;
      for (int i = 0; i < tamanho_baralho(minhas_cartas); i++) {
        acessa_carta(minhas_cartas, 0, &carta_na_mao);

        //fprintf(stderr, "Carta na mao: %s %d %d-- ", carta_na_mao.carta_str, carta_na_mao.valor_int, carta_na_mao.naipe_int);
        //fprintf(stderr, "Carta na mesa: '%s%s %d %d'\n", carta_que_esta_na_mesa.valor_str, carta_que_esta_na_mesa.naipe_str, carta_que_esta_na_mesa.valor_int, carta_que_esta_na_mesa.naipe_int);

        comparacao = compara_carta(carta_na_mao, carta_que_esta_na_mesa);
      

        //fprintf(stderr, "comparacao: %d\n", comparacao);

        if (comparacao == COMPATIVEL || comparacao == IGUAL){
            //fprintf(stderr,"\n### DEU CERTO BREIKEI AQUI###\n");
            break;
          }
        gira_baralho(minhas_cartas);
      }

      if (comparacao == INCOMPATIVEL) {
        printf("BUY 1\n");
        scanf("%s", str);
        Carta compra1 = converte_string_para_carta(str);
        adiciona_carta_no_inicio(minhas_cartas, compra1);
        strcpy(meu_evento.action,"BUY");
        strcpy(meu_evento.complemento,"1");
        strcpy(meu_evento.complemento2,"NULL");


        //fprintf(stderr, "###  \"%s\"  ###", str);
        
        
      }else{// ♥, ♦, ♣, ♠.

        //fprintf(stderr,"\n### DEVERIA JOGAR ALGO###\n");
        //fprintf(stderr,"\n# '%s' -- comparação com 'A': %d #\n", carta_na_mao.valor, strcmp(carta_na_mao.valor,"A"));
        printf("DISCARD %s", carta_na_mao.carta_str);
        strcpy(meu_evento.action,"DISCARD");
        strcpy(meu_evento.complemento,carta_na_mao.carta_str);
        if(carta_na_mao.valor_int == BARALHO_AS || carta_na_mao.valor_int == BARALHO_C){
          strcpy(meu_evento.complemento,carta_na_mao.carta_str);        
          //fprintf(stderr,"\n### DEVERIA PRINTAR UM NOVO NAIPE ###\n");
          int naipe_da_vez = naipe_preferido(minhas_cartas);
          //fprintf(stderr,"\nNAIPE DA VEZ: %d\n", naipe_da_vez);
          switch(naipe_da_vez){
            case PAUS:
              //fprintf(stderr,"\n### NOVO NAIPE: PAUS ###\n");
              printf(" ♣\n");
              strcpy(meu_evento.complemento2,"♣");
              break;
            case OURO:
              //fprintf(stderr,"\n### NOVO NAIPE: OUROS ###\n");
              strcpy(meu_evento.complemento2,"♦");
              printf(" ♦\n");
              break;
            case COPAS:
              //fprintf(stderr,"\n### NOVO NAIPE: COPAS ###\n");
              strcpy(meu_evento.complemento2,"♥");
              printf(" ♥\n");
              break;
            case ESPADAS:
              //fprintf(stderr,"\n### NOVO NAIPE: ESPADAS ###\n");
              strcpy(meu_evento.complemento2,"♠");
              printf(" ♠\n");
              break;
          }
        }else{
          strcpy(meu_evento.complemento2,"NULL");
          printf("\n");
        }

        //fprintf(stderr,"\n### My event: %s %s ###\n","DISCARD", carta_na_mao.carta_str);
        descarta_carta(minhas_cartas, 0);
        carta_que_esta_na_mesa.naipe_int = converte_string_para_naipe(meu_evento.complemento2);
      }
        
        

    }
    adiciona_evento_no_inicio(historico,meu_evento);
    Evento add;
    acessa_evento(historico, 0, &add);
  }
  return 0;
}
