/*
* Aluno : Cleyton de Souza Oliveira   data : 28/10/2020
*/


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define ADJACENTE 1
#define RETIRADO  0


typedef struct estrada{
	int cidadeA;
	int cidadeB;
}estrada;



bool cidadeAdjacenteEmComum(int adjacenciaA , int adjacenciaB){
	return adjacenciaA == ADJACENTE && adjacenciaB == ADJACENTE;
}
void estabelecerRelacao(vector<vector<int>> * matrizAdjacencia , int cidadeA, int cidadeB, int tipoRelacao){
	(*matrizAdjacencia)[ cidadeA ][ cidadeB ] = tipoRelacao;
	(*matrizAdjacencia)[ cidadeB ][ cidadeA ] = tipoRelacao;
}

bool existeCaminho(vector<vector<int>> matrizAdjacencia, int C, int cidadeA, int cidadeB ){
	/*
	* Faz um busca nos C campos de adjacência de A e B, se existe alguma cidade adjacente em comum, por consequência um caminho que liga A e B
	*/

	bool retorno;
	for(int cidadeRelacionada = 0; cidadeRelacionada < C; cidadeRelacionada++){
		
		if(cidadeAdjacenteEmComum( matrizAdjacencia[cidadeA][cidadeRelacionada], matrizAdjacencia[cidadeB][cidadeRelacionada])){ 
			return true;

		}else if(matrizAdjacencia[ cidadeA ][ cidadeRelacionada ] == ADJACENTE){

			estabelecerRelacao(&matrizAdjacencia, cidadeA, cidadeRelacionada, RETIRADO); // Removendo o caminho já percorrido			

			retorno = existeCaminho(matrizAdjacencia, C, cidadeRelacionada, cidadeB); //Buscando na próxima na próxima cidade, se existe alguma cidade adjacente em comum com a cidade B

			if(retorno)	
				return retorno;
		}
		
	}
	return false;
}
bool estradaCritica(vector<vector<int>> matrizAdjacencia, int C, estrada e){

	estabelecerRelacao(&matrizAdjacencia, e.cidadeA, e.cidadeB, RETIRADO); // Removendo Estrada sendo testada
	

	return !existeCaminho( matrizAdjacencia, C, e.cidadeA, e.cidadeB);//Caso existir um caminho por outras cidades a estrada não é critica
}

int qtdEstradasCriticas(vector<vector<int>> matrizAdjacencia, vector<estrada> estradas, int C){
	int qtdCriticas = 0;

	for(estrada e : estradas)		
		if(estradaCritica(matrizAdjacencia, C, e))
			qtdCriticas++;
	
	return qtdCriticas;
}


int main( int argc, char *argv[ ]){   
	int C, E, v, u;

	vector<vector<int>> matrizAdjacencia ;

	
	

	
	
	ifstream arquivo; // arquivo de leitura dos dados
	for(int iteratorArquivo = ADJACENTE; iteratorArquivo < argc; iteratorArquivo++){

		arquivo.open(argv[iteratorArquivo], ios::in); // abre o arquivo para leitura
		if (! arquivo){ 
			cout << "=============================================\n" << argv[iteratorArquivo]<< " não encontrado.\n" << "=============================================\n";
			continue;
		} 		
			
		arquivo >> C >> E; // Obtendo os parâmetros 

		vector<vector<int>> matrizAdjacencia (C, vector<int>(C,RETIRADO));// Definindo e Iniciando a Matriz de Adjacência
		vector<estrada> estradas(E); //Definindo vetor das Estradas

		for(int estrada = 0; estrada < E; estrada++){//Preenchendo a matriz de adjacência

			arquivo >> estradas[estrada].cidadeA >> estradas[estrada].cidadeB;
			
			estradas[estrada].cidadeA--; estradas[estrada].cidadeB--;	

			estabelecerRelacao( &matrizAdjacencia, estradas[estrada].cidadeA, estradas[estrada].cidadeB, ADJACENTE);
		}


		cout << qtdEstradasCriticas(matrizAdjacencia, estradas, C) <<endl; 

		
		arquivo.close();
	}
		
	
	return 0;
}