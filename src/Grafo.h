#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include "Territorio.h"
#include "NodoG.h"

using namespace std;

class Grafo {
private:
    list<NodoG<Territorio*>> vertices;

public:
    Grafo();
    Grafo(list<Territorio*> vertices);
    void InsVertice(Territorio* v);
    void InsArco(int v1, int v2, int c);
    int OrdenGrafo() const;
    int CostoArco(int v1, int v2);
    Territorio* InfoVertice(int v);
    void EliminarTodosLosArcos();

    list<NodoG<Territorio*>> getVertices();
};

#endif
