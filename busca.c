#include "busca.h"

int** alocaDistanciaTemp(int xGrafo, int yGrafo){
	int i;
	int **distanciaTemp;
	
	distanciaTemp = malloc(xGrafo * sizeof(int*));
	for(i = 0; i < xGrafo; i++){
		distanciaTemp[i] = malloc(yGrafo * sizeof(int));
	}

	return distanciaTemp;
}

TUsouBuraco** alocaUsouBuraco(int xGrafo, int yGrafo){
	
	int i;
	TUsouBuraco **usouBuraco;
	
	usouBuraco = malloc(xGrafo * sizeof(TUsouBuraco*));
	for(i = 0; i < xGrafo; i++){
		usouBuraco[i] = malloc(yGrafo * sizeof(TUsouBuraco));
	}

	return usouBuraco;
}

TPassouPorta** alocaPassouPorta(int xGrafo, int yGrafo){
	
	int i;
	TPassouPorta **passouPorta;
	
	passouPorta = malloc(xGrafo * sizeof(TPassouPorta*));
	for(i = 0; i < xGrafo; i++){
		passouPorta[i] = malloc(yGrafo * sizeof(TPassouPorta));
	}

	return passouPorta;
}

void encontraMenorCaminho(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax){

	int i;
	int chaves[4];
	int **distanciaTemp;
	TUsouBuraco **usouBuraco;
	TPassouPorta **passouPorta;

	//Inicializa o vetor de chaves sinalizando que não encontrou nenhuma//
	for(i = 0; i < NUMERO_CHAVES; i++)
		chaves[i] = 0;
	
	//Cria matriz com distancias mínimas//
	distanciaTemp = alocaDistanciaTemp(xGrafo, yGrafo);

	//Cria matriz para identificar se passamos ou não por um buraco para chegar em algum caminho//
	usouBuraco = alocaUsouBuraco(xGrafo, yGrafo);

	//Cria matriz para identificar se passamos ou não por um buraco para chegar em algum caminho//
	passouPorta = alocaPassouPorta(xGrafo, yGrafo);

	buscaLargura(Grafo, xGrafo, yGrafo, buracosMinhoca, inicial, nChavesMax, chaves, distanciaTemp, usouBuraco, passouPorta);

	destroiMatrizInteiros(distanciaTemp, xGrafo);
	destroiMatrizUsouBuraco(usouBuraco, xGrafo);
	destroiMatrizPassouPorta(passouPorta, xGrafo);
}

void inicializaMatrizDistanciaBuracos(int **distanciaTemp, int xGrafo, int yGrafo, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta){
	
	int i, j,k;

	//Inicializa as distancias temporárias com infinito e o uso de buracos como 0//
	for(i = 0; i < xGrafo; i++){
		for(j = 0; j < yGrafo; j++){
			distanciaTemp[i][j] = INFINITO;
			for(k = 0; k < NUMERO_BURACOS_MINHOCA; k++){
				usouBuraco[i][j].b[k] = '0';
				passouPorta[i][j].c[k] = '0';
			}
		}
	}
}

void inicializaFilas(Fila *fila, Fila *filaChaves, TPosicao inicial){

	criaFila(fila);
	criaFila(filaChaves);

	enfileira(fila, inicial.x, inicial.y);
}

void inicializaBuscaChaves(Fila *filaChaves, TPosicao *inicial, int *chaves, TVertice **Grafo, int **distanciaTemp, int xGrafo, int yGrafo){
	
	int i, j, x, y;
	
	//Desenfileramos a primeira chave encontrada pela busca//
	desenfileira(filaChaves, &x, &y);
	
	//Reajustamos os pontos iniciais par iniciar a busca a partir deles//
	inicial->x = x;
	inicial->y = y;
	
	//Sinalizamos que a chave foi encontrada//
	chaves[chaveProcurada(Grafo[x][y].chave)] = 2;

	//Colorimos todos os vertices como não visitado//
	for(i = 0; i < xGrafo; i++){
		for(j = 0; j < yGrafo; j++){
			Grafo[i][j].cor = 0;
		}
	}
	
	//A distancia até o ponto inicial é igual a anteriormente encontrada na busca//
	distanciaTemp[x][y] = Grafo[x][y].distancia;
}

