#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <list>
#include <string>

class Jugador;  // Declaración adelantada
class Continente;  // Declaración adelantada

using namespace std;

class Territorio {

private:

    int id;
    string nombre;
    int unidades;  // Número de unidades en el territorio
    Jugador* propietario;  // puntero al jugador que posee el territorio
    Continente* continente;  // puntero al continente del que hace parte
    list<Territorio*> territoriosAdyacentes;  // Lista de punteros a territorios adyacentes

public:

    Territorio();  // Constructor por omisión

    Territorio(int id, string nombre, Continente* continente, list<Territorio*> territoriosAdyacentes);  // Constructor que inicializa el territorio con un nombre, un id, el continente del que hace parte y la lista de los territorios adyacentes

    Territorio(int id, string nombre, int unidades, Jugador* propietario, Continente* continente, list<Territorio*> territoriosAdyacentes);  // Constructor con todos los atributos

    void nuevoAdyacente(Territorio* territorio);  // Agrega un territorio adyacente a la lista de territorios adyacentes

    bool esAdyacente(Territorio* territorio);  // Retorna true si el territorio está adyacente al proporcionado, false en caso contrario

    Territorio* buscarAdyacente(int id);  // Retorna nullptr si el territorio no es adyacente o no existe

    Jugador* getPropietario();  // Retorna el propietario actual del territorio
    void setPropietario(Jugador* propietario);  // Asigna el propietario del territorio

    int getUnidades();  // Retorna el número de unidades en el territorio
    void setUnidades(int unidades);  // Cambia el número de unidades en el territorio

    int getId();  // Retorna el id del territorio
    void setId(int id);  // Cambia el id del territorio

    string getNombre();  // Retorna el nombre del territorio
    void setNombre(string nombre);  // Cambia el nombre del territorio

    Continente* getContinente();  // Retorna el continente del que hace parte el territorio
    void setContinente(Continente* continente);  // Asigna el continente del que hace parte el territorio

    list<Territorio*> getTerritoriosAdyacentes();  // Retorna una lista de los territorios adyacentes
    void setTerritoriosAdyacentes(list<Territorio*> territoriosAdyacentes);  // Cambia la lista de territorios adyacentes

};

#endif
