/*
Integrantes:
Lucas Tuon de Matos - 10417987
Eduardo Oliveira Carvalho - 10417170
*/

#include "arp_app.h"

extern float infinito;

int main() {
    menu();
    return 0;
}

void menu() {
    while (true) {
        imprime_menu();
        recebe_opc();
        switch (opc) {
        case 1:
            ler_arquivo();
            break;
        case 2:
            escrever_arquivo();
            break;
        case 3:
            inserir_vertice();
            break;
        case 4:
            inserir_aresta();
            break;
        case 5:
            remover_vertice();
            break;
        case 6:
            remover_aresta();
            break;
        case 7:
            mostrar_arquivo();
            break;
        case 8:
            mostrar_grafo();
            break;
        case 9:
            obter_conexidade();
            break;
        case 10:
            gerar_grafo_reduzido();
            break;
        case 0:
            encerrar();
            break;
        default:
            std::cout << "Opcao invalida" << std::endl << std::endl;
            break;
        }
    }
    
}

// imprime o menu de opcoes no terminal
void imprime_menu() {
    std::cout << "###########################################" << std::endl;
    std::cout << "    ANALISADOR DE REDES DE POLINIZACAO" << std::endl;
    std::cout << "###########################################" << std::endl << std::endl;

    std::cout << " 1. Ler de arquivo" << std::endl;
    std::cout << " 2. Gravar em arquivo" << std::endl;
    std::cout << " 3. Inserir vertice" << std::endl;
    std::cout << " 4. Inserir aresta" << std::endl;
    std::cout << " 5. Remover vertice" << std::endl;
    std::cout << " 6. Remover aresta" << std::endl;
    std::cout << " 7. Mostrar conteudo do arquivo" << std::endl;
    std::cout << " 8. Mostrar grafo" << std::endl;
    std::cout << " 9. Processar conexidade" << std::endl;
    std::cout << "10. Construir grafo reduzido" << std::endl;
    std::cout << " 0. Encerrar" << std::endl;

    std::cout << std::endl << "Opcao: ";
}

// recebe a opcao inserida no terminal
void recebe_opc() {
    std::getline(std::cin, buffer); // le string 

    try {
        opc = std::stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza opc para uma opcao invalida (-1)
    catch (std::invalid_argument) {
        opc = -1; 
    }
    return;
}

// funcao do menu que cria grafo a partir de arquivo
void ler_arquivo() {
    // usuario informa o nome do arquivo
    std::cout << "Nome do arquivo: ";
    std::getline(std::cin, buffer);
    
    grafo = entrada_arquivo(buffer);

    // verifica se o grafo foi gerado
    if (grafo == nullptr) {
        std::cout <<  "Erro ao criar o grafo. Verifique o nome e conteudo do arquivo." << std::endl << std::endl;
    }
    else {
        std::cout <<  "Grafo criado com sucesso." << std::endl << std::endl;
    }

    return;
}

// le o arquivo informado pelo usuario e constroi o grafo
TGrafo *entrada_arquivo(std::string nome_arquivo) {
    arq_entrada.open(nome_arquivo);
    // verifica se o arquivo foi aberto corretamente
    if (!arq_entrada.is_open()) {
        return nullptr;
    }

    // le o tipo do grafo e armazena na var global tipo 
    getline(arq_entrada, buffer);
    tipo = stoi(buffer);

    // le o numero de vertices 
    getline(arq_entrada, buffer);
    int n = stoi(buffer);
    if (n < 0) { // verifica se o numero lido eh valido
        arq_entrada.close();
        return nullptr;
    }

    // instancia o grafo em memoria
    TGrafo *ptrG = new TGrafo(n);

    // le os vertices
    std::string r;
    char delimiter = ' ';
    for (int i = 0; i < n; i++) {
        getline(arq_entrada, buffer);
        r = buffer.substr(buffer.find(delimiter)+1, buffer.size()); // le o rotulo
        ptrG->rotulos.push_back(r); // insere o rotulo na lista de rotulos
    }

    // le o numero de arestas 
    getline(arq_entrada, buffer);
    int m = stoi(buffer);

    // le cada aresta e insere no grafo
    int v, w;
    float peso;
    for (int i = 0; i < m; i++) {
        getline(arq_entrada, buffer);
        v = std::stoi(buffer.substr(0, buffer.find(delimiter)));
        w = std::stoi(buffer.substr(buffer.find(delimiter)+1, buffer.find(delimiter)+2));
        peso = std::stof(buffer.substr(buffer.find(delimiter)+2, buffer.size()));
        ptrG->insereA(v, w, peso);
    }

    arq_entrada.close();
    return ptrG;
}

// funcao do menu que escreve arquivo a partir de grafo em memoria
void escrever_arquivo() {
    std::cout << "Nome do arquivo: ";
    std::getline(std::cin, buffer);
    // verifica se o arquivo foi gerado
    if (!saida_arquivo(buffer)) {
        std::cout <<  "Erro ao escrever em arquivo. Tente novamente." << std::endl << std::endl;
    }
    else {
        std::cout <<  "Grafo escrito em arquivo com sucesso." << std::endl << std::endl;
    }
    
    return;
}

// formata e escreve o grafo salvo em memoria no arquivo informado pelo usuario 
bool saida_arquivo(std::string nome_arquivo) {
    arq_saida.open(nome_arquivo);
    // verifica se o arquivo foi aberto corretamente
    if (!arq_saida.is_open()) {
        return false;
    }

    // escreve o tipo de grafo
    arq_saida << tipo << std::endl;

    // escreve o numero de vertices e cada vertice em uma linha 
    int n = grafo->get_n();
    arq_saida << n << std::endl;
    for (int i = 0; i < n; i++) {
        arq_saida << i << " " << grafo->rotulos.at(i) << std::endl;
    }

    // escreve o numero de arestas e cada aresta em uma linha
    int m = grafo->get_m();
    arq_saida << m << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grafo->get_peso(i,j) != infinito) {
                arq_saida << i << " " << j << " " << grafo->get_peso(i,j) << std::endl;
            }
            
        }
        
    }

    arq_saida.close();
    return true;
}