void buscaLargura(TVertice **Grafo, int xGrafo, int yGrafo, TBuracoMinhoca *buracosMinhoca, TPosicao inicial, int nChavesMax, int *chaves, int **distanciaTemp, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta){

	//Inicializa filas//
	Fila *fila = malloc(sizeof(Fila));
	Fila *filaChaves = malloc(sizeof(Fila));
	inicializaFilas(fila, filaChaves, inicial);	
	
	int x, y, i;

	//Inicializa matriz com distancias temp e a de uso de buracos de minhoca//
	inicializaMatrizDistanciaBuracos(distanciaTemp, xGrafo, yGrafo, usouBuraco, passouPorta);

	//Inicializa ponto inicial//
	distanciaTemp[inicial.x][inicial.y] = Grafo[inicial.x][inicial.y].distancia;
	
	//Inicializa buracos de minhoca em relação ao ponto inicial//
	for(i = 0; i < NUMERO_BURACOS_MINHOCA; i++){
		usouBuraco[inicial.x][inicial.y].b[i] = Grafo[inicial.x][inicial.y].usouBuraco[i];
	}

	//Enquanto a fila de vertices adjacentes não estiver vazia//
	while(!filaVazia(fila)){

		desenfileira(fila, &x, &y);
		
		//Verificamos seu adjacentes//
		verificaAdjacentes(Grafo, xGrafo, yGrafo, x, y, fila, filaChaves, buracosMinhoca, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, passouPorta);

	}

	//Enquanto a fila de chaves encontradas não estiver vazia//
	while(!filaVazia(filaChaves)){
		inicializaBuscaChaves(filaChaves, &inicial, chaves, Grafo, distanciaTemp, xGrafo, yGrafo);
		//Chamamos a busca em largura de um novo ponto inicial//
		buscaLargura(Grafo, xGrafo, yGrafo, buracosMinhoca, inicial, nChavesMax, chaves, distanciaTemp, usouBuraco, passouPorta);
	}

	destroiFila(fila);
	destroiFila(filaChaves);
}

void verificaAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta){

	int passouBuraco = 0;

	//printDebug(distanciaTemp, Grafo, xGrafo, yGrafo, usouBuraco, passouPorta);
	
	//Esquerda//
	if(x > 0 && passouBuraco == 0)
		insereAdjacentes(Grafo, xGrafo, yGrafo, x-1, y, x, y, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, &passouBuraco, passouPorta);
	//Direita//
	if(x < xGrafo - 1 && passouBuraco == 0)
		insereAdjacentes(Grafo, xGrafo, yGrafo, x+1, y, x, y, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, &passouBuraco, passouPorta);
	//Para baixo//
	if(y > 0 && passouBuraco == 0)
		insereAdjacentes(Grafo, xGrafo, yGrafo, x, y-1, x, y, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, &passouBuraco, passouPorta);
	//Para cima//
	if(y < yGrafo - 1 && passouBuraco == 0)
		insereAdjacentes(Grafo, xGrafo, yGrafo, x, y+1, x, y, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, &passouBuraco, passouPorta);
}

