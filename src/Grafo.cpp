#include "Grafo.h"

Grafo::Grafo() {
    this->vertices = list< NodoG<Territorio*> >();
}

Grafo::Grafo(list<Territorio*> vertices) {
    for (Territorio* t : vertices) {
        this->vertices.push_back(NodoG<Territorio*>(t));
    }
}

void Grafo::InsVertice(Territorio* t) {
    this->vertices.push_back(NodoG<Territorio*>(t));
}

void Grafo::InsArco(int v1, int v2, int c) {
    auto it = this->vertices.begin();
    advance(it, v1);
    it->AgregarArco(v2, c);
}

int Grafo::OrdenGrafo() const {
    return this->vertices.size();
}

Territorio* Grafo::InfoVertice(int v){
    auto it = this->vertices.begin();
    advance(it, v);
    return it->ObtenerInfo();
}

int Grafo::CostoArco(int v1, int v2){
  auto it = this->vertices.begin();
  advance(it, v1);
  return it->CostoArco(v2);
}

void Grafo::EliminarTodosLosArcos() {
    for (auto &nodo : vertices) {
        nodo.eliminarArcos();
    }
}

list<NodoG<Territorio*>> Grafo::getVertices(){
  return this->vertices;
}

