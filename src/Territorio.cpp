#include "Territorio.h"

Territorio::Territorio() {

    this->id = 0;
    this->nombre = "";
    this->unidades = 0;
    this->territoriosAdyacentes = list<Territorio*>();
    this->propietario = nullptr;
    this->continente = nullptr;
    
}

Territorio::Territorio(int id, string nombre, Continente* continente, list<Territorio*> territoriosAdyacentes) {
    this->id = id;
    this->nombre = nombre;
    this->continente = continente;
    this->territoriosAdyacentes = territoriosAdyacentes;
    this->unidades = 0;
    this->propietario = nullptr;
}

Territorio::Territorio(int id, string nombre, int unidades, Jugador* propietario, Continente* continente, list<Territorio*> territoriosAdyacentes) {
    this->id = id;
    this->nombre = nombre;
    this->unidades = unidades;
    this->propietario = propietario;
    this->continente = continente;
    this->territoriosAdyacentes = territoriosAdyacentes;
}

void Territorio::nuevoAdyacente(Territorio* territorio) {
    territoriosAdyacentes.push_back(territorio);
}

bool Territorio::esAdyacente(Territorio* territorio) {
    for(Territorio* adyacente : territoriosAdyacentes) {
        if(adyacente == territorio) {
            return true;
        }
    }
    return false;
}

Territorio* Territorio::buscarAdyacente(int id) {
    for (Territorio* territorio : territoriosAdyacentes) {
        if (territorio->getId() == id) {
            return territorio;
        }
    }
    return nullptr; 
}

Jugador* Territorio::getPropietario() {
    return propietario;
}

void Territorio::setPropietario(Jugador* propietario) {
    this->propietario = propietario;
}

int Territorio::getUnidades() {
    return unidades;
}

void Territorio::setUnidades(int unidades) {
    this->unidades = unidades;
}

int Territorio::getId() {
    return id;
}

void Territorio::setId(int id) {
    this->id = id;
}

string Territorio::getNombre() {
    return nombre;
}

void Territorio::setNombre(string nombre) {
    this->nombre = nombre;
}

Continente* Territorio::getContinente() {
    return continente;
}

void Territorio::setContinente(Continente* continente) {
    this->continente = continente;
}

list<Territorio*> Territorio::getTerritoriosAdyacentes() {
    return territoriosAdyacentes;
}

void Territorio::setTerritoriosAdyacentes(list<Territorio*> territoriosAdyacentes) {
    this->territoriosAdyacentes = territoriosAdyacentes;
}
