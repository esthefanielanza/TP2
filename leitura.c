#include "leitura.h"

TVertice **leituraGrafo(int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao *inicial, TPosicao *final){

	int i, j, buracosMinhocaAtual = 0;
	char caractereLido;
	TVertice **Grafo;
	
	Grafo = alocaGrafo(xGrafo, yGrafo);
	
	//Lemos cada vértice do gráfico pré configurando cada elemento do struct//
	for(i = xGrafo - 1; i >= 0; i--){
		for(j = 0; j < yGrafo; j++){
				
			scanf("\n%c", &caractereLido);
			preencheVertice(Grafo, caractereLido, inicial, final, buracosMinhoca, &buracosMinhocaAtual, i, j);
			
		}
	}
	return Grafo;
}

void preencheVertice(TVertice **Grafo, char caractereLido, TPosicao *inicial, TPosicao *final, TBuracoMinhoca *buracosMinhoca, int *buracosMinhocaAtual, int i, int j){

	int k;
	
	//Caso seja lido um buraco de minhoca//
	if(caractereLido >= '0' && caractereLido <= '9'){	
		Grafo[i][j].chave = *buracosMinhocaAtual + '0';
		preencheBuracoMinhoca(buracosMinhoca, *buracosMinhocaAtual, caractereLido - '0');
		*buracosMinhocaAtual = *buracosMinhocaAtual + 1;
	} 
	
	//Caso contrário apenas preenchemos a chave com o caractere lido//
	else
		Grafo[i][j].chave = caractereLido;

	//Inicializamos o ponto inicial do labirinto//
	if(caractereLido == 'V'){
		Grafo[i][j].distancia = 0;
		inicial->x = i; inicial->y = j;
	}

	//Inicializamos o ponto final do labirinto//
	else{
		Grafo[i][j].distancia = INFINITO;
		if(caractereLido == 'E'){
			final->x = i; final->y = j;
		}
	}

	//Preenchemos com 0 os outros elementos do struct//
	for(k = 0; k < NUMERO_BURACOS_MINHOCA; k++)
		Grafo[i][j].usouBuraco[k] = '0';
	Grafo[i][j].nChaves = 0;
	Grafo[i][j].cor = 0;	
}

TVertice **alocaGrafo(int xGrafo, int yGrafo){

	int i;
	TVertice **Grafo;
	//Alocamos memória para o grafo em relação a x e y//
	Grafo = (TVertice**) malloc(xGrafo * sizeof(TVertice*));
	for(i = 0; i < xGrafo; i++)
		Grafo[i] = (TVertice*) malloc(yGrafo * sizeof(TVertice));

	return Grafo;
}

void criaBuracosMinhoca(TBuracoMinhoca *buracosMinhoca){
	
	int i;
	
	//Inicializamos os buracos de minhoca com 0 no x e y//
	for(i = 0; i < NUMERO_BURACOS_MINHOCA; i++){
		buracosMinhoca[i].x = 0;
		buracosMinhoca[i].y = 0;
	}

}

void preencheBuracoMinhoca(TBuracoMinhoca *buracosMinhoca, int buracoAtual, int x){
	
	char y;
	//Lemos o segundo caractere para posição y do buraco//
	scanf("\n%c", &y);

	buracosMinhoca[buracoAtual].x = x;
	//Realizamos a conversão de caractere para inteiro//
	buracosMinhoca[buracoAtual].y = y - '0';
}

void imprimeChavesGrafo(TVertice **Grafo, int xGrafo, int yGrafo){

	int i, j;
	for(i = 0; i < xGrafo; i++){
		for(j = 0; j < yGrafo; j++){
			printf("%c ", Grafo[i][j].chave);
		}
		printf("\n");
	}
}

void imprimeDistanciasGrafo(TVertice **Grafo, int xGrafo, int yGrafo){

	int i, j;
	for(i = 0; i < xGrafo; i++){
		for(j = 0; j < yGrafo; j++){
			if(Grafo[i][j].distancia == INFINITO)
				printf("# ");
			else
				printf("%d ", Grafo[i][j].distancia);
		}
		printf("\n");
	}
}

void destroiGrafo(TVertice **Grafo, int x){
	int i;
	for(i = 0; i < x; i++)
		free(Grafo[i]);
	free(Grafo);
}