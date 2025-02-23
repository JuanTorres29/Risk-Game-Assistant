#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <list>
#include <string>

using namespace std;

class HuffmanNode {

private:

    char caracter; // Caracter del nodo
    int frecuencia; // Frecuencia del caracter
    HuffmanNode *hijoIzquierdo, *hijoDerecho; // Punteros a los hijos del nodo

public:

    HuffmanNode(char caracter, int frecuencia); // Constructor que inicializa el nodo con un caracter y su frecuencia

    char getCaracter(); // Retorna el caracter del nodo
    void setCaracter(char caracter); // Cambia el caracter del nodo

    int getFrecuencia(); // Retorna la frecuencia del caracter en el nodo
    void setFrecuencia(int frecuencia); // Cambia la frecuencia del caracter en el nodo

    HuffmanNode *getHijoIzq(); // Retorna el puntero al hijo izquierdo del nodo
    void setHijoIzq(HuffmanNode *nodo); // Asigna el puntero al hijo izquierdo del nodo

    HuffmanNode *getHijoDer(); // Retorna el puntero al hijo derecho del nodo
    void setHijoDer(HuffmanNode *nodo); // Asigna el puntero al hijo derecho del nodo
};

class CodigoHuffman {

public:

    char caracter; // Caracter asociado al código
    string codigo; // Código binario asociado al caracter

    CodigoHuffman(string codigo, char caracter); // Constructor que inicializa el objeto con un código binario y un caracter asociado
};

class HuffmanTree {

private:

    HuffmanNode* raiz; // Puntero a la raíz del árbol de Huffman


    //Métodos internos:

    void construirCodigos(HuffmanNode* nodo, const string& codigo, list<CodigoHuffman>& codigos); // Método recursivo para construir los códigos de Huffman.

    void ordenar(list<HuffmanNode*>& lista); // Ordena una lista de nodos de Huffman según la frecuencia.
    
    void liberarMemoria(HuffmanNode* nodo); // Método recursivo para liberar la memoria utilizada por el árbol de Huffman.
        

public:

    HuffmanTree(list<HuffmanNode*> frecuencias); // Constructor que construye el árbol de Huffman a partir de una lista de nodos de huffman

    list<CodigoHuffman> obtenerCodigos(); // Retorna una lista de códigos de Huffman construidos a partir del árbol

    string decodificar(const string& textoBinario, int numCaracteres); // Decodifica un texto binario utilizando el árbol de Huffman y retorna el texto decodificado

    ~HuffmanTree(); // Destructor que libera la memoria utilizada por el árbol de Huffman
};
#endif