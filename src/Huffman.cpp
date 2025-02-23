#include "Huffman.h" 

using namespace std;

// Métodos de HuffmanNode

HuffmanNode::HuffmanNode(char caracter, int frecuencia) {
    this->caracter = caracter;
    this->frecuencia = frecuencia;
    this->hijoIzquierdo = this->hijoDerecho = nullptr;
}

char HuffmanNode::getCaracter() {
    return caracter; //Retorna el caracter para el Huffman Node
}

int HuffmanNode::getFrecuencia() {
    return frecuencia;  //Retorna la frecuencia para el Huffman Node
}

HuffmanNode* HuffmanNode::getHijoIzq() {
    return hijoIzquierdo;  //Retorna el hijo izquierdo  del Huffman Node
}

HuffmanNode* HuffmanNode::getHijoDer() {
    return hijoDerecho;  //Retorna el hijo derecho del Huffman Node
}

void HuffmanNode::setCaracter(char caracter) {
    this->caracter = caracter;  //Cambia el caracter para el Huffman Node
}

void HuffmanNode::setFrecuencia(int frecuencia) {
    this->frecuencia = frecuencia;  //Cambia la frecuencia para el Huffman Node
}

void HuffmanNode::setHijoIzq(HuffmanNode *nodo) {
    this->hijoIzquierdo = nodo;  //Cambia el hijo izquierdo del Huffman Node 
}

void HuffmanNode::setHijoDer(HuffmanNode *nodo) {
    this->hijoDerecho = nodo;  //Cambia el hijo derecho del Huffman Node
}

// Métodos de CodigoHuffman

CodigoHuffman::CodigoHuffman(string codigo, char caracter) {
    this->codigo = codigo;
    this->caracter = caracter;
}

// Métodos de HuffmanTree

HuffmanTree::HuffmanTree(list<HuffmanNode*> frecuencias) {
  
    // Crear lista de frecuencias ordenadas
    ordenar(frecuencias);
    while (frecuencias.size() > 1) {
        HuffmanNode *hijoIzquierdo = frecuencias.front(); frecuencias.pop_front();
        HuffmanNode *hijoDerecho = frecuencias.front(); frecuencias.pop_front();
        HuffmanNode *top = new HuffmanNode('\0', hijoIzquierdo->getFrecuencia() + hijoDerecho->getFrecuencia());
        top->setHijoIzq(hijoIzquierdo);
        top->setHijoDer(hijoDerecho);
        frecuencias.push_back(top);
        ordenar(frecuencias);
    }
    raiz = frecuencias.front();
}

void HuffmanTree::construirCodigos(HuffmanNode* nodo, const string& codigo, list<CodigoHuffman>& codigos) {
    if (!nodo) return;
    if (!nodo->getHijoIzq() && !nodo->getHijoDer()) {
        codigos.push_back(CodigoHuffman(codigo, nodo->getCaracter()));
    }
    construirCodigos(nodo->getHijoIzq(), codigo + "0", codigos);
    construirCodigos(nodo->getHijoDer(), codigo + "1", codigos);
}

void HuffmanTree::ordenar(list<HuffmanNode*>& lista) {
    lista.sort([](HuffmanNode* a, HuffmanNode* b) { return a->getFrecuencia() < b->getFrecuencia(); });
}

void HuffmanTree::liberarMemoria(HuffmanNode* nodo) {
    if (!nodo) return;
    liberarMemoria(nodo->getHijoIzq());
    liberarMemoria(nodo->getHijoDer());
    delete nodo;
}

list<CodigoHuffman> HuffmanTree::obtenerCodigos() {
        list<CodigoHuffman> codigos;
        construirCodigos(raiz, "", codigos); // Construye los códigos de Huffman
        return codigos; // Retorna la lista de códigos
    }

 // Función para decodificar un texto binario
string HuffmanTree::decodificar(const string& textoBinario, int numCaracteres) {
    string textoDecodificado;
    HuffmanNode* nodoActual = raiz;
    int contador = 0;
    for (char bit : textoBinario) {
        if (bit == '0') {
            if (nodoActual->getHijoIzq()) nodoActual = nodoActual->getHijoIzq();
        }else if (bit == '1') {
            if (nodoActual->getHijoDer()) nodoActual = nodoActual->getHijoDer();
        }
      
            if (!nodoActual->getHijoIzq() && !nodoActual->getHijoDer()) {
                textoDecodificado += nodoActual->getCaracter();
                nodoActual = raiz;
                contador++;
            }
            if(contador == numCaracteres) break;
        }
  
    return textoDecodificado;
}


HuffmanTree::~HuffmanTree() {
    liberarMemoria(raiz);
}
