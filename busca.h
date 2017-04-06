#ifndef BUSCA_H
#define BUSCA_H

#include "leitura.h"
#include "fila.h"

#define NUMERO_CHAVES 4

typedef struct TUsouBuraco{
	char b[NUMERO_BURACOS_MINHOCA];
} TUsouBuraco;

typedef struct TPassouPorta{
	char c[NUMERO_CHAVES];
} TPassouPorta;

/*---------------------------------------------------------------------------------------------
Protótipo: void encontraMenorCaminho(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax);
Função: Iniciakiza matrizes temporárias e prepara o grafo para iniciar a busca em largura.
Entrada: O Grafo, seus extremos, um vetor de buracos de minhoca, a posição inicial e o número
de chaves maximo;
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void encontraMenorCaminho(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax);

/*---------------------------------------------------------------------------------------------
Protótipo: void inicializaMatrizDistanciaBuracos(int **distanciaTemp, int xGrafo, int yGrafo, TUsouBuraco **usouBuraco);
Função: Inicializa a matriz de distancias temp com infinito e a de usou buracos de minhoca com 
zeros.
Entrada: a matriz de distancia temporária, seus extremos, as matrizes de usou buraco.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void inicializaMatrizDistanciaBuracos(int **distanciaTemp, int xGrafo, int yGrafo, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta);

/*---------------------------------------------------------------------------------------------
Protótipo: void inicializaFilas(Fila *fila, Fila *filaChaves, TPosicao inicial);
Função: Inicializa a fila de vértices e de chaves para a busca em largura.
Entrada: As filas a serem iniciadas e a posição inicial.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void inicializaFilas(Fila *fila, Fila *filaChaves, TPosicao inicial);

/*---------------------------------------------------------------------------------------------
Protótipo: void inicializaBuscaChaves(Fila *filaChaves, TPosicao *inicial, int *chaves, TVertice **Grafo, int **distanciaTemp, int xGrafo, int yGrafo);
Função: Inicializa as matrizes para iniciar a busca a partir de uma chave.
Entrada: A fila de chaves, a posição inicial, as chaves, o grafo, as distancias temporárias e
seus extremos.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void inicializaBuscaChaves(Fila *filaChaves, TPosicao *inicial, int *chaves, TVertice **Grafo, int **distanciaTemp, int xGrafo, int yGrafo);

/*---------------------------------------------------------------------------------------------
Protótipo: void buscaLargura(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax, int *chaves, int **distanciaTemp, TUsouBuraco **usouBuraco);
Função: Realiza a busca em largura para encontrar o menor caminho
Entrada: O grafo, os extremos, os buracos de minhoca, a posição inicial, o número de chaves max
as chaves em mãos, a matriz de distancias temporárias e a matriz que indentifica se algum buraco
de minhoca foi usado.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void buscaLargura(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax, int *chaves, int **distanciaTemp, TUsouBuraco **usouBuraco, TPassouPorta **passouBuraco);

/*---------------------------------------------------------------------------------------------
Protótipo: verificaAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco);
Função: Verifica os adjacentes em volta de um determinado ponto x(esq, dir, cima, baixo)
Entrada: O grafo, os extremos, os buracos de minhoca, a posição inicial, o número de chaves max
as chaves em mãos, a matriz de distancias temporárias e a matriz que indentifica se algum buraco
de minhoca foi usado.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void verificaAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta);

/*---------------------------------------------------------------------------------------------
Protótipo: void recalculaDistancias(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, TUsouBuraco **usouBuraco);
Função: Recalcula as distancias mínimas até determinado ponto;
Entrada: O Grafo, a matriz temporária, o ponto atual e o anterior e se foi usado algum buraco de
minhoca.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void recalculaDistancias(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, TUsouBuraco **usouBuraco, int passouBuraco, TPassouPorta **passouPorta);

/*---------------------------------------------------------------------------------------------
Protótipo: void insereAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, int xAnt, int yAnt, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco);
Função: Insere os adjacentes na fila caso estes sejam válidos
Entrada: O grafo, os extremos, os buracos de minhoca, a posição inicial, o número de chaves max
as chaves em mãos, a matriz de distancias temporárias e a matriz que indentifica se algum buraco
de minhoca foi usado.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void insereAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, int xAnt, int yAnt, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco, int *passouBuraco, TPassouPorta **passouPorta);

/*---------------------------------------------------------------------------------------------
Protótipo: void encontrouPorta(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, int *chaves, Fila *fila, TUsouBuraco **usouBuraco);
Função: Rotina para quando encontramos uma porta
Entrada: O grafo, a matriz temporária, o ponto atual e o anterior, as chaves usadas, fila, iden
tifica se algum buraco de minhoca foi usado.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void encontrouPorta(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, int *chaves, Fila *fila, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta);

/*---------------------------------------------------------------------------------------------
Protótipo: void encontrouBuraco(TVertice **Grafo, int *x, int *y, int xAnt, int yAnt, int buracoMinhocaAtual, TUsouBuraco **usouBuraco, TBuracoMinhoca *buracos);
Função: Rotina para quando encontramos um buraco de minhoca.
Entrada: Recebe o grafo, a posição atual e a anterior, o buraco de minhoca atual e outras vari
áveis relacionadas.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void encontrouBuraco(TVertice **Grafo, int *x, int *y, int xAnt, int yAnt, int buracoMinhocaAtual, TBuracoMinhoca *buracos, int xGrafo, int yGrafo, int **distanciaTemp);

/*---------------------------------------------------------------------------------------------
Protótipo: int chaveProcurada(char c);
Função: Devolve o indice para determinada porta ou chave.
Entrada: Um caractere referente a porta ou chave.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
int chaveProcurada(char c);

/*---------------------------------------------------------------------------------------------
Protótipo: void criaFila(Fila *f);
Função: Verifica se já existe chave
Entrada: Um caractere referente a chave e o vetor de chaves.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
int verificaChaves(char c, int *chaves);

/*---------------------------------------------------------------------------------------------
Protótipo: void criaFila(Fila *f);
Função: Cria uma fila vazia
Entrada: Recebe uma fila
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
int chaveProcurada(char c);

/*---------------------------------------------------------------------------------------------
Protótipo: void criaFila(Fila *f);
Função: Desaloca espaço de uma matriz de int.
Entrada: a matriz e o seu número de colunas.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void destroiMatrizInteiros(int **m, int y);

/*---------------------------------------------------------------------------------------------
Protótipo: void destroiMatrizUsouBuraco(TUsouBuraco **usouBuraco, int x);
Função: Desaloca espaço para uma matriz de buracos de minhoca.
Entrada: A matriz e o seu número de colunas.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void destroiMatrizUsouBuraco(TUsouBuraco **usouBuraco, int y);

void destroiMatrizPassouPorta(TPassouPorta **passouPorta, int x);
#endif