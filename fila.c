 #include "fila.h"

void criaFila(Fila *f){

	f->frente = (Celula*) malloc(sizeof(Celula));
	f->tras = f->frente;
	f->frente->prox = NULL;
	f->tamanho = 0;
}

void enfileira(Fila *f, int x, int y){

	Apontador novaCelula;
	novaCelula = (Celula*) malloc(sizeof(Celula));
	
	novaCelula->x = x;
	novaCelula->y = y;
	novaCelula->prox = NULL;

	f->tras->prox = novaCelula;
	f->tras = novaCelula;
	f->tamanho++;
}


int filaVazia(Fila *f){
	return(f->frente == f->tras);
}

void desenfileira(Fila *f, int *x, int *y){

	if(filaVazia(f)){
		printf("Erro: Fila vazia");
		return;
	}

	Apontador q;
	q = f->frente;
	f->frente = f->frente->prox;
	*x = f->frente->x;
	*y = f->frente->y;
	free(q);
	f->tamanho--;
}

void destroiFila(Fila *f){
	
	Apontador aux, remover;
	aux = f->frente;
	
	while(aux->prox != NULL){
		remover = aux;
		aux = aux->prox;
		free(remover);
	}

	free(aux);
	free(f);
}