// insere um vertice no grafo em memoria
void inserir_vertice() {
    // le rotulo a ser iserido
    std::string r;
    std::cout << "Rotulo para o vertice: ";
    std::getline(std::cin, buffer);
    r = buffer;
    if (r == "") {
        std::cout << "Rotulo invalido" << std::endl;
        return;
    }
    int v = grafo->insereV(r);
    std::cout <<  "Vertice " << v << " inserido." << std::endl << std::endl;
    return;
}

// insere uma aresta no grafo em memoria
void inserir_aresta() {
    // le vertice origem
    int v;
    std::cout << "Vertice de origem: ";
    std::getline(std::cin, buffer);
    try {
        v = stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza v para um vertice invalido (-1)
    catch (std::invalid_argument) {
        v = -1;
    }
    if (v < 0 || v >= grafo->get_n()) {
        std::cout << "Vertice invalido" << std::endl;
        return;
    }
    

    // le vertice destino
    int w;
    std::cout << "Vertice de destino: ";
    std::getline(std::cin, buffer);
    try {
        w = stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza w para um vertice invalido (-1)
    catch (std::invalid_argument) {
        w = -1;
    }
    if (w < 0 || w >= grafo->get_n()) {
        std::cout << "Vertice invalido" << std::endl;
        return;
    }


    // le peso da aresta
    float peso;
    std::cout << "Peso: ";
    std::getline(std::cin, buffer);
    try {
        peso = stof(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza peso para um valor invalido (-1)
    catch (std::invalid_argument) {
        peso = -1;
    }
    if (peso < 0) {
        std::cout << "Peso invalido. Deve ser valor positivo." << std::endl;
        return;
    }

    grafo->insereA(v,w,peso); // insere a aresta no grafo
    std::cout <<  "Aresta inserida." << std::endl << std::endl;
    return;
}

// remove um vertice do grafo em memoria
void remover_vertice() {
    // le vertice a ser removido
    int v;
    std::cout << "Vertice (indice): ";
    std::getline(std::cin, buffer);
    try {
        v = stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza v para um vertice invalido (-1)
    catch (std::invalid_argument) {
        v = -1;
    }
    if (v < 0 || v >= grafo->get_n()) {
        std::cout << "Vertice invalido" << std::endl;
        return;
    }

    grafo->removeV(v); // remove o vertice do grafo
    std::cout <<  "Vertice removido." << std::endl << std::endl;
    return;
}

// insere uma aresta do grafo em memoria
void remover_aresta() {
    // le vertice origem
    int v;
    std::cout << "Vertice de origem: ";
    std::getline(std::cin, buffer);
    try {
        v = stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza v para um vertice invalido (-1)
    catch (std::invalid_argument) {
        v = -1;
    }
    if (v < 0 || v >= grafo->get_n()) {
        std::cout << "Vertice invalido" << std::endl;
        return;
    }
    

    // le vertice destino
    int w;
    std::cout << "Vertice de destino: ";
    std::getline(std::cin, buffer);
    try {
        w = stoi(buffer);
    }
    // se usuario digita um caracter ao inves de um numero
    // atualiza w para um vertice invalido (-1)
    catch (std::invalid_argument) {
        w = -1;
    }
    if (w < 0 || w  >= grafo->get_n()) {
        std::cout << "Vertice invalido" << std::endl;
        return;
    }

    grafo->removeA(v,w); // remove a aresta do grafo
    std::cout <<  "Aresta removida." << std::endl << std::endl;
    return;
}

// mostra o conteudo do arquivo informado pelo usuario
void mostrar_arquivo() {
    // usuario informa o nome do arquivo
    std::cout << "Nome do arquivo: ";
    std::getline(std::cin, buffer);

    arq_entrada.open(buffer);
    // verifica se o arquivo foi aberto corretamente
    if (!arq_entrada.is_open()) {
        std::cout <<  "Erro ao abrir arquivo. Verifique se o nome foi informado corretamente." << std::endl << std::endl;
        return;
    }

    while (!arq_entrada.eof()) {
        getline(arq_entrada, buffer);
        std::cout << buffer << std::endl;
    }

    std::cout << std::endl << "Fim do arquivo." << std::endl << std::endl;

    arq_entrada.close();
    return;
}

// mostra o conteudo do grafo em memoria
void mostrar_grafo() {
    grafo->show();
    return;
}

// processa a conexidade do grafo em memoria e mostra o valor obtido
void obter_conexidade() {
    std::cout << "O grafo eh";
    grafo->is_conexo() ? std::cout << "conexo" : std::cout << "desconexo";
    std::cout << "." << std::endl << std::endl;
    return;
}

// informa o usuario que nao eh possivel gerar grafo reduzido
void gerar_grafo_reduzido() {
    std::cout << "O grafo eh nao direcionado. Nao ha grafo reduzido para exibir:" << std::endl;
    return;
}

// encerra o programa
void encerrar() {
    std::cout << "Encerrando..." << std::endl;
    delete grafo; // desaloca memoria para grafo
    exit(0); 
    return;
}
