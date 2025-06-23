#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

int main()
{

    baralho_t *baralho_head = NULL, *jogador[2] = {NULL, NULL}, *descarte = NULL, *indisponivel = NULL;
    baralho_t baralho[QUANT_BARAL];
    baralho_t carta_escolhida;
    baralho_t conjunto[3];
    char naipe[4][10] = {"PAUS", "OUROS", "COPAS", "ESPADAS"};
    int opcao = 0, validade = 0, ganhador = 0;

    
    gerar_baralho(&baralho_head, baralho, naipe);

    for (int i = 0; i < 2; i++)
    {
        entregar_cartas(&baralho_head, &jogador[i]);
    }
    



    while (jogador[0] != NULL && jogador[1] != NULL)
    {
        


        for (int n_jogador = 0; n_jogador < 2; n_jogador++)
        {
            

            do
            { 
                validade = 0;
                printf("\n========================\n      JOGADOR %d",n_jogador + 1);
                printf("\nEscolha onde comprar:");
                printf("\n (1) Baralho\n:");
                if (descarte != NULL)
                {
                    printf("\n (2) Mesa\n:");
                }
                scanf("%d", &opcao);
        
                switch (opcao)
                {
                case 1:
                    validade = comprar_carta(&baralho_head, &jogador[n_jogador]);
                    printf("\n Certo baralho");
                    break;
        
                case 2:
                    validade = comprar_carta(&descarte, &jogador[n_jogador]);
                    break;
        
                default:
                    printf("\nOpicao invalida");
                    validade = -1;
                    break;
                }
            } while (validade == -1); 
        

            do
            {
                validade = 0;
                printf("\n========================\n      JOGADOR %d", n_jogador + 1);
                exibir_cartas(jogador[n_jogador]);
                printf("\nEscolha a acao:");
                printf("\n (1) Fazer Trinca\n");
                printf("\n (2) Fazer Sequencia\n");
                printf("\n (3) Descarta\n");
                printf("\n (4) Mostrar placar\n:");
                scanf("%d", &opcao);
        
                switch (opcao)
                {
                case 1:
                    validade = trinca(&jogador[n_jogador], conjunto);
                    if (validade != -1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            descarta_carta(&jogador[n_jogador], &indisponivel, conjunto[i]);
                        }
                        validade = -1; 
                    }
                    printf("\n Certo baralho");
                    break;
        
                case 2:
                    validade = sequencia(&jogador[n_jogador], conjunto);
                    if (validade != -1)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            descarta_carta(&jogador[n_jogador], &indisponivel, conjunto[i]);
                        }
                        validade = -1; 
                    }
                    break;
        
                case 3:
                    carta_escolhida = escolher_carta();
                    validade = descarta_carta(&jogador[n_jogador], &descarte, carta_escolhida);
                    break;

                case 4:
                    mostra_placar();
                    validade = -1;
                    break;
        
                default:
                    printf("\nOpicao invalida");
                    validade = -1;
                    break;
                }
            } while (validade == -1);
            
        }


    }
    

    if(jogador[0] == NULL){ganhador = 1;};
    if(jogador[1] == NULL){ganhador = 2;};

    printf("\nJogador %d VENCEU\n", ganhador);

    atualizar_ponto(ganhador);


    return 0;
}