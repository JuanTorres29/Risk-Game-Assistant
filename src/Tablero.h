#ifndef TABLERO_H
#define TABLERO_H

#include "Carta.h"
#include "Continente.h"
#include "Jugador.h"
#include "Territorio.h"
#include "Huffman.h" 
#include "Grafo.h"

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;



class Tablero {

private:

    list<Continente> continentes; // Lista de continentes en el juego
    list<Jugador> jugadores; // Lista de jugadores en el juego
    list<Carta> mazo; // Lista de cartas en el juego
    list<Territorio> territorios; // Lista de territorios en el juego

    Grafo grafo; // Grafo de ataque de territorios

    bool juegoInicializado;
    int idJugadorEnTurno;
    int cartasIntercambiadas;

    bool hayGanador(); // Retorna true si ya hay un ganador
    string obtenerColor(int idJugador); //Retorna un color

    void repartirTerritorios(); // Reparte los territorios entre los jugadores al inicio del juego

    string lecturaArchivoTexto(const string& nombreArchivo); //Retorna un string con el resultado de la lectura del archivo de texto
    string lecturaArchivoBinario(const string& nombreArchivo); //Retorna un string con el resultado de la lectura del binario (decodificado)

    bool atacar(Jugador* jugadorAtaca, int idTerritorioDesde, int idTerritorioHacia); // Realiza un ataque desde un territorio a otro y aplica los resultados, retorna true si el territorio es conquistado
    bool fortificar(Jugador* jugador, int idTerritorioDesde, int idTerritorioHacia); // Mueve unidades de ejército de un territorio a otro, retorna true si el movimiento es exitoso

    int obtenerUnidadesPorContinentes(Jugador* jugador); // Obtiene el número de unidades que recibe el jugador por ser dueño de un continente

    Carta* buscarCarta(int id_carta); // Retorna apuntador a la carta si se encuentra
    Jugador* buscarJugador(int id_jugador); // Retorna apuntador al jugador si se encuentra
    Territorio* buscarTerritorio(int id_territorio) ; // Retorna apuntador al territorio si se encuentra
    Continente* buscarContinente(int id_continente); // Retorna apuntador al Continente si se encuentra
    void insertarArcosGrafo(); // Inserta los arcos al grafo de territorios con base en el jugador que tenga el turno
    
    

public:

    Tablero(); // Constructor por omisión

    Tablero(list<Continente> continentes, list<Jugador> jugadores, list<Carta> mazo, list<Territorio> territorios); // Constructor con todos los atributos

    
    void agregarContinente(Continente continente); // Agrega un continente a la lista de continentes del tablero
    
    void agregarJugador(Jugador jugador); // Agrega un jugador a la lista de jugadores del juego

    void agregarCarta(Carta carta); // Agrega una carta al mazo del juego

    void agregarTerritorio(Territorio territorio); // Agrega un territorio a la lista de territorios del juego

    void turno(int idJugador); // Serie de funciones que ejecuta cada jugador en su turno

    void verEstadoDelJuego(); // Imprime en pantalla el estado del juego
    
    list<Continente> getContinentes(); // Retorna una lista de los continentes en el tablero
    
    list<Jugador> getJugadores(); // Retorna una lista de los jugadores en el juego
    
    list<Carta> getMazo(); // Retorna una lista de las cartas en el mazo

    list<Territorio> getTerritorios(); // Retorna una lista de los territorios en el mazo

    void setContinentes(list<Continente> continentes); // cambia la lista de los continentes en el tablero
    
    void setJugadores(list<Jugador> jugadores); // cambia la lista de los jugadores en el juego
    
    void setMazo(list<Carta> mazo); // cambia la lista de las cartas en el mazo

    void setTerritorios(list<Territorio> territorios); // cambia la lista de los territorios en el mazo

    string estadoJuego(); // Retorna un string con el estado de la partida

    bool guardar(const string& nombreArchivo); // Guarda el estado actual del juego en un archivo de texto
    
    bool guardarComprimido(const string& nombreArchivo); // Guarda el estado actual del juego en un archivo binario comprimido utilizando la codificación de Huffman
    
    bool inicializar(const string& nombreArchivo); // Inicializa el juego con los datos contenidos en el archivo identificado por <nombreArchivo>
    bool inicializar(); // Inicializa el juego desde cero

    void FloydWarshall(vector<vector<int>> &distancias, vector<vector<int>> &predecesores, const int INFINITO);
    void costoConquista(int idTerritorio);
    void conquistaMasBarata();

    void llenarTablero();
};
  
#endif