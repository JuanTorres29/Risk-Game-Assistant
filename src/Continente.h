#ifndef CONTINENTE_H
#define CONTINENTE_H

#include <list>
#include <string>

#include "Territorio.h" 

using namespace std;


class Continente {

private:

    int id;
    string nombre;
    string color;
    list<Territorio*> territorios;  // Lista de punteros a territorios que conforman el continente
    int unidadesRey;

public:

    Continente(int id, string nombre, string color, list<Territorio*> territorios, int unidadesRey);  // Constructor que inicializa el continente con un nombre, un id, la lista de territorios que lo conforman y las unidades recibidas por el rey del continente

    void agregarTerritorio(Territorio* territorio);  // Agrega un puntero a territorio a la lista de territorios del continente

    bool esDueno(Jugador* jugador);

    int getUnidadesRey();  // Retorna el número de unidades que recibe el jugador al apropiarse de todo el continente
    void setUnidadesRey(int unidades);  // Cambia las unidades recibidas por el rey del continente

    string getNombre();  // Retorna el nombre del continente
    void setNombre(string nombre);  // Cambia el nombre del continente

    int getId();  // Retorna el id del continente
    void setId(int id);  // Cambia el id del continente

    string getColor();  // Retorna el color del continente
    void setColor(string color);  // Cambia el color del continente

    list<Territorio*> getTerritorios();  // Retorna una lista de punteros a los territorios que conforman el continente
    void setTerritorios(list<Territorio*> territorios);  // Cambia la lista de punteros a los territorios del continente
};
#endif
