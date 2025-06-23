#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jogo.h"


void gerar_baralho(baralho_t **baralho_head, baralho_t baralho[], char naipe[][10])
{
    int numero_carta = 1, local_carta = 0;

    srand(time(NULL));


    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            baralho[local_carta].classe = numero_carta;   
            strcpy(baralho[local_carta].naipe, naipe[j]); 
            local_carta++;
        }
        numero_carta++;
    }

    
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < QUANT_BARAL; i++)
        {
            int local_carta_rand = (rand() % (QUANT_BARAL - 1)) + 0;
            baralho_t temp;
            
            temp = baralho[i];
            baralho[i] = baralho[local_carta_rand];
            baralho[local_carta_rand] = temp;

        }

    }

    *baralho_head = &baralho[0];

    for (int i = 0; i < QUANT_BARAL - 1; i++)
    {
        baralho[i].next = &baralho[i + 1];
    }
    baralho[QUANT_BARAL - 1].next = NULL;
}

void exibir_cartas(baralho_t *baralho_head)
{
    baralho_t *atual = baralho_head;

    printf("\nBaralho encadeado:\n");

    while (atual != NULL)
    {
        if(atual->classe == 1) {printf("Classe: AS, Naipe: %s\n", atual->naipe);}
        else if(atual->classe == 11) {printf("Classe: J, Naipe: %s\n", atual->naipe);}
        else if(atual->classe == 12) {printf("Classe: Q, Naipe: %s\n", atual->naipe);}
        else if(atual->classe == 13) {printf("Classe: K, Naipe: %s\n", atual->naipe);}
        else{ printf("Classe: %d, Naipe: %s\n", atual->classe, atual->naipe); }
        
        atual = atual->next; 
    }
}

void entregar_cartas(baralho_t **baralho_head, baralho_t **player_head)
{
    baralho_t *ultima_carta = NULL;
    int contador = 0;

    while (contador < 6)
    {
        baralho_t *carta_atual = *baralho_head; 
        *baralho_head = carta_atual->next;      
        carta_atual->next = NULL;               

        if (*player_head == NULL) 
        {
            *player_head = carta_atual; 
        }
        else
        {
            ultima_carta->next = carta_atual; 
        }

        ultima_carta = carta_atual; 
        contador++;
    }
}

int comprar_carta(baralho_t **baralho_head, baralho_t **player_head)
{
    if (*baralho_head == NULL)
    {
        printf("\nNao da para comprar, nao tem cartas nesse monte");
        return -1;
    }

    baralho_t *carta_atual = *baralho_head;

    *baralho_head = carta_atual->next;

    carta_atual->next = *player_head;
    *player_head = carta_atual;

    return 0;
}

int descarta_carta(baralho_t **player_head, baralho_t **descarte, baralho_t carta_escolhida)
{
    baralho_t *carta_atual = *player_head;
    baralho_t *carta_anterior = NULL;

    while (carta_atual != NULL)
    {

        if (carta_atual->classe == carta_escolhida.classe && strcmp(carta_atual->naipe, carta_escolhida.naipe) == 0)
        {
            if (carta_anterior == NULL)
            {
                *player_head = carta_atual->next; 
            }
            else
            {
                carta_anterior->next = carta_atual->next; 
            }
            
            carta_atual->next = *descarte;
            *descarte = carta_atual;

            printf("\nCarta descartada com sucesso");
            return 0;
        }

        carta_anterior = carta_atual;
        carta_atual = carta_atual->next;
    }

    printf("\nEssa carta nao esta na sua mao, tente novamente: ");
    return -1;
}

void atualizar_ponto(int ganhador)
{
    int j1 = 0, j2 = 0;

    FILE *file_r = fopen("placar.txt", "r");
    if (file_r != NULL)
    {
        fscanf(file_r, "%d %d", &j1, &j2);
        fclose(file_r);
    }

    if (ganhador == 1){j1++;}
    if (ganhador == 2){j2++;}
        

    FILE *file_w = fopen("placar.txt", "w");
    if (file_w == NULL)
    {
        printf("Arquivo 'placar.txt' nao foi criado\n");
        return;
    }

    fprintf(file_w, "%d %d", j1, j2);
    fclose(file_w);

    printf("Placar J1 %d | J2 %d\n", j1, j2);
}

void mostra_placar()
{
    int j1 = 0, j2 = 0;

    FILE *file_r = fopen("placar.txt", "r");
    if (file_r != NULL)
    {
        fscanf(file_r, "%d %d", &j1, &j2);
        fclose(file_r);
    }

    printf("\nj1 %d | j2 %d", j1, j2);
}

