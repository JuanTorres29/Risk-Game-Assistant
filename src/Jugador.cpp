#include "Jugador.h"

using namespace std;


Jugador::Jugador(int id, string nombre, string color) {
    this->id = id;
    this->nombre = nombre;
    this->color = color;
}

Jugador::Jugador(int id, string nombre, string color, list<Territorio*> territorios, list<Carta> cartas) {
    this->id = id;
    this->nombre = nombre;
    this->color = color;
    this->territorios = territorios;
    this->cartas = cartas;
}

void Jugador::agregarCarta(Carta carta){
    this->cartas.push_back(carta);
}
void Jugador::removerCarta(Carta carta){
    this->cartas.remove(carta);
}

void Jugador::agregarTerritorio(Territorio* territorio) {
    this->territorios.push_back(territorio);
}

void Jugador::removerTerritorio(Territorio* territorio) {
    this->territorios.remove(territorio);
}

bool Jugador::sigueVivo() {
    return !(this->territorios.empty());
}

int Jugador::cambiarCartas(int& gruposIntercambiados, list<Carta>& mazo){

    if(cartas.size() < 3){
      return 0;
    }
  
    int unidades;

    if(gruposIntercambiados == 1){
      unidades = 4;
    }
    else if(gruposIntercambiados == 2){
        unidades = 6;
    }
    else if(gruposIntercambiados == 3){
        unidades = 8;
    }
    else if(gruposIntercambiados == 4){
        unidades = 10;
    }
    else if(gruposIntercambiados == 5){
        unidades = 12;
    }
    else if(gruposIntercambiados == 6){
        unidades = 15;
    }
    else if(gruposIntercambiados > 6){
        unidades = 15 + (5*(gruposIntercambiados - 6));
    }

    for (auto it1 = cartas.begin(); it1 != cartas.end(); it1++) {
        for (auto it2 = next(it1); it2 != cartas.end(); it2++) {
            for (auto it3 = next(it2); it3 != cartas.end(); it3++) {

                bool algunComodin = (it1)->getTipo() == "CM" || it2->getTipo() == "CM" || it3->getTipo() == "CM";
                
                if (it1->getFigura() == it2->getFigura() && it2->getFigura() == it3->getFigura()) {
                    if (it1->getTerritorio()->getPropietario() == this){
                       it1->getTerritorio()->setUnidades(it1->getTerritorio()->getUnidades() + 2);
                    }
                    if (it2->getTerritorio()->getPropietario() == this){
                        it2->getTerritorio()->setUnidades(it2->getTerritorio()->getUnidades() + 2);
                    }
                    if (it3->getTerritorio()->getPropietario() == this){
                        it3->getTerritorio()->setUnidades(it3->getTerritorio()->getUnidades() + 2);
                    }

                    cout << "\n\nCartas cambiadas: " << it1->getFigura() << " - " << it2->getFigura() << " - " << it3->getFigura() << endl<<endl;

                    mazo.push_back(*it1);
                    mazo.push_back(*it2);
                    mazo.push_back(*it3);

                    removerCarta(*it1);
                    removerCarta(*it2);
                    removerCarta(*it3);

                    gruposIntercambiados++;
                    return unidades;
                }
              
                else if (it1->getFigura() != it2->getFigura() && it2->getFigura() != it3->getFigura() && it1->getFigura() != it3->getFigura()) {
                  
                  if(it1->getTipo() != "CM"){
                    if (it1->getTerritorio()->getPropietario() == this){
                       it1->getTerritorio()->setUnidades(it1->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  if(it2->getTipo() != "CM"){
                    if (it2->getTerritorio()->getPropietario() == this){
                        it2->getTerritorio()->setUnidades(it2->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  if(it3->getTipo() != "CM"){
                    if (it3->getTerritorio()->getPropietario() == this){
                        it3->getTerritorio()->setUnidades(it3->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  cout << "\n\nCartas cambiadas: " << it1->getFigura() << " - " << it2->getFigura() << " - " << it3->getFigura() << endl<<endl;

                  mazo.push_back(*it1);
                  mazo.push_back(*it2);
                  mazo.push_back(*it3);

                  removerCarta(*it1);
                  removerCarta(*it2);
                  removerCarta(*it3);

                  return unidades;
                }

                else if(algunComodin && (it1->getTipo() != "CM" && it2->getTipo() != "CM" || it1->getTipo() != "CM" && it3->getTipo() != "CM" || it2->getTipo() != "CM" && it3->getTipo() != "CM")){

                  if(it1->getTipo() != "CM"){
                    if (it1->getTerritorio()->getPropietario() == this){
                       it1->getTerritorio()->setUnidades(it1->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  if(it2->getTipo() != "CM"){
                    if (it2->getTerritorio()->getPropietario() == this){
                        it2->getTerritorio()->setUnidades(it2->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  if(it3->getTipo() != "CM"){
                    if (it3->getTerritorio()->getPropietario() == this){
                        it3->getTerritorio()->setUnidades(it3->getTerritorio()->getUnidades() + 2);
                    }
                  }

                  cout << "\n\nCartas cambiadas: " << it1->getFigura() << " - " << it2->getFigura() << " - " << it3->getFigura() << endl<<endl;

                  mazo.push_back(*it1);
                  mazo.push_back(*it2);
                  mazo.push_back(*it3);

                  removerCarta(*it1);
                  removerCarta(*it2);
                  removerCarta(*it3);

                  return unidades;
                  
                }
            }
        }
    }
    return 0;
}

int Jugador::obtenerUnidadesPorTerritorios(){
    int numTerritorios = territorios.size();
    return numTerritorios / 3;
}

void Jugador::mostrarDatos() {

  cout << endl;

  int maxIdWidth = 0;
  int maxNombreWidth = 0;
  int maxUnidadesWidth = 0;

  for (const auto& territorio : territorios) {
      maxIdWidth = max(maxIdWidth, static_cast<int>(to_string(territorio->getId()).length()));
      maxNombreWidth = max(maxNombreWidth, static_cast<int>(territorio->getNombre().length()));
      maxUnidadesWidth = max(maxUnidadesWidth, static_cast<int>(to_string(territorio->getUnidades()).length()));
  }

  // Cabecera de la tabla
  cout << left << setw(maxIdWidth + 2) << "ID";
  cout << setw(maxNombreWidth + 2) << "Nombre";
  cout << setw(maxUnidadesWidth + 2) << "Unidades" << endl;

  // Línea separadora
  cout << setfill('-');
  cout << setw(maxIdWidth + 2) << "" << setw(maxNombreWidth + 2) << "" << setw(maxUnidadesWidth + 2) << "" << endl;
  cout << setfill(' ');

  // Datos de los territorios
  for (const auto& territorio : territorios) {
      cout << left << setw(maxIdWidth + 2) << territorio->getId();
      cout << setw(maxNombreWidth + 2) << territorio->getNombre();
      cout << setw(maxUnidadesWidth + 2) << territorio->getUnidades() << endl;
  }

    cout << endl;
  }


void Jugador::asignarUnidades(int unidades) {
    while (unidades > 0) {  // Mientras haya unidades por asignar
        // Mostrar la lista de territorios del jugador y las unidades restantes

        cout << "--Turno de "<<nombre<<"--\n"<<endl;
      
        cout << "Unidades restantes para asignar: " << unidades << endl;
        mostrarDatos();

        // Solicitar al jugador que elija un territorio y la cantidad de unidades a asignar
        int idTerritorio, unidadesAsignar;
        cout << "Ingresa el ID del territorio al que deseas asignar unidades: ";
        cin >> idTerritorio;
        cout << "Ingresa la cantidad de unidades a asignar: ";
        cin >> unidadesAsignar;

        // Validar la entrada
        if (unidadesAsignar <= 0 || unidadesAsignar > unidades) {
            cout << "\n(Error) Cantidad de unidades no válida. Inténtalo de nuevo.\n";
          cout << "\n\n---<Presione enter para continuar>---" << endl;

          getchar();
          getchar();
          system("clear");
            continue;  // Vuelve al inicio del bucle
        }

        // Buscar el territorio seleccionado
        Territorio* territorioSeleccionado = nullptr;
      
        for (Territorio* territorio : territorios) {
            if (territorio->getId() == idTerritorio) {
                territorioSeleccionado = territorio;
                break;
            }
        }

        // Verificar que el territorio pertenezca al jugador
        if (!territorioSeleccionado || territorioSeleccionado->getPropietario()->getId() != this->getId()) {
            cout << "\n(Error) El territorio no le pertenece.\n";
            cout << "\n\n---<Presione enter para continuar>---" << endl;

            getchar();
            getchar();
            system("clear");
            continue;  // Vuelve al inicio del bucle
        }
  
        // Asignar las unidades al territorio seleccionado
        territorioSeleccionado->setUnidades(territorioSeleccionado->getUnidades() + unidadesAsignar);
        unidades -= unidadesAsignar;  // Reducir las unidades restantes por asignar

        cout << "\nUnidades asignadas con éxito. Unidades restantes: " << unidades << endl;

      cout << "\n\n---<Presione enter para continuar>---" << endl;

        getchar();
        getchar();
        system("clear");
      
    }

    cout << "Todas las unidades han sido asignadas.\n";

    cout << "\n\n---<Presione enter para continuar>---" << endl;

    getchar();
    system("clear");
}

list<int> Jugador::tirarDados(int cantidadDados) {

    list<int> resultados;
    for(int i = 0; i < cantidadDados; ++i) {
        int valorDado = rand() % 6 + 1;
        resultados.push_back(valorDado);
    }
    return resultados;
}

bool Jugador::atacar() {

system("clear");

cout << "--Turno de "<<nombre<<"--\n"<<endl;

mostrarDatos();
// Solicitar al usuario el ID del territorio desde el cual desea atacar
int idTerritorioDesde;
cout << "Ingrese el ID del territorio desde el cual desea atacar: ";
cin >> idTerritorioDesde;

// Encontrar el territorioDesde en la lista de territorios del jugador
Territorio* territorioDesde = nullptr;
for (Territorio* territorio : territorios) {
    if (territorio->getId() == idTerritorioDesde) {
        territorioDesde = territorio;
        break;
    }
}

if (!territorioDesde) {
    cout << "No posee el territorio desde el cual desea atacar.\n";
    return false;
}

// Solicitar al usuario el ID del territorio hacia el cual desea atacar
int idTerritorioHacia;
cout << "Ingrese el ID del territorio hacia el cual desea atacar: ";
cin >> idTerritorioHacia;

// Usando la función buscarAdyacente para obtener el territorioHacia
Territorio* territorioHacia = territorioDesde->buscarAdyacente(idTerritorioHacia);

if (!territorioHacia) {
    cout << "\nEl territorio a atacar no es adyacente o no existe.\n";
    return false;
}

if(territorioHacia->getPropietario() == this){
  cout << "\nYa es dueño del territorio que desea atacar.\n";
  return false;
}

  if(!territorioHacia->getPropietario()){

      system("clear");
    
      while(1){

          cout << "--Turno de "<<nombre<<"--"<<endl;

          if(territorioDesde->getUnidades() <= 1){
            cout << "(Unidades insuficientes) No tiene suficientes unidades para mover al territorio inhabitado\n";
            return false;
          }
          int unidadesMover;
          cout <<"\n*Cuantas unidades desea mover?: ";
          cin >> unidadesMover;

          if(unidadesMover < 1){
            cout <<"\n(Unidades invalidas) Solo puede mover 1 unidad o más\n";
            cout << "\n\n---<Presione enter para continuar>---" << endl;

            getchar();
            getchar();
            system("clear");
            continue;
          }

          else if(unidadesMover < territorioDesde->getUnidades()){
            territorioDesde->setUnidades(territorioDesde->getUnidades() - unidadesMover);
            territorioHacia->setUnidades(unidadesMover);
            territorioHacia->setPropietario(this);    
            this->agregarTerritorio(territorioHacia);
            return true;  
          }
          else{
              cout <<"\n(Unidades insuficientes) No tiene suficientes unidades para mover al territorio inhabitado\n";
            cout << "\n\n---<Presione enter para continuar>---" << endl;

            getchar();
            getchar();
            system("clear");
          }
      }
  }

  string seguirAtacando;
  
  do {

      system("clear");

      cout << "--Turno de "<<nombre<<"--\n"<<endl;
    
      list<int> dadosAtaque = tirarDados(3);
      list<int> dadosDefensa = territorioHacia->getPropietario()->tirarDados(2);

      dadosAtaque.sort(greater<int>());  // Ordenar los dados de ataque de mayor a menor
      dadosDefensa.sort(greater<int>());  // Ordenar los dados de defensa de mayor a menor

      cout << "\nDados Ataque: ";
      for(int x : dadosAtaque){
        cout << x << "  ";
      }
    
      cout << "\nDados Defensa: ";
      for(int x : dadosDefensa){
        cout << x << "  ";
      }



      for(auto itAtaque = dadosAtaque.begin(), itDefensa = dadosDefensa.begin(); itAtaque != dadosAtaque.end() && itDefensa != dadosDefensa.end(); ++itAtaque, ++itDefensa) {
          if(territorioDesde->getUnidades() == 0 || territorioHacia->getUnidades() == 0){
              break;
          }
          if (*itAtaque > *itDefensa) {
              territorioHacia->setUnidades(territorioHacia->getUnidades() - 1);
          } else {
              territorioDesde->setUnidades(territorioDesde->getUnidades() - 1);
          }
      }

      if(territorioDesde->getUnidades() == 0){
        cout <<"\n\n**Perdiste el Territorio**\n\n";
        territorioDesde->setPropietario(nullptr);
        this->removerTerritorio(territorioDesde);
        return false;
      }

      else if(territorioHacia->getUnidades() == 0) {

          if(territorioDesde->getUnidades() == 1){
            cout << "(Unidades insuficientes) Ganó el territorio, pero no tiene suficientes unidades para mover\n";
            territorioHacia->getPropietario()->removerTerritorio(territorioHacia);
            territorioHacia->setPropietario(nullptr);
            return false;
          }
        
          cout <<"\n**Ganaste el Territorio**\n";
        
          while(1){
              int unidadesMover;
              cout <<"\n*Cuantas unidades desea mover?: ";
              cin >> unidadesMover;

              if(unidadesMover < 1){
                cout <<"\n(Unidades invalidas) Solo puede mover 1 unidad o más\n";
                cout << "\n\n---<Presione enter para continuar>---" << endl;

                getchar();
                getchar();
                system("clear");
                continue;
              }

              if(unidadesMover < territorioDesde->getUnidades()){
                territorioDesde->setUnidades(territorioDesde->getUnidades() - unidadesMover);
                territorioHacia->getPropietario()->removerTerritorio(territorioHacia);
                territorioHacia->setUnidades(unidadesMover);
                territorioHacia->setPropietario(this);    
                this->agregarTerritorio(territorioHacia);
                return true;  
              }
              else{
                  cout <<"\n(Unidades insuficientes) No tiene suficientes unidades para mover\n";
              }
          }
      }

      cout << "\nDesea seguir atacando el territorio? (si/no) ";
      cin >> seguirAtacando;

      system("clear");


  } while(seguirAtacando == "si");

  return true;
  }


void Jugador::fortificar() {

    system("clear");

    cout << "--Turno de "<<nombre<<"--\n"<<endl;
  
    // Imprimir los territorios del jugador
    mostrarDatos();

    // Solicitar el territorio desde el cual mover las unidades
    int idTerritorioDesde;
    cout << "Ingresa el ID del territorio desde el cual deseas mover unidades: ";
    cin >> idTerritorioDesde;

    // Buscar el territorio
    Territorio* territorioDesde = nullptr;
  
    for(auto& territorio : territorios) {
        if(territorio->getId() == idTerritorioDesde) {
            territorioDesde = territorio;
            break;
        }
    }

    // Verificar que el territorio pertenezca al jugador
    if(!territorioDesde) {
      cout << "No posee el territorio desde el cual desea fortificar.\n";
      return;
    }

    // Solicitar el territorio adyacente al cual mover las unidades
    int idTerritorioHacia;
    cout << "Ingresa el ID del territorio adyacente al cual deseas mover unidades: ";
    cin >> idTerritorioHacia;

    // Obtener el territorio adyacente
    Territorio* territorioHacia = territorioDesde->buscarAdyacente(idTerritorioHacia);

    // Verificar que el territorio adyacente pertenezca al jugador y esté adyacente
  if (!territorioHacia) {
      cout << "\nEl territorio a fortificar no es adyacente o no existe.\n";
      return;
  }

  if(territorioHacia->getPropietario() != this){
    cout << "\nNo es dueño del territorio.\n";
    return;
  }

    // Solicitar la cantidad de unidades a mover
    int unidadesMover;
    cout << "Cantidad de unidades a mover (tienes " << territorioDesde->getUnidades() - 1 << " unidades disponibles): ";
    cin >> unidadesMover;

    // Verificar que la cantidad de unidades sea válida
    if(unidadesMover >= territorioDesde->getUnidades() || unidadesMover < 1) {
        cout << "Cantidad de unidades no válida.\n";
        return;
    }

    // Mover las unidades
    territorioDesde->setUnidades(territorioDesde->getUnidades() - unidadesMover);
    territorioHacia->setUnidades(territorioHacia->getUnidades() + unidadesMover);

    cout << "(Fortificación exitosa) Has fortificado con éxito." << endl;
}


  

string Jugador::getNombre() {
    return this->nombre;
}

void Jugador::setNombre(string nombre) {
    this->nombre = nombre;
}

string Jugador::getColor() {
    return this->color;
}

void Jugador::setColor(string color) {
    this->color = color;
}

int Jugador::getId() {
    return this->id;
}

void Jugador::setId(int id) {
    this->id = id;
}

list<Territorio*> Jugador::getTerritorios() {
    return this->territorios;
}

void Jugador::setTerritorios(list<Territorio*> territorios) {
    this->territorios = territorios;
}

list<Carta> Jugador::getCartas() {
    return this->cartas;
}

void Jugador::setCartas(list<Carta> cartas) {
    this->cartas = cartas;
}

