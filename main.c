#include "leitura.h"
#include "busca.h"

int main(void){

	//Tamanho do grafo e maior número de chaves que Vinicius pode carregar//
	int xGrafo, yGrafo, nChaves;

	//Vários vertices formam um grafo em forma de matriz//
	TVertice **Grafo;

	//Variáveis para inicio e fim do grafo//
	TPosicao inicial, final;

	//Cria um vetor para armazenar as direções dos buracos de minhoca//
	TBuracoMinhoca buracosMinhoca[NUMERO_BURACOS_MINHOCA];
	criaBuracosMinhoca(buracosMinhoca);

	//Lê valores do stdin//
	scanf("%d %d %d", &xGrafo, &yGrafo, &nChaves);
	
	//Lê o Grafo do stdin e o prepara para o Algoritmo de busca//
	Grafo = leituraGrafo(xGrafo, yGrafo, buracosMinhoca, &inicial, &final);

	//Encontra o menor caminho//
   encontraMenorCaminho(Grafo, xGrafo, yGrafo, buracosMinhoca, inicial, nChaves);

    //printf("\nDistancias \n");
    //imprimeDistanciasGrafo(Grafo, xGrafo, yGrafo);

    //Imprime o resultado//
    if(Grafo[final.x][final.y].distancia != INFINITO)
    	printf("%d\n", Grafo[final.x][final.y].distancia);

    else
    	printf("-1\n");

    destroiGrafo(Grafo, xGrafo);

	return 0;
}