/*
Integrantes:
Lucas Tuon de Matos - 10417987
Eduardo Oliveira Carvalho - 10417170
*/

/*
Implementacao de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjacencia
e metodos para utilizacao de um grafo dirigido.
*/
#ifndef ___GRAFO_VALORADO_MATRIZ___

#define ___GRAFO_VALORADO_MATRIZ___

#include <iostream>
#include <limits>
#include <vector>
#include <stack>
#include <algorithm> // std::find

// definicao de uma estrutura para armezanar um grafo
class TGrafo{
	private:
		int n; // quantidade de vertices
		int m; // quantidade de arestas
		float **adj; //matriz de adjacencia
		int atinge(int vInicio, int vFim);
		

	public:
		std::vector<std::string> rotulos; // lista de rotulos
		TGrafo(int n);
		~TGrafo();
		int get_n();
		int get_m();
		float get_peso(int v, int w);
		void show();
		int insereV(std::string rotulo);
		void insereA(int v, int w, int peso);
		void removeV(int v);
		void removeA(int v, int w);
		bool is_conexo();
		int insereR(std::string rotulo);
};

#endif