void encontrouPorta(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, int *chaves, Fila *fila, TUsouBuraco **usouBuraco, TPassouPorta **passouPorta){
	
	int i;

	//Se ainda não passamos por uma porta desse tipo incrementamos o contador de chaves//
	if(passouPorta[xAnt][yAnt].c[chaveProcurada(Grafo[x][y].chave)] == '0'){
		passouPorta[x][y].c[chaveProcurada(Grafo[x][y].chave)] = '1';
		if(Grafo[x][y].nChaves == 0)
			Grafo[x][y].nChaves = Grafo[xAnt][yAnt].nChaves + 1;
	}

	//Caso seja zero copiamos a restrição da chave anterior//
	if(Grafo[x][y].nChaves == 0)
			Grafo[x][y].nChaves = Grafo[xAnt][yAnt].nChaves;
	
	//Copiamos o valor do vértice anterior para o número de chaves//
	for(i = 0; i < NUMERO_CHAVES; i++){
		if(passouPorta[x][y].c[i] == '0'){
			passouPorta[x][y].c[i] = passouPorta[xAnt][yAnt].c[i];
		}
		usouBuraco[x][y].b[i] = usouBuraco[xAnt][yAnt].b[i];
		Grafo[x][y].usouBuraco[i] = usouBuraco[xAnt][yAnt].b[i];
	}

	//Verificamos se já temos a chave em mãos//
	if(!verificaChaves(Grafo[x][y].chave, chaves))
		return;

	else{

		if(distanciaTemp[x][y] > distanciaTemp[xAnt][yAnt] + 1)
			distanciaTemp[x][y] = distanciaTemp[xAnt][yAnt] + 1;
				
		if(Grafo[x][y].distancia > distanciaTemp[x][y]){
			//Anotamos que encontramos uma distancia menor que a anterior//
			Grafo[x][y].distancia = distanciaTemp[x][y];
			//Repassamos para o vértice se foi usado ou não um buraco de minhoca//
			for(i = 0; i < NUMERO_BURACOS_MINHOCA; i++){
				usouBuraco[x][y].b[i] = usouBuraco[xAnt][yAnt].b[i];
				Grafo[x][y].usouBuraco[i] = usouBuraco[xAnt][yAnt].b[i];
			}
		}
		
		enfileira(fila, x, y);
		return;
	}
}

void encontrouBuraco(TVertice **Grafo, int *x, int *y, int xAnt, int yAnt, int buracoMinhocaAtual, TBuracoMinhoca *buracos, int xGrafo, int yGrafo, int **distanciaTemp){
	
	int i, j, d;

	//Mudamos o x e o y para o indicado no buraco de minhoca//
	*x = (int)buracos[buracoMinhocaAtual].x;
	*y = (int)buracos[buracoMinhocaAtual].y;
	d = distanciaTemp[xAnt][yAnt];
	
	for(i = 0; i < xGrafo; i++){
		for(j = 0; j < yGrafo; j++){
			Grafo[i][j].cor = 0;
			distanciaTemp[i][j] = INFINITO;
		}
	}

	distanciaTemp[*x][*y] = d + 1;
}

void recalculaDistancias(TVertice **Grafo, int **distanciaTemp, int x, int y, int xAnt, int yAnt, TUsouBuraco **usouBuraco, int passouBuraco, TPassouPorta **passouPorta){

	int i;

	//Se a distancia anterior + 1 é menor que a distancia armazenada//
	if(distanciaTemp[x][y] > distanciaTemp[xAnt][yAnt] + 1){
		//Atualizamos a distancia e se foi usado um buraco de minhoca//
		if(passouBuraco != 1)
			distanciaTemp[x][y] = distanciaTemp[xAnt][yAnt] + 1;

		for(i = 0; i < NUMERO_BURACOS_MINHOCA; i++){
			if(usouBuraco[x][y].b[i] == '0')
				usouBuraco[x][y].b[i] = usouBuraco[xAnt][yAnt].b[i];
			if(passouPorta[x][y].c[i] == '0'){
				passouPorta[x][y].c[i] = passouPorta[xAnt][yAnt].c[i];
			}
		}
	}	

	//Se a distancia guardada no Grafo é maior que a distancia anterior//
	if(Grafo[x][y].distancia > distanciaTemp[x][y]){
		//Atualizamos o número de chaves utilizadas//
		
		if(Grafo[x][y].nChaves == 0)
			Grafo[x][y].nChaves = Grafo[xAnt][yAnt].nChaves;

		//Atualizamos os buracos de minhoca usados//
		for(i = 0; i < NUMERO_BURACOS_MINHOCA; i++){
			if(Grafo[x][y].usouBuraco[i] == '0')
				Grafo[x][y].usouBuraco[i] = usouBuraco[xAnt][yAnt].b[i];
		}
		//Atualizamos a distancia//
		Grafo[x][y].distancia = distanciaTemp[x][y];
	}
}

