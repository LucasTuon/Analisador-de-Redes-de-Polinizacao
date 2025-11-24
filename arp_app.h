/*
Integrantes:
Lucas Tuon de Matos - 10417987
Eduardo Oliveira Carvalho - 10417170
*/

#ifndef ___ARP_APP___
#define ___ARP_APP___

#include <iostream>
#include <fstream>
#include <string>

#include "TGrafo.h"

// variaveis globais do menu
std::string buffer = ""; // buffer de leitura de arquivo ou terminal
int opc = 0; // opc do menu
int tipo; // tipo do grafo
std::ifstream arq_entrada; // arquivo de leitura
std::ofstream arq_saida; // arquivo de escrita
TGrafo *grafo; // ponteiro para estrutura do grafo em memoria

// implementacao do menu
void menu();
void imprime_menu();
void recebe_opc();

// funcoes do menu
void ler_arquivo();
void escrever_arquivo();
void inserir_vertice();
void inserir_aresta();
void remover_vertice();
void remover_aresta();
void mostrar_arquivo();
void mostrar_grafo();
void obter_conexidade();
void gerar_grafo_reduzido();
void encerrar();

// funcoes auxiliares para tratarem arquivos
TGrafo *entrada_arquivo(std::string nome_arquivo); 
bool saida_arquivo(std::string nome_arquivo);
#endif
