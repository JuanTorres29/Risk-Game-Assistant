#include "Continente.h"

using namespace std;

Continente::Continente(int id, string nombre, string color, list<Territorio*> territorios, int unidadesRey){
    this->id = id;
    this->nombre = nombre;
    this->color = color;
    this->territorios = territorios;
    this->unidadesRey = unidadesRey;
}

bool Continente::esDueno(Jugador* jugador) {
    for (auto& territorio : territorios) {
        if (territorio->getPropietario() != jugador) {
            return false;  // Si encuentra un territorio no propiedad del jugador, retorna false
        }
    }
    return true;  // Si todos los territorios son propiedad del jugador, retorna true
}

int Continente::getUnidadesRey() {
    return unidadesRey; //Retorna las unidades del rey
}

void Continente::setUnidadesRey(int unidades) {
    unidadesRey = unidades;  //Cambia las unidades del rey
}

string Continente::getNombre() {
    return nombre;  //Retorna el nombre del continente
}

void Continente::setNombre(string nombre) {
    this->nombre = nombre;  //Cambia el nombre del continente
}

int Continente::getId() {
    return id;   //Retorna el id del continente
}

void Continente::setId(int id) {
    this->id = id;  //Cambia el id del continente
}

string Continente::getColor() {
    return color;  //Retorna el color del continente
}

void Continente::setColor(string color) {
    this->color = color;  //Cambia el color del continente
}

list<Territorio*> Continente::getTerritorios() {
    return territorios;  //Retorna la lista de territorios del continente
}

void Continente::setTerritorios(list<Territorio*> territorios) {
    this->territorios = territorios;  //Cambia la lista de territoios del contiente 
}

void Continente::agregarTerritorio(Territorio* territorio) {
    territorios.push_back(territorio); //Agrega un territorio a la lista del continente
}