void insereAdjacentes(TVertice **Grafo, int xGrafo, int yGrafo, int x, int y, int xAnt, int yAnt, Fila *fila, Fila *filaChaves, TBuracoMinhoca *buracos, int *chaves, int nChavesMax, TPosicao inicial, int **distanciaTemp, TUsouBuraco **usouBuraco, int *passouBuraco, TPassouPorta **passouPorta){

	int i, j;

	//Caso seja necessário usar um número maior de chaves pra passar por essa caminho, retornamos//
	if(nChavesMax <  Grafo[x][y].nChaves)
		return;

	//Se não é uma parede e ainda não foi visitado//
	if(Grafo[x][y].chave != '#' && Grafo[x][y].cor == 0){

		//Mudamos a cor do vértice//
		Grafo[x][y].cor = 1;
		
		//Caso seja uma porta//
		if(Grafo[x][y].chave == 'C' || Grafo[x][y].chave == 'D' || Grafo[x][y].chave == 'H' || Grafo[x][y].chave == 'S'){
			encontrouPorta(Grafo, distanciaTemp, x, y, xAnt, yAnt, chaves, fila, usouBuraco, passouPorta);	
			return;		
		}

		//Enquanto cairmos em buraco de minhoca//
		if(Grafo[x][y].chave <= '9' && Grafo[x][y].chave >= '0'){
		
			int buracoMinhocaAtual;			
			
			while(Grafo[x][y].chave <= '9' && Grafo[x][y].chave >= '0'){
				
				buracoMinhocaAtual = (int)Grafo[x][y].chave - (int)'0';

				if(usouBuraco[xAnt][yAnt].b[buracoMinhocaAtual] == '0'){
					
					//Mudamos o x e o y para o indicado no buraco de minhoca//
					x = (int)buracos[buracoMinhocaAtual].x;
					y = (int)buracos[buracoMinhocaAtual].y;
					//d = distanciaTemp[xAnt][yAnt];
					
					//Sinalizamos que usamos um buraco para chegar nessa posição//
					Grafo[x][y].usouBuraco[buracoMinhocaAtual] = '1';
					usouBuraco[x][y].b[buracoMinhocaAtual] = '1';
				}

				else
					break;
			}
				
			if(usouBuraco[xAnt][yAnt].b[buracoMinhocaAtual] == '0'){
				verificaAdjacentes(Grafo, xGrafo, yGrafo, xAnt, yAnt, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, passouPorta);
			
				while(!filaVazia(fila)){
					desenfileira(fila, &i, &j);
					verificaAdjacentes(Grafo, xGrafo, yGrafo, i, j, fila, filaChaves, buracos, chaves, nChavesMax, inicial, distanciaTemp, usouBuraco, passouPorta);
				}

				encontrouBuraco(Grafo, &x, &y, xAnt, yAnt, buracoMinhocaAtual, buracos, xGrafo, yGrafo, distanciaTemp);
				*passouBuraco = 1;
			}	
		}

		//Recalculamos distancias até esse ponto//
		recalculaDistancias(Grafo, distanciaTemp, x, y, xAnt, yAnt, usouBuraco, *passouBuraco, passouPorta);

		//Se encontramos uma chave guardamos sua posição em uma fila para iniciar a buscar a partir dela//
		if(Grafo[x][y].chave == 'c' || Grafo[x][y].chave == 'd' || Grafo[x][y].chave == 'h' || Grafo[x][y].chave == 's'){
			if(chaves[chaveProcurada(Grafo[x][y].chave)] == 0){
				enfileira(filaChaves, x, y);
				chaves[chaveProcurada(Grafo[x][y].chave)] = 1;
			}
		}
		enfileira(fila, x, y);
	}
}

int verificaChaves(char c, int *chaves){
	
	int chaveAtual;

	chaveAtual = chaveProcurada(c);

	if(chaves[chaveAtual] == 2)
		return 1;

	else
		return 0;
}

int chaveProcurada(char c){

	if(c == 'C' || c == 'c')
		return 0;

	else if(c == 'D' || c == 'd')
		return 1;

	else if(c == 'H' || c == 'h')
		return 2;

	else
		return 3;
}

void destroiMatrizInteiros(int **m, int x){

	int i;
	for(i = 0; i < x; i++)
		free(m[i]);

	free(m);

}

void destroiMatrizUsouBuraco(TUsouBuraco **usouBuraco, int x){

	int i;
	for(i = 0; i < x; i++)
		free(usouBuraco[i]);

	free(usouBuraco);
}

void destroiMatrizPassouPorta(TPassouPorta **passouPorta, int x){

	int i;
	for(i = 0; i < x; i++)
		free(passouPorta[i]);

	free(passouPorta);
}
