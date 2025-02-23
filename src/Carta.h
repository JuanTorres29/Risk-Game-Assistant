#ifndef CARTA_H
#define CARTA_H

#include <string>

#include "Territorio.h"

using namespace std;

class Carta {

private:

    int id;
    string tipo; // Infantería, Caballería, Artillería, Comodín, Misión Secreta
    string figura;
    Territorio* territorio;  // Cambiar idTerritorio a un puntero a Territorio

public:

    // Constructor que inicializa la carta con un id, un tipo, un puntero a un territorio y una figura
    Carta(int id, string tipo, Territorio* territorio, string figura);

    int getId(); // Retorna el id de la carta
    void setId(int id); // Cambia el id de la carta

    string getTipo(); // Retorna el tipo de la carta
    void setTipo(string tipo);  // Eliminar el punto y coma extra

    Territorio* getTerritorio();  // Retorna el puntero al territorio asociado a la carta
    void setTerritorio(Territorio* territorio);  // Cambia el puntero al territorio asociado a la carta

    string getFigura(); // Retorna la figura de la carta
    void setFigura(string figura); // cambia la figura de la carta

  bool operator==(const Carta& otra) const {
      return id == otra.id;
  }

};

#endif
