#ifndef NODOG_H
#define NODOG_H

#include <list>
#include <utility>
#include "Territorio.h"

using namespace std;

template <typename T>
class NodoG {
private:
    T info;
    list<pair<int,int>> arcos;

public:
    NodoG(){
      this->info = T();
    }

    NodoG(T info){
      this->info = info;
    }

    void AgregarArco(int destino, int costo){
      this->arcos.push_back(make_pair(destino, costo));
    }

    T ObtenerInfo() const{
      return this->info;
    }

    int CostoArco(int territorio) {
        for(auto it = this->arcos.begin(); it != this->arcos.end(); it++){
        if (it->first == territorio) {
            return it->second;
        }
    }
      return -1;
    }

    void eliminarArcos() {
        arcos.clear();
    }
};

#endif

