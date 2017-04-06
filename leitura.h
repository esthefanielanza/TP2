#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITO INT_MAX
#define NUMERO_BURACOS_MINHOCA 4

typedef struct TPosicao{
	int x;
	int y;
} TPosicao;

typedef struct TVertice{
	int distancia;
	int cor;
	char chave;
	int nChaves;
	char usouBuraco[NUMERO_BURACOS_MINHOCA];
} TVertice;

typedef struct TBuracoMinhoca{
	int x;
	int y;
} TBuracoMinhoca;

/*---------------------------------------------------------------------------------------------
Protótipo: TVertice** leituraGrafo(int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao *inicial, TPosicao *final);
Função: Lê o grafo.
Entrada: Os extremos do grafo, o vetor de buracos de minhoca e apontadores para armazenar a
posição inicial e final.
Saída: Uma matriz de TVértices, ou seja, o grafo.
---------------------------------------------------------------------------------------------*/
TVertice** leituraGrafo(int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao *inicial, TPosicao *final);

/*---------------------------------------------------------------------------------------------
Protótipo: TVertice **alocaGrafo(int xGrafo, int yGrafo);
Função: Aloca espaço para o grafo.
Entrada: Os extremos do grafo.
Saída: Uma matriz de vértices.
---------------------------------------------------------------------------------------------*/
TVertice **alocaGrafo(int xGrafo, int yGrafo);

/*---------------------------------------------------------------------------------------------
Protótipo: void criaBuracosMinhoca(TBuracoMinhoca *buracosMinhoca);
Função: Preenche os buracos de minhoca com 0 no x e y;
Entrada: O vetor de buracos de minhoca.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void criaBuracosMinhoca(TBuracoMinhoca *buracosMinhoca);

/*---------------------------------------------------------------------------------------------
Protótipo: void preencheVertice(TVertice **Grafo, char caractereLido, TPosicao *inicial, TPosicao *final, TBuracoMinhoca *buracosMinhoca, int *buracosMinhocaAtual, int i, int j);
Função: Preenche os outros campos do struct vértice, como distancia, cor e etc.
Entrada: O Grafo, o caractere lido, as posições iniciais e finais, o vetor de buraco de minhoca, 
o buraco de minhoca e as posições atuais de i e j.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void preencheVertice(TVertice **Grafo, char caractereLido, TPosicao *inicial, TPosicao *final, TBuracoMinhoca *buracosMinhoca, int *buracosMinhocaAtual, int i, int j);

/*---------------------------------------------------------------------------------------------
Protótipo: void preencheBuracoMinhoca(TBuracoMinhoca *buracosMinhoca, int buracoAtual, int x);
Função: Lê o segundo valor, y, para o buraco de minhoca e preenche os campos do struct.
Entrada: O vetor de buracos de minhoca, o atual e sua posição x.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void preencheBuracoMinhoca(TBuracoMinhoca *buracosMinhoca, int buracoAtual, int x);

/*---------------------------------------------------------------------------------------------
Protótipo: void imprimeChavesGrafo(TVertice **Grafo, int xGrafo, int yGrafo);
Função: Imprime as chaves do grafo em forma de matriz.
Entrada: O Grafo e seus extremos.
de chaves maximo;
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void imprimeChavesGrafo(TVertice **Grafo, int xGrafo, int yGrafo);

/*---------------------------------------------------------------------------------------------
Protótipo: void imprimeDistanciasGrafo(TVertice **Grafo, int xGrafo, int yGrafo);
Função: Imprime a matriz com as distancias mínimas.
Entrada: O Grafo e seus extremos.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void imprimeDistanciasGrafo(TVertice **Grafo, int xGrafo, int yGrafo);

/*---------------------------------------------------------------------------------------------
Protótipo: void destroiGrafo(TVertice **Grafo, int y);
Função: Desaloca memória utilizada pelo grafo.
Entrada: O Grafo e seus extremos.
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void destroiGrafo(TVertice **Grafo, int x);

#endif
