/*
Integrantes:
Lucas Tuon de Matos - 10417987
Eduardo Oliveira Carvalho - 10417170
*/

#include "TGrafo.h"

// variavel global que representa infinito positivo
float infinito = std::numeric_limits<float>::infinity();

// Construtor do TGrafo, responsável por 
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No início dos tempos não há arestas
    this->m = 0; 
    // aloca da matriz do TGrafo
    float **adjac = new float*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j] = infinito;
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;  // vertices
	m = 0;  // arestas
	delete [] *adj;
}

// getters 
int TGrafo::get_n() {
    return n;
}

int TGrafo::get_m() {
    return m;
}

float TGrafo::get_peso(int v, int w) {
    return adj[v][w];
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] !=  infinito)
                std::cout << adj[i][w] << " ";
            else std::cout << "i ";
    }
    std::cout << std::endl << std::endl;
}

// insere um vértice no grafo de modo que o novo
// vertice v sera o ultimo elemento na matriz 
int TGrafo::insereV(std::string rotulo) {
    int novo_n = n + 1;

    // Cria a nova matriz com tamanho aumentado
    float **nova_adj = new float*[novo_n];
    for(int i = 0; i < novo_n; i++) {
        nova_adj[i] = new float[novo_n];
    }
    // Copia os dados da matriz antiga para a nova
    for (int i = 0; i < novo_n; i++) {
        for (int j = 0; j < novo_n; j++) {
            if (i == novo_n-1 || j == novo_n-1) {
                nova_adj[i][j] = infinito;
            }
            else {
                nova_adj[i][j] = adj[i][j];
            }
        }
    }

    // insere o rotulo na lista de rotulos
    rotulos.push_back(rotulo);

    // desaloca a matriz original
    delete[] *adj;

    // atualiza o grafo
    n = novo_n;
    adj = nova_adj;
    return novo_n-1;
}
 
// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, int peso){
    // testa se nao temos a aresta
    if(adj[v][w] == infinito){
        adj[v][w] = peso;
        m++; // atualiza qtd arestas
    }
}

// remove um vertice v do Grafo
void TGrafo::removeV(int v){

    int novo_n = n - 1;
    
    // Cria a nova matriz com tamanho reduzido
    float **nova_adj = new float*[novo_n];
    for(int i = 0; i < novo_n; i++) {
        nova_adj[i] = new float[novo_n];
    }

    // preenche a matriz com infinito
    for (int i = 0; i < novo_n; i++) {
        for (int j = 0; j < novo_n; j++) {
            nova_adj[i][j] = infinito;
        }
    }
    
    // Copia os dados da matriz antiga para a nova, pulando o vértice 'v'
    int novaLinha = 0;
    for(int i = 0; i < n; i++) {

        if (i == v) {   // Caso seja a linha do vertice removido
            continue;
        }
        int novaColuna = 0;
        for(int j = 0; j < n; j++) {
            
            if (j == v) {   // Caso seja a coluna do vertice removido
                continue;
            }

            nova_adj[novaLinha][novaColuna] = adj[i][j];   // Passa o valor da matriz antiga para a nova
            novaColuna++;
        }
        novaLinha++;
    }

    // remove o rotulo da lista de rotulos
    rotulos.erase(rotulos.begin() + v);

    // desaloca a matriz original
    delete[] *adj;
    
    // atualiza o grafo
    n = novo_n;
    adj = nova_adj;
    
    // Recalcula o valor de m
    m = 0;
    for(int i = 0; i < n; i++) {    
        for(int j = 0; j < n; j++) {
            if(adj[i][j] != infinito) {
                m++;
            }
        }
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] != infinito){
        adj[v][w] = infinito;
        m--; // atualiza qtd arestas
    }
}

// Funcao que usa o DFS para verificar se um vertice atinge outro
int TGrafo::atinge(int vInicio, int vFim) {
    if (n == 0) return 0;  // grafo vazio

    int* verticesMarcados = new int[n];
    for (int i = 0; i < n; i++) {
        verticesMarcados[i] = 0;  // inicializa como não visitado
    }

    std::stack<int> P;
    P.push(vInicio);
    verticesMarcados[vInicio] = 1;

    while (!P.empty()) {
        int atual = P.top();
        P.pop();

        if (atual == vFim) {
            delete[] verticesMarcados;
            return 1; // encontrou o vFim
        }

        for (int v = 0; v < n; v++) {
            if (adj[atual][v] != infinito && verticesMarcados[v] == 0) {
                P.push(v);
                verticesMarcados[v] = 1;
            }
        }
    }

    delete[] verticesMarcados;
    return 0; // vFim não alcançável
}

// Verifica se eh conexo ou desconexo (seguindo modelo do slide)
bool TGrafo::is_conexo() {

    // Transforma a matriz do grafo G em simetrica
    int** tempAdj = new int*[n];
    for (int i = 0; i < n; i++) {
        tempAdj[i] = new int[n];
        for (int j = 0; j < n; j++) {
            tempAdj[i][j] = (adj[i][j] == 1 || adj[j][i] == 1) ? 1 : 0;
        }
    }

    std::stack<int> P;
    int verticesMarcados[n] = {0};
    int contador = 0;
    int vInicio = 0;

    if (n > 0) {
        verticesMarcados[vInicio] = 1;
        P.push(vInicio);
        contador++;
    }

    int noAtual;
    while (!P.empty()) {
        noAtual = P.top();
        P.pop();

        for (int v = 0; v < n; v++) {
            if (tempAdj[noAtual][v] == 1 && verticesMarcados[v] == 0) {
                verticesMarcados[v] = 1;
                P.push(v);
                contador++;
            }
        }
    }

    // Libera a memória alocada para a matriz temporaria
    delete[] tempAdj;

    if(contador == n){
        return true; // Se a busca encontrou todos os vertices, eh conexo
    }

    return false; // Caso contrario, ele eh desconexo
}