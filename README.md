# Cacheta
**Trabalho-Avaliativo**

##Cacheta (readaptada)

O jogo feito foi a cacheta(Pif-Paf), porém adaptamos ela. A diferença é que ela não possui os 2 coringas, só vai ser jogado com um baralho de 52 cartas.

.Cada jogador recebe 6 cartas no início;
.Combinações possíveis Trinca(3 classes iguais com 3 naipes diferentes) e Sequência(3 classe diferentes porém em ordem com 3 naipes iguais);
.O jogador só poderá descartar 1 carta por round;
.O jogador poderá fazer várias combinações por round.

##📋 Regras

1° Deve ser feito combinações com cartas para elas serem tiradas da sua mão;
2° Para o round ir para o próximo jogador, o atual deve descartá alguma carta;
3° O jogador que tiver nenhuma carta no final ganha;

###Ciclo de ações

O jogo trabalho nesta dinâmica

1° Escolhe de onde vai comprar a carta(se for a primeira jogada, só terá a opção pela baralho);
2° Escolhe se vai fazer uma Sequência, Trinca, Mostrar Placar ou Descarta;
3° Se escolher Trinca ou Sequência ele vai pergunta quais são as 3 cartas;
4° Se escolher Mostrar Placar ele mostrará o placar já salvo(se for a primeira jogada, vai estar J1 0 | J2 0);
5° Se escolher descarte, a carta é descartada e o round e passado ao outro jogador.



##Código Detalhes

A compilação é feita por gcc (main.c) (jogos.c) (nome do executável)
```
gcc main.c jogo.c -o run.exe
```
```
./run.exe
```

#Funções:

**void gerar_baralho();**
*Esta função é responsável pela criação do baralho, recebendo o ponteiro da cabeça do baralho, uma array para guardar as cartas e uma array de naipes. Ela gera todas as cartas de um baralho, mistura as cartas e no final encadeia os baralho com a cabeça do baralho;

**void exibir_cartas();**
*Esta função é responsável por exibir na tela o mão recebido. Ela recebe o ponteiro da variável e exibe na tela do terminal;

**void entregar_cartas();**
*Esta função é responsável por entregar a carta ao jogador. Ela recebe o ponteiro da cabeça do baralho e do jogador, assim retirando a carta do início do baralho e inserindo no inicio da mão do jogador 6 vezes por manipulação de ponteiros;

**int comprar_carta();**
.Esta função é responsável por entregar uma carta do monte de cartas ao jogador. Ela recebe o ponteiro da cabeça do baralho e do jogador,  assim retirando a carta do início do baralho e inserindo no inicio da mão do jogador por manipulação de ponteiros;

**int descarta_carta();**
*Esta função é responsável por retirar da mão do jogador uma carta e inserir no ponteiro de descarte. Ela recebe o ponteiro da mão do jogador e o ponteiro de descartes e por meio de manipulação de ponteiros leva a carta da mão do jogador até a pilha de descartes;

**void atualizar_ponto();**
*Essa função atualiza os placares com as pontuações de cada jogador. Ela abre o arquivo em modo de leitura “r” com o nome “placar.txt”. Caso ela não consiga abrir esse arquivo, é mostrada uma mensagem de erro.

**void mostrar_placar();**
*Essa função abre um arquivo “placar.txt”, em modo leitura “r” e exibe o placar linha por linha no terminal. Em cada linha apresenta um terminal de pontuação de cada jogador, gravado ao final de partidas anteriores;

**baralho_t escolher_carta();**
*Esta função faz uma solicitação ao usuário que insira o valor e um naipe de uma carta. 
Após a escolha do usuário, ela faz as comparações com strings, usando “strcmp()”. A função converte os símbolos para valores. Se o valor for inválido ele mostra uma mensagem de erro, e a entrada é solicitada novamente.

---
Por **Gabriel**
