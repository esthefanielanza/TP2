#ifndef FILA_H
#define FILA_H

#include "leitura.h"

typedef struct Celula *Apontador;

typedef struct Celula{
	int x, y;
	Apontador prox;
} Celula;

typedef struct Fila{
	Apontador frente, tras;
	int tamanho;
} Fila;

/*---------------------------------------------------------------------------------------------
Protótipo: void criaFila(Fila *f);
Função: Cria uma fila vazia
Entrada: Recebe uma fila
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void criaFila(Fila *f);

/*---------------------------------------------------------------------------------------------
Protótipo: void enfileira(Fila *f, int rua)
Função: Enfileira uma rua
Entrada: A fila e a rua a ser enfileirada
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void enfileira(Fila *p, int x, int y);

/*---------------------------------------------------------------------------------------------
Protótipo: filaVazia(Fila *f);
Função: Descobre se uma fila está vazia
Entrada: A fila
Saída: Retorna 1 para filas vazias e 0 para filas que possuem algum elemento
---------------------------------------------------------------------------------------------*/
void desenfileira(Fila *p, int *x, int *y);


/*---------------------------------------------------------------------------------------------
Protótipo: void desenfileira(Fila *f, int *rua)
Função: Desenfileira uma célula da fila
Entrada: A fila
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
int filaVazia(Fila *f);


/*---------------------------------------------------------------------------------------------
Protótipo: void destroiFila(FilaCaminho *f);
Função: Desaloca espaço na memória alocado para fila de menores caminhos
Entrada: A fila de caminhos
Saída: Não retorna nenhum valor
---------------------------------------------------------------------------------------------*/
void destroiFila(Fila *f);


#endif
