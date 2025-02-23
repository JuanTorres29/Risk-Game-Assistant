#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include <string>
#include <iostream>
#include <iomanip>

#include "Territorio.h"  
#include "Carta.h"  



using namespace std;

class Jugador {

private:

    int id;
    string nombre;
    string color;
    list<Territorio*> territorios;  
    list<Carta> cartas;          

public:

    Jugador(int id, string nombre, string color);
    Jugador(int id, string nombre, string color, list<Territorio*> territorios, list<Carta> cartas);

    void agregarTerritorio(Territorio* territorio);  
    void removerTerritorio(Territorio* territorio);  

    void agregarCarta(Carta carta);
    void removerCarta(Carta carta);

    bool sigueVivo();  

    int cambiarCartas(int& gruposIntercambiados, list<Carta>& mazo);

    int obtenerUnidadesPorTerritorios();

    void mostrarDatos();

    void asignarUnidades(int unidades);
    list<int> tirarDados(int cantidadDados);  
    bool atacar();
    void fortificar();

    string getNombre();
    void setNombre(string nombre);

    string getColor();
    void setColor(string color);

    int getId();
    void setId(int id);

    list<Territorio*> getTerritorios();
    void setTerritorios(list<Territorio*> territorios);

    list<Carta> getCartas();
    void setCartas(list<Carta> cartas);
};

#endif
