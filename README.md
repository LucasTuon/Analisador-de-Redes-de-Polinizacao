# Projeto Teoria dos Grafos - Analisador de Redes de Polinização

Este repositório contém o código-fonte de uma aplicação em C++ para a criação, manipulação e análise de grafos dirigidos e valorados. A estrutura do grafo é implementada utilizando uma matriz de adjacência e a interação com o usuário é feita através de um menu de console interativo.

Integrantes: 
- Lucas Tuon de Matos        - 10417987
- Eduardo Oliveira Carvalho  - 10417170

## Tema
O objetivo principal do projeto é fornecer uma ferramenta para estudar algoritmos de grafos. A classe TGrafo encapsula a lógica da estrutura de dados, enquanto a aplicação oferece uma interface para que o usuário possa testar as funcionalidades de forma prática, seja criando um grafo do zero ou carregando um a partir de um arquivo.

## Funcionalidades
O programa oferece um menu com as seguintes opções:

- Manipulação Básica do Grafo:

- Adicionar e remover vértices dinamicamente.

- Adicionar e remover arestas com seus respectivos pesos.

- Exibir a matriz de adjacência do grafo em memória.

Persistência de Dados:

- Carregar a estrutura de um grafo a partir de um arquivo de texto.

- Salvar o grafo atual em memória para um arquivo de texto.

Análise de Conectividade:

Um algoritmo que determina o nível de conectividade do grafo, classificando-o como:

- Desconexo

- Conexo

Grafo Reduzido:

Essa opção foi retirada após a mudança para um grafo não direcionado.


## Estrutura dos Arquivos

- TGrafo.h: Arquivo de cabeçalho com a definição da classe TGrafo e a assinatura de seus métodos.

- TGrafo.cpp: Implementação dos métodos da classe TGrafo, contendo toda a lógica de manipulação e análise do grafo.

- arp_app.h: Declarações das funções da aplicação e do menu interativo.

- arp_app.cpp: Arquivo principal que contém a função main e a lógica para a interface de linha de comando.

## Link para o vídeo
https://youtu.be/vRDOtkG567A
