#include "Carta.h"

using namespace std;

Carta::Carta(int id, string tipo, Territorio* territorio, string figura) {
    this->id = id;
    this->tipo = tipo;
    this->territorio = territorio;
    this->figura = figura;
}

int Carta::getId() {
    return id;
}  // Retorna el id de la carta

void Carta::setId(int id) {
    this->id = id;
}  // Cambia el id de la carta

string Carta::getTipo() {
    return tipo;
}  // Retorna el tipo de la carta

void Carta::setTipo(string tipo) {
    this->tipo = tipo;
}  // Cambia el tipo de la carta

Territorio* Carta::getTerritorio() {
    return territorio;
}  // Retorna el puntero al territorio asociado a la carta

void Carta::setTerritorio(Territorio* territorio) {
    this->territorio = territorio;
}  // Cambia el puntero al territorio asociado a la carta

string Carta::getFigura() {
    return figura;
}  // Retorna la figura de la carta

void Carta::setFigura(string figura) {
    this->figura = figura;
}  // Cambia la figura de la carta