baralho_t escolher_carta()
{
    baralho_t carta;
    char valor[10];

    do
    {
        printf("\nDigite o valor da carta, ex(AS, 2-10, J=11, Q=12, K=13): ");
        scanf("%8s", valor);

        if (strcmp(valor, "AS") == 0 || strcmp(valor, "A") == 0) { carta.classe = 1; }
        else if (strcmp(valor, "J") == 0) { carta.classe = 11; }
        else if (strcmp(valor, "Q") == 0) { carta.classe = 12; }
        else if (strcmp(valor, "K") == 0) { carta.classe = 13; }
        else
        {
            int num = atoi(valor);
            if (num >= 2 && num <= 10){ carta.classe = num; }
            else { carta.classe = 0; }
        }

        if (carta.classe < 1 || carta.classe > 13)
        {
            printf("Valor invalido. Tente escolher um valor entre AS até K\n");
        }

    } while (carta.classe < 1 || carta.classe > 13);

    do
    {
        printf("Digite o naipe da carta: OUROS, ESPADAS, PAUS ou COPAS: ");
        scanf("%8s", carta.naipe);

        if (strcmp(carta.naipe, "COPAS") == 0 || strcmp(carta.naipe, "OUROS") == 0 || strcmp(carta.naipe, "ESPADAS") == 0 || strcmp(carta.naipe, "PAUS") == 0)
        {
            break;
        }

        else
        {
            printf("\nNaipe invalido. Tente digitar o nome do naipe escolhido: OUROS, COPAS, ESPADAS ou PAUS.\n");
            printf("\n========================\n");
        }

    } while (1);

    return carta;
}

int trinca(baralho_t **player_head, baralho_t conjunto[])
{
    baralho_t *carta_atual = *player_head;
    int encontrado = 0;

    for (int i = 0; i < 3; i++)
    {
        printf("\nCarta %d", i + 1);
        conjunto[i] = escolher_carta();
    }

    for (int i = 0; i < 3; i++)
    {
        baralho_t *carta_atual = *player_head; 
        int encontrado = 0;

        while (carta_atual != NULL)
        {
            if (carta_atual->classe == conjunto[i].classe &&
                strcmp(carta_atual->naipe, conjunto[i].naipe) == 0)
            {
                encontrado = 1;
                break;
            }

            carta_atual = carta_atual->next;
        }

        if (!encontrado)
        {
            printf("\nA carta %d nao tem em sua mao", i);
            return -1;
        }
    }


    int paus = 0, ouros = 0, copas = 0, espadas = 0;
    if (conjunto[0].classe == conjunto[1].classe && conjunto[0].classe == conjunto[2].classe)
    {
        for (int i = 0; i < 3; i++)
        {
            if (strcmp(conjunto[i].naipe, "PAUS") == 0) { paus++; }
            if (strcmp(conjunto[i].naipe, "OUROS") == 0) { ouros++; }
            if (strcmp(conjunto[i].naipe, "COPAS") == 0) { copas++; }
            if (strcmp(conjunto[i].naipe, "ESPADAS") == 0) { espadas++; }
        }
        if (paus > 1 || ouros > 1 || copas > 1 || espadas > 1)
        {
            printf("\nTem naipes iguais");
            return -1;
        }
    }
    else
    {
        printf("\nAs classes sao diferentes");
        return -1;
    }

    return 0;
}

int sequencia(baralho_t **player_head, baralho_t conjunto[])
{
    baralho_t *carta_atual = *player_head;
    int encontrado = 0;


    for (int i = 0; i < 3; i++)
    {
        printf("\nCarta %d", i + 1);
        conjunto[i] = escolher_carta();
    }

 
    for (int i = 0; i < 3; i++)
    {
        baralho_t *carta_atual = *player_head; 
        int encontrado = 0;

        while (carta_atual != NULL)
        {
            if (carta_atual->classe == conjunto[i].classe &&
                strcmp(carta_atual->naipe, conjunto[i].naipe) == 0)
            {
                encontrado = 1;
                break; 
            }

            carta_atual = carta_atual->next;
        }

        if (!encontrado)
        {
            printf("\nA carta %d nao tem em sua mao", i);
            return -1;
        }
    }


    int paus = 0, ouros = 0, copas = 0, espadas = 0;
    if (conjunto[0].classe != conjunto[1].classe && conjunto[0].classe != conjunto[2].classe && conjunto[1].classe != conjunto[2].classe)
    {
        for (int i = 0; i < 3; i++)
        {
            if (strcmp(conjunto[i].naipe, "PAUS") == 0) { paus++; }
            if (strcmp(conjunto[i].naipe, "OUROS") == 0) { ouros++; }
            if (strcmp(conjunto[i].naipe, "COPAS") == 0) { copas++; }
            if (strcmp(conjunto[i].naipe, "ESPADAS") == 0) { espadas++; }
        }
        if (paus == 3 || ouros == 3 || copas == 3 || espadas == 3){}
        else
        {
            printf("\nA sequencia tem naipes diferentes\n");
            return -1;
        }
    }
    else
    {
        printf("\nA sequencia tem numeros iguais\n");
        return -1;
    }


    for (int i = 0; i < 3 - 1; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (conjunto[i].classe > conjunto[j].classe)
            {
                baralho_t temp_conjunto = conjunto[i];
                conjunto[i] = conjunto[j];
                conjunto[j] = temp_conjunto;
            }
        }
    }

    if (conjunto[1].classe != conjunto[0].classe + 1 || conjunto[2].classe != conjunto[1].classe + 1)
    { printf("\nA sequencia pula a ordem\n"); return -1; }

    return 0;
}