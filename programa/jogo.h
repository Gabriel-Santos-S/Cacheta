#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>

#define QUANT_BARAL 52

typedef struct baralho {
    int classe;
    char naipe[10];
    struct baralho *next;
} baralho_t;

void gerar_baralho(baralho_t **baralho_head, baralho_t baralho_gerado[], char naipe[][10]);
void exibir_cartas(baralho_t *baralho_head);
void entregar_cartas(baralho_t **baralho_head, baralho_t **player_head);
int comprar_carta(baralho_t **baralho_head, baralho_t **player_head);
int descarta_carta(baralho_t **player_head, baralho_t **descarte, baralho_t carta_escolhida);
void atualizar_ponto(int ganhador);
void mostra_placar();
baralho_t escolher_carta();
int trinca(baralho_t **player_head, baralho_t conjunto[]);
int sequencia(baralho_t **player_head, baralho_t conjunto[]);

#endif