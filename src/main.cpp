#include "Tablero.h"
#include <iostream>

using namespace std;

string extraerParametro(const string& comando);

int main() {
  
    Tablero tablero = Tablero();

    tablero.llenarTablero();

  
    string comando;

    while (true) { // Loop infinito, la salida se controla con 'break'
        cout << "Ingrese un comando: ";
        getline(cin, comando); 
      
//----------------------------------INICIALIZAR-----------------------------------------

       
      
        if(comando == "inicializar"){
            if(tablero.inicializar()){
              cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." << endl;
            }
        }
//----------------------------------INICIALIZAR <ARCHIVO>-----------------------------------------
          
        else if (comando.substr(0,11) == "inicializar") {
          
            string nombreArchivo = extraerParametro(comando);
            
            if (!nombreArchivo.empty()) {
                if(tablero.inicializar(nombreArchivo)){
                  cout << "(Inicialización satisfactoria) El juego se ha inicializado correctamente." << endl;
                }
                else{
                  cout <<"(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente."<<endl;
                }
            } else {
                cout << "Nombre de archivo no proporcionado o formato incorrecto." << endl;
            }
        } 

//----------------------------------GUARDAR_COMPRIMIDO-----------------------------------------

          else if (comando.substr(0,18) == "guardar_comprimido") {

              string nombreArchivo = extraerParametro(comando);
              if (!nombreArchivo.empty()) {
                    if(tablero.guardarComprimido(nombreArchivo)){
                    cout << "(Comando correcto) La partida ha sido codificada y guardada correctamente."<<endl;
                  }
                  else{
                    cout <<"(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente."<<endl;
                  }
                  } 
                  else {
                      cout << "Nombre de archivo no proporcionado o formato incorrecto." << endl;
                  }
          }

//----------------------------------GUARDAR-----------------------------------------
          
        else if (comando.substr(0,7) == "guardar") {
            string nombreArchivo = extraerParametro(comando);
            if (!nombreArchivo.empty()) {
                if(tablero.guardar(nombreArchivo)){
                  cout << "(Comando correcto) La partida ha sido guardada correctamente."<<endl;
                }
                else{
                  cout <<"(Error al codificar y/o guardar) La partida no ha sido codificada ni guardada correctamente."<<endl;
                }
                } 
                else {
                cout << "Nombre de archivo no proporcionado o formato incorrecto." << endl;
            }
        } 
          
          
//----------------------------------COSTO_CONQUISTA-----------------------------------------
          
        else if(comando.substr(0,15) == "costo_conquista"){
            int idTerritorio = stoi(extraerParametro(comando));
            tablero.costoConquista(idTerritorio);
        }

//----------------------------------COSTO_CONQUISTA-----------------------------------------

        else if(comando == "conquista_mas_barata"){
            tablero.conquistaMasBarata();
        }


//----------------------------------TURNO-----------------------------------------

        else if(comando.substr(0,5) == "turno"){
            int turnoJugador = stoi(extraerParametro(comando));
            tablero.turno(turnoJugador);
        }
//------------------------------MOSTRAR_ESTADO------------------------------------

        else if(comando == "estado"){
          cout << tablero.estadoJuego();
        }

//----------------------------------SALIR-----------------------------------------
          
        else if (comando == "salir") {
            break; // Salir del bucle y terminar el programa
        } 

//----------------------------------COMANDO_INCORRECTO-----------------------------------------
          
        else {
            cout << "Comando no reconocido." << endl;
        }
    }

    return 0;
}


string extraerParametro(const string& comando) {
    size_t inicio = comando.find('<');
    size_t fin = comando.find('>');
    if (inicio != string::npos && fin != string::npos) {
        // Extrae el substring entre '<' y '>'
        return comando.substr(inicio + 1, fin - inicio - 1);
    }
    return "";
}






