#include "Tablero.h"

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

    Tablero::Tablero(){
      this->continentes = list<Continente>();
      this->jugadores = list<Jugador>();
      this->mazo = list<Carta>();
      this->territorios = list<Territorio>();
      this->juegoInicializado = false;
      this->idJugadorEnTurno = 0;
    }

//-----------------Getters y setters-----------------------

    list<Continente> Tablero::getContinentes() {
        return continentes;
    }

    list<Jugador> Tablero::getJugadores() {
        return jugadores;
    }

    list<Carta> Tablero::getMazo() {
        return mazo;
    }

    list<Territorio> Tablero::getTerritorios() {
        return territorios;
    }

    void Tablero::setContinentes(list<Continente> continentes) {
        this->continentes = continentes;
    }

    void Tablero::setJugadores(list<Jugador> jugadores) {
        this->jugadores = jugadores;
    }

    void Tablero::setMazo(list<Carta> mazo) {
        this->mazo = mazo;
    }

    void Tablero::setTerritorios(list<Territorio> territorios) {
        this->territorios = territorios;
    }


    void Tablero::agregarContinente(Continente continente) {
        continentes.push_back(continente);
    }

    void Tablero::agregarJugador(Jugador jugador) {
        jugadores.push_back(jugador);
    }

    void Tablero::agregarCarta(Carta carta) {
        mazo.push_back(carta);
    }

    void Tablero::agregarTerritorio(Territorio territorio) {
        territorios.push_back(territorio);
    }

//-----------------Función para asignar color-----------------------

string Tablero::obtenerColor(int idJugador) {
  
    string colores[] = {"Azul", "Rojo", "Verde", "Blanco", "Violeta", "Negro"};

    return colores[idJugador];
}

//-----------------Inicializa el juego desde cero------------------------------------

bool Tablero::inicializar() {

    if (juegoInicializado) {
        cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
        return false;
    }

    int numJugadores;
    while(1){
      cout << "Ingrese la cantidad de jugadores (3 - 6): ";
      cin >> numJugadores;
      if(numJugadores < 7 && numJugadores > 2){
        break;
      }
    }

    // Crear jugadores
    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Ingrese el nombre del jugador " << i << ": ";
        cin >> nombre;

        string color = obtenerColor(i);  
      
        jugadores.push_back(Jugador(i, nombre, color));
    }

    system("clear");

    repartirTerritorios();

    juegoInicializado = true;
    return true;
}


//-----------------Retorna un string con el estado del juego-----------------------

string Tablero::estadoJuego(){

    string texto;
    texto += to_string(jugadores.size()) + "\n";  

    for(auto& jugador : jugadores){  
        texto += jugador.getNombre() + ";";  
        texto += jugador.getColor() + ";";  

        auto territoriosJugador = jugador.getTerritorios();

        texto += to_string(territoriosJugador.size()) + ";";

        for(auto territorio : territoriosJugador){  
            texto += to_string(territorio->getId()) + ";";  
            texto += to_string(territorio->getUnidades()) + ";";  
        }

        auto cartasJugador = jugador.getCartas();  

      if(cartasJugador.size() != 0){

        texto += to_string(cartasJugador.size()) + ";";

        for(auto it = cartasJugador.begin(); it != cartasJugador.end(); ++it){  
            texto += to_string(it->getId());
            if (next(it) != cartasJugador.end()) {  
                texto += ";";
            }
        }
        texto += "\n"; 
      }
      else{
        texto += to_string(cartasJugador.size()) + "\n";
      }
    }

    return texto;
}



//-----------------------Guarda en un archivo de texto-------------------------


bool Tablero::guardar(const string& nombreArchivo) {

    if(!juegoInicializado){
      cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente.";
      return false;
    }
  
    ofstream outFile(nombreArchivo);
  
    if (!outFile.is_open()){
      return false;
    }

    string estadoDelJuego = estadoJuego();

    if(estadoDelJuego.length() == 0){
      return false;
    }

    outFile << estadoDelJuego;

    outFile.close();
  
    return true;
}


//-----------------Guarda en un archivo binario---------------------------


bool Tablero::guardarComprimido(const string& nombreArchivo) {

    if(!juegoInicializado){
      cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente.";
      return false;
    }

    list<HuffmanNode*> nodos;

    string estadoDelJuego = estadoJuego();
  
    if(estadoDelJuego.empty()){
        return false;
    }

    // Crea la lista de nodos de Huffman (cada caracter con su frecuencia)
    for(char caracter : estadoDelJuego){
        bool esta = false;
        for(HuffmanNode* nodo : nodos){
            if(caracter == nodo->getCaracter()){
                nodo->setFrecuencia(nodo->getFrecuencia() + 1);
                esta = true;
                break;
            }
        }
        if(!esta){
            nodos.push_back(new HuffmanNode(caracter, 1));
        }   
    }


    // Construye el árbol de Huffman y obtener los códigos
    HuffmanTree arbol(nodos);
    list<CodigoHuffman> codigos = arbol.obtenerCodigos();

    string textoBinario = "";

    // Convierte el estado del juego a binario
    for(char caracter : estadoDelJuego){
        bool esta = false;
        for(const CodigoHuffman& codigo : codigos){
            if(codigo.caracter == caracter){
                textoBinario += codigo.codigo;
                esta = true;
                break;
            }
        }
        // Si un carácter no está en los códigos de Huffman (lo cual sería muy extraño), retorna falso
        if(!esta){
            return false;
        }
    }


  
    ofstream archivo(nombreArchivo, ios::binary);



    if (!archivo.is_open()){
      return false;
    }

    // Escribe la cantidad de caracteres diferentes (n) en el archivo
    int n = codigos.size();
    archivo.write(reinterpret_cast<const char*>(&n), sizeof(n));

    // Para cada código en la lista de códigos Huffman
    for (const auto& codigo : nodos) {
        // Escribe el carácter (ci) y su frecuencia (fi) en el archivo
        char ci = codigo->getCaracter();
        int fi = codigo->getFrecuencia();
        archivo.write(&ci, sizeof(ci));
        archivo.write(reinterpret_cast<const char*>(&fi), sizeof(fi));
    }

    // Escribe la longitud del archivo original (w) en el archivo
    int w = textoBinario.length();
    archivo.write(reinterpret_cast<const char*>(&w), sizeof(w));

    
    string textoBinarioArreglado = textoBinario;

    // Si textoBinario no es múltiplo de 8, añade ceros al final
    while (textoBinarioArreglado.length() % 8 != 0) {
        textoBinarioArreglado += '0';
    }

    // Escribe cada byte del código binario en el archivo por medio de operaciones de bits

    //    0000 0100   (byte)
    //  | 0000 0001   (1)
    //  ------------
    //    0000 0101   (resultado)

    for (int i = 0; i < textoBinarioArreglado.length(); i += 8) {
        char byte = 0;
        for (int j = 0; j < 8; j++) {
            byte <<= 1;
            if (textoBinarioArreglado[i + j] == '1') {
                byte |= 1;
            }
        }
        archivo.write(&byte, sizeof(byte));
    }

    archivo.close();
    return true;

    // Cierra el archivo
    archivo.close();
    return true;
}

//-----------------Inicializa el juego desde un archivo-----------------------------

bool Tablero::inicializar(const string& nombreArchivo){

    if(juegoInicializado){
      cout << "(Juego en curso) El juego ya ha sido inicializado." << endl;
      return false;
    }

    string tipo = nombreArchivo.substr(nombreArchivo.size() - 3, 3);

    string estadoJuego;

    if(tipo=="txt"){
      estadoJuego = lecturaArchivoTexto(nombreArchivo);
    }
    else if(tipo=="bin"){
      estadoJuego = lecturaArchivoBinario(nombreArchivo);
    }

    if(estadoJuego.size() == 0){
      return false;
    }
    
istringstream archivo(estadoJuego);  // Convertir el string a un stream para facilitar lectura

string dato;

getline(archivo, dato);
int numJugadores = stoi(dato);

string saltoLinea;

for(int i = 0; i < numJugadores; i++){
    string nombre;
    string color;
    getline(archivo, nombre, ';');
    getline(archivo, color, ';');

    getline(archivo, dato, ';');
    int numTerritorios = stoi(dato);

    list<Territorio*> territoriosJugador;

    for(int j = 0; j < numTerritorios; j++){

        getline(archivo, dato, ';');
        int idTerritorio = stoi(dato);
        Territorio* territorio = buscarTerritorio(idTerritorio);
        territoriosJugador.push_back(territorio);

        getline(archivo, dato, ';');
        int numUnidades = stoi(dato);

        territorio->setUnidades(numUnidades);
    }

    list<Carta> cartasJugador;
  
    getline(archivo, dato);

    if(dato != "0"){

      istringstream cartas(dato);

      getline(cartas, dato, ';');
      
      int numCartas = stoi(dato);
  
      for(int j = 0; j < numCartas; j++){
          if (j < numCartas - 1) {
              getline(cartas, dato, ';');
          } else {
              getline(cartas, dato);  // Para la última carta, el delimitador es el salto de línea
          }
          int idCarta = stoi(dato);
          Carta* carta = buscarCarta(idCarta);  
          cartasJugador.push_back(*carta);
          mazo.remove(*carta);
      }
    }

    Jugador nuevoJugador = Jugador(i, nombre, color, territoriosJugador, cartasJugador);
    agregarJugador(nuevoJugador);

    // Ahora asignamos el propietario a los territorios
    for(auto &territorio : territoriosJugador){
        territorio->setPropietario(buscarJugador(i));
    }
}

juegoInicializado = true;
idJugadorEnTurno = 0;
cartasIntercambiadas = 1;

return true;

}

//-----------------Retorna un string con el contenido del archivo de texto------------

string Tablero::lecturaArchivoTexto(const string& nombreArchivo){

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()){
      cout <<"no abre";
      return "";
    }

    string estadoJuego;
    string lineaLeida;

    while(getline(archivo, lineaLeida)){
      estadoJuego += lineaLeida;
      estadoJuego += "\n";
    }
  

  archivo.close();
  
  return estadoJuego;
}  


//-----------------Retorna un string con el contenido del archivo binario--------------

string Tablero::lecturaArchivoBinario(const string& nombreArchivo){


    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) return ""; // Retorna un string vacío si no se puede abrir el archivo

    int n; 
    archivo.read(reinterpret_cast<char*>(&n), sizeof(n));

    list<HuffmanNode*> frecuencias;
  
    for (int i = 0; i < n; ++i) {
        char ci;
        int fi; 
        archivo.read(&ci, sizeof(ci));
        archivo.read(reinterpret_cast<char*>(&fi), sizeof(fi));
        frecuencias.push_back(new HuffmanNode(ci, fi));
    }

    HuffmanTree arbol(frecuencias);

    int w; 
  
    archivo.read(reinterpret_cast<char*>(&w), sizeof(w));

    string textoBinario;
  
    char byte;

    // (byte & (1 << i)) verifica si el bit en la posición i del byte byte es igual a 1
    // Posiciones de los bytes:
    // Bit 7  Bit 6  Bit 5  Bit 4  Bit 3  Bit 2  Bit 1  Bit 0
  
    while (archivo.read(&byte, sizeof(byte))) {
        for (int i = 7; i >= 0; i--) {
            if (byte & (1 << i)) {
                 textoBinario += '1';
            }else{
                 textoBinario += '0';
                }
            }   
      }
    archivo.close();

    return arbol.decodificar(textoBinario, w); 
}

//-------Retorna un puntero al Jugador, Carta, Territorio o Continente por medio del ID-----------------

Jugador* Tablero::buscarJugador(int id_jugador) {
    for (Jugador& jugador : jugadores) {
        if (jugador.getId() == id_jugador) {
            return &jugador; 
        }
    }
    return nullptr;  
}


Carta* Tablero::buscarCarta(int id_carta) {
    for (Carta& carta : mazo) {
        if (carta.getId() == id_carta) {
            return &carta;  
        }
    }
    return nullptr;  
}

Territorio* Tablero::buscarTerritorio(int id_territorio){
  for (Territorio& territorio : territorios) {
        if (territorio.getId() == id_territorio) {
            return &territorio;  
        }
    }
    return nullptr;  
}

Continente* Tablero::buscarContinente(int id_continente){
    for (Continente& continente : continentes) {
          if (continente.getId() == id_continente) {
              return &continente;  
          }
      }
      return nullptr;  
  }

//-----------------Retorna true si ya hubo un ganador---------------------------

bool Tablero::hayGanador() {
  
    int jugadoresVivos = 0;
  
    for (auto& jugador : jugadores) {
        if (jugador.sigueVivo()) {
            jugadoresVivos++;
        }
    }

    if (jugadoresVivos == 1) {
        return true;
    }

    return false;
}

//-----------------Reparte los territorios al inicio de la partida----------------

void Tablero::repartirTerritorios() {

    int numJugadores = jugadores.size();
    int infanteriasPorJugador;

    // Cantidad de infanterías por jugador
    switch(numJugadores) {
        case 3:
            infanteriasPorJugador = 35;
            break;
        case 4:
            infanteriasPorJugador = 30;
            break;
        case 5:
            infanteriasPorJugador = 25;
            break;
        case 6:
            infanteriasPorJugador = 20;
            break;
    }


    int territoriosOcupados = 0;
    int unidadesRestantes[jugadores.size()];

    for(int i = 0; i < jugadores.size(); i++){
        unidadesRestantes[i] = infanteriasPorJugador;
    }


    while (territoriosOcupados < territorios.size()) {
        for (int i = 0; i < numJugadores; i++) {
          if(territoriosOcupados >= territorios.size()){
            break;
          }
            if (unidadesRestantes[i] > 0) {
                Jugador* jugador = buscarJugador(i);  
                cout << "Repartición de territorios - Escoja su territorio\n\n";


                int maxIdWidth = 0;
                int maxNombreWidth = 0;

                for (Territorio &territorio : territorios) {
                    maxIdWidth = max(maxIdWidth, static_cast<int>(to_string(territorio.getId()).length()));
                    maxNombreWidth = max(maxNombreWidth, static_cast<int>(territorio.getNombre().length()));
                }

                // Cabecera de la tabla
                cout << left << setw(maxIdWidth + 2) << "ID";
                cout << setw(maxNombreWidth + 2) << "Nombre" <<endl;

                // Línea separadora
                cout << setfill('-');
                cout << setw(maxIdWidth + 2) << "" << setw(maxNombreWidth + 2) << "" << endl;
                cout << setfill(' ');

                // Datos de los territorios
                for (Territorio &territorio : territorios) {
                    if(!territorio.getPropietario()){
                    cout << left << setw(maxIdWidth + 2) << territorio.getId();
                    cout << setw(maxNombreWidth + 2) << territorio.getNombre() <<endl;
                    }
                }

                  cout << endl;
      
              
                cout << "--Turno de " << jugador->getNombre() <<"--"<<endl;

                int idTerritorio;
                cout << "\nID del territorio: ";
                cin >> idTerritorio;       
                Territorio* territorio = buscarTerritorio(idTerritorio);  

                if(territorio){
                  if (!territorio->getPropietario()) {  
                      territorio->setPropietario(jugador);  
                      territorio->setUnidades(1);
                      jugador->agregarTerritorio(territorio);  
                      territoriosOcupados++;
                      unidadesRestantes[i]--;
                      cout << "\nTerritorio asignado";
                  }
                  else{
                    cout << "\n(Error) El territorio ya tiene dueño\n";
                    i--;
                  }
                }
                else{
                  cout << "\n(Error) El territorio no existe\n";
                  i--;
                }
            }
          cout << "\n\n---<Presione enter para continuar>---" << endl;

          getchar();
          getchar();
          system("clear");
        }
          
    }


    bool infanteriasUbicadas = false;
    for(int i = 0; i < jugadores.size(); i++){
        if(unidadesRestantes[i] > 0){
            infanteriasUbicadas = false;
            break;
        }
    }

  
    if(!infanteriasUbicadas){
      system("clear");
      for(int i = 0; i < jugadores.size(); i++){
        buscarJugador(i)->asignarUnidades(unidadesRestantes[i]);
          }
      }
}

//-----------------Operaciones realizadas en cada turno--------------------------

void Tablero::turno(int id_jugador) {
    // Verificar si el juego ha sido inicializado correctamente

    system("clear");
  
    if (!juegoInicializado) {
        cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
        return;
    }

    // Verificar si ya hay un ganador
    if (hayGanador()) {
        cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
        return;
    }

    // Verificar si el id_jugador es válido
    Jugador* jugador = buscarJugador(id_jugador);
  
    if (!jugador) {
        cout << "(Jugador no válido) El jugador " << id_jugador << " no forma parte de esta partida." << endl;
        return;
    }

    // Verificar si es el turno del jugador
    if (id_jugador != idJugadorEnTurno) {
        cout << "(Jugador fuera de turno) No es el turno del jugador " << id_jugador << "." << endl;
        return;
    }

    if(!jugador->sigueVivo()){
      cout << "(Jugador muerto) El jugador " << jugador->getNombre() << " ya perdió." << endl;
      return;
    }

    cout << "--Turno de "<<jugador->getNombre()<<"--\n"<<endl;

    // Paso 1: Obtener y ubicar nuevas unidades
    int nuevasUnidades = 0;
    string respuesta;

    cout << "Desea cambiar cartas por unidades? (si/no): ";
    cin >> respuesta;


    if(respuesta == "si"){
      nuevasUnidades += jugador->cambiarCartas(cartasIntercambiadas, mazo);
      cout << "Unidades obtenidas por cartas: " << nuevasUnidades << endl;
    }

    int unidadesTerritorios = jugador->obtenerUnidadesPorTerritorios();
    int unidadesContinentes = obtenerUnidadesPorContinentes(jugador);


    

  
    cout << "Unidades obtenidas por territorios: " << unidadesTerritorios << endl;
    cout << "Unidades obtenidas por continentes: " << unidadesContinentes << endl;
  
    nuevasUnidades += unidadesTerritorios + unidadesContinentes;

    cout << "\n\n---<Presione enter para continuar>---" << endl;

      getchar();
      getchar();
      system("clear");
    
    
  
    jugador->asignarUnidades(nuevasUnidades);

    srand(time(0));

    cout << "--Turno de "<<jugador->getNombre()<<"--\n"<<endl;

    // Paso 2: Atacar
    cout << "¿Deseas atacar? (si/no): ";
    cin >> respuesta;
    while (respuesta == "si"){

      if(jugador->atacar()){
        
          if (!mazo.empty()) {
 
              Carta cartaGanada = mazo.front();
              mazo.pop_front();  

              jugador->agregarCarta(cartaGanada);

          } else {
              cout << "(Mazo vacío) No hay más cartas disponibles para entregar." << endl;
          }
      }
      cout << "\n¿Deseas atacar de nuevo? (si/no): ";
      cin >> respuesta;
      system("clear");
    }
    system("clear");
    // Paso 3: Fortificar

    cout << "--Turno de "<<jugador->getNombre()<<"--\n"<<endl;

    cout << "¿Deseas fortificar? (si/no): ";
    cin >> respuesta;

    while (respuesta == "si"){
        jugador->fortificar();
        cout << "\n¿Deseas fortificar de nuevo? (si/no): ";
        cin >> respuesta;
        system("clear");
     }
    system("clear");
    cout << "(Turno terminado correctamente) El turno del jugador " << id_jugador << " ha terminado." << endl;

  
    // Paso 4: Cambiar turno
    if(idJugadorEnTurno == jugadores.size() - 1){
      idJugadorEnTurno = 0;
    }
    else{
      idJugadorEnTurno++;
    }
}

//-----------------Retorna las unidades obtenidas por los continentes-----------------

int Tablero::obtenerUnidadesPorContinentes(Jugador* jugador) {
    int unidades = 0;
    for (auto& continente : continentes) {
        if (continente.esDueno(jugador)) {
            unidades += continente.getUnidadesRey();
        }
    }
    return unidades;
}

//-----------------Función para reconstruir el camino más corto desde un Territorio inicial hasta un Territorio final----------------

list<int> ReconstruirCamino(vector<vector<int>> predecesores, int u, int v) {

        list<int> camino;
        if (predecesores[u][v] == -1) {
            return camino; // No hay camino
        }
        while (u != v) {
            camino.push_front(v);
            v = predecesores[u][v];
        }
        camino.push_front(u);
        return camino;

}

//-----------------Insertar arcos Grafo-----------------


void Tablero::insertarArcosGrafo() { 

  grafo.EliminarTodosLosArcos();

  for (Territorio& origen : territorios) {
      for (Territorio* destino : origen.getTerritoriosAdyacentes()) {
          // Si el territorio de destino no tiene propietario, el costo es 0
          if(!destino->getPropietario()){
            grafo.InsArco(origen.getId() - 1, destino->getId() - 1, 0);
          }
          // Si el destino es el mísmo territorio, el costo es 0
          else if(destino->getId() == origen.getId()){
            grafo.InsArco(origen.getId() - 1, destino->getId() - 1, 0);
          }  
          // Verifica si el territorio destino pertenece al jugador en turno
          else if (destino->getPropietario() != buscarJugador(idJugadorEnTurno)) {
              int costo = destino->getUnidades();
              grafo.InsArco(origen.getId() - 1, destino->getId() - 1, costo);
          }
      }
  }

  int n = grafo.OrdenGrafo(); 

  for (int i = 0; i < n; ++i) {
      string nombreOrigen = grafo.InfoVertice(i)->getNombre();

      for (int j = 0; j < n; ++j) {
          if (i != j) { 
              string nombreDestino = grafo.InfoVertice(j)->getNombre();
              string propietarioDestino = grafo.InfoVertice(j)->getPropietario()->getNombre();
              int costo = grafo.CostoArco(i, j);

             
              if (costo != -1) {
                  std::cout << "Costo de " << nombreOrigen << " a " << nombreDestino << ": " << costo << std::endl;
              }
          }
      }
  }
  
}


// -----------------Algoritmo FloydWarshal para encontrar el camino mas corto entre dos Territorios del tablero-----------------

void Tablero::FloydWarshall(vector<vector<int>> &distancias, vector<vector<int>> &predecesores, const int INFINITO) {

  
        const int n = grafo.OrdenGrafo();

        distancias = vector<vector<int>>(n, vector<int>(n, INFINITO));
        predecesores = vector<vector<int>>(n, vector<int>(n, -1));
          

        // Configurar las distancias iniciales y los predecesores
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    distancias[i][j] = 0;
                    predecesores[i][j] = i;
                } else {
                    int costo = grafo.CostoArco(i, j);
                    if (costo != -1) {
                        distancias[i][j] = costo;
                        predecesores[i][j] = i;
                    }
                }
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (distancias[i][k] != INFINITO && distancias[k][j] != INFINITO && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                        predecesores[i][j] = predecesores[k][j];
                    }
                }
            }
        }
    }


//-----------------Costo para conquistar un territorio desde el más cercano------------------------------------

void Tablero::costoConquista(int idTerritorio) {

    if (!juegoInicializado) {
        cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
        return;
    }

    // Verificar si ya hay un ganador
    if (hayGanador()) {
        cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
        return;
    }

    if (buscarTerritorio(idTerritorio)->getPropietario()->getId() == idJugadorEnTurno) {
        cout << "(Territorio inválido) Ya es dueño del territorio." <<endl;
        return;
    }

  
    idTerritorio -= 1; // Ya que los IDs de territorios son base 1

    insertarArcosGrafo();

    int n = grafo.OrdenGrafo();

    const int INFINITO = 999999;
    vector<vector<int>> distancias;
    vector<vector<int>> predecesores;

    FloydWarshall(distancias, predecesores, INFINITO);

    cout << "Matriz de Distancias:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distancias[i][j] == INFINITO)
                cout << "INF ";
            else
                cout << distancias[i][j] << " ";
        }
        cout << endl;
    }

    // Imprimir la matriz de predecesores
    cout << "\nMatriz de Predecesores:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << predecesores[i][j] << " ";
        }
        cout << endl;
    }



    // Encuentra el territorio controlado más cercano al territorio objetivo en términos de número de territorios a atravesar. Si es igual, busca el camino que sea más barato de conquistar.
    int minLongitudCamino = 999999;
    int territorioOrigen = -1;

  for (int i = 0; i < n; i++) {
      Jugador* propietario = grafo.InfoVertice(i)->getPropietario();
      if (propietario && propietario->getId() == idJugadorEnTurno) {
          list<int> camino = ReconstruirCamino(predecesores, i, idTerritorio);
          if (!camino.empty() && (camino.size() < minLongitudCamino || (camino.size() <= minLongitudCamino && distancias[i][idTerritorio] < distancias[territorioOrigen][idTerritorio]))) {
              minLongitudCamino = camino.size();
              territorioOrigen = i;
          }
      }
  }

    list<int> camino = ReconstruirCamino(predecesores, territorioOrigen, idTerritorio);
    int costoTotal = distancias[territorioOrigen][idTerritorio];

    buscarJugador(idJugadorEnTurno)->mostrarDatos();

    auto it = camino.begin();

    cout << "Para conquistar el territorio " << buscarTerritorio(idTerritorio + 1)->getNombre() << " debe atacar desde "<< buscarTerritorio(*it + 1)->getNombre();

  if(camino.size() > 2){
    cout << ", pasando por los territorios ";
    for (auto it = next(camino.begin()); it != prev(camino.end()); ++it) {
        cout << grafo.InfoVertice(*it)->getNombre();
        if (next(it) != prev(camino.end())) {
            cout << ", ";
        }
    }
  }
    cout <<". Debe conquistar " << costoTotal << " unidades de ejercito"<<endl;
    cout << endl;
}


//-----------------Territorio menos costoso para conquistar------------------------------------

void Tablero::conquistaMasBarata(){

  if (!juegoInicializado) {
    cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
    return;
  }

  // Verificar si ya hay un ganador
  if (hayGanador()) {
    cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    return;
  }

  insertarArcosGrafo();

  int n = grafo.OrdenGrafo();

  const int INFINITO = 999999;
  vector<vector<int>> distancias;
  vector<vector<int>> predecesores;

  FloydWarshall(distancias, predecesores, INFINITO);

  int minCostoCamino = 999999;
  int territorioOrigen;
  int territorioDestino;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      Jugador* propietario = grafo.InfoVertice(i)->getPropietario();
      if (propietario && propietario->getId() == idJugadorEnTurno && i != j) {
          int costo = distancias[i][j];
          if (costo < minCostoCamino && grafo.InfoVertice(j)->getPropietario()->getId() != idJugadorEnTurno) {
              minCostoCamino = costo;
              territorioOrigen = i;
              territorioDestino = j;
        }
      }
    }
  }

    list<int> camino = ReconstruirCamino(predecesores, territorioOrigen, territorioDestino);

    buscarJugador(idJugadorEnTurno)->mostrarDatos();

    auto it = camino.begin();

  string nombreTerritorioOrigen = grafo.InfoVertice(territorioOrigen)->getNombre();
  string nombreTerritorioDestino = grafo.InfoVertice(territorioDestino)->getNombre();

  cout << "La conquista más barata es avanzar sobre el territorio " << nombreTerritorioDestino 
       << " desde el territorio " << nombreTerritorioOrigen << ". Para conquistar el territorio " 
       << nombreTerritorioDestino << ", debe atacar desde " << nombreTerritorioOrigen;

  if(camino.size() > 2){
    cout << ", pasando por los territorios ";
    for (auto it = next(camino.begin()); it != prev(camino.end()); ++it) {
        cout << grafo.InfoVertice(*it)->getNombre();
        if (next(it) != prev(camino.end())) {
            cout << ", ";
      }
    }
  }

  cout << ". Debe conquistar " << minCostoCamino << " unidades de ejército." << endl;
  
}

//-----------------Llenado de datos------------------------------------

void Tablero::llenarTablero(){

  agregarContinente(Continente(1, "America del Norte", "Rojo", {}, 5));  
  agregarContinente(Continente(2, "America del Sur", "Azul",{}, 2)); 
  agregarContinente(Continente(3, "Europa", "Naranja",{}, 5));  
  agregarContinente(Continente(4, "Africa", "Verde",{}, 3));  
  agregarContinente(Continente(5, "Asia", "Amarillo",{}, 7));  
  agregarContinente(Continente(6, "Australia", "Negro",{}, 2)); 

    agregarTerritorio(Territorio(1, "Alaska", buscarContinente(1), {}));
    agregarTerritorio(Territorio(2, "Alberta", buscarContinente(1), {}));
    agregarTerritorio(Territorio(3, "Estados Unidos Occidentales", buscarContinente(1), {}));
    agregarTerritorio(Territorio(4, "Estados Unidos Orientales", buscarContinente(1), {}));
    agregarTerritorio(Territorio(5, "Groenlandia", buscarContinente(1), {}));
    agregarTerritorio(Territorio(6, "Ontario", buscarContinente(1), {}));
    agregarTerritorio(Territorio(7, "Quebec", buscarContinente(1), {}));
    agregarTerritorio(Territorio(8, "Territorio Noroccidental", buscarContinente(1), {}));
    agregarTerritorio(Territorio(9, "America Central", buscarContinente(1), {}));
    agregarTerritorio(Territorio(10, "Argentina", buscarContinente(2), {}));
    agregarTerritorio(Territorio(11, "Brasil", buscarContinente(2), {}));
    agregarTerritorio(Territorio(12, "Peru", buscarContinente(2), {}));
    agregarTerritorio(Territorio(13, "Venezuela", buscarContinente(2), {}));
    agregarTerritorio(Territorio(14, "Escandinavia", buscarContinente(3), {}));
    agregarTerritorio(Territorio(15, "Europa del Norte", buscarContinente(3), {}));
    agregarTerritorio(Territorio(16, "Europa del Sur", buscarContinente(3), {}));
    agregarTerritorio(Territorio(17, "Europa Occidental", buscarContinente(3), {}));
    agregarTerritorio(Territorio(18, "Gran Bretania", buscarContinente(3), {}));
    agregarTerritorio(Territorio(19, "Islandia", buscarContinente(3), {}));
    agregarTerritorio(Territorio(20, "Ucrania", buscarContinente(3), {}));
    agregarTerritorio(Territorio(21, "Africa del Norte", buscarContinente(4), {}));
    agregarTerritorio(Territorio(22, "Africa del Sur", buscarContinente(4), {}));
    agregarTerritorio(Territorio(23, "Africa Oriental", buscarContinente(4), {}));
    agregarTerritorio(Territorio(24, "Congo", buscarContinente(4), {}));
    agregarTerritorio(Territorio(25, "Egipto", buscarContinente(4), {}));
    agregarTerritorio(Territorio(26, "Madagascar", buscarContinente(4), {}));
    agregarTerritorio(Territorio(27, "Afghanistan",buscarContinente(5), {}));
    agregarTerritorio(Territorio(28, "China", buscarContinente(5), {}));
    agregarTerritorio(Territorio(29, "India", buscarContinente(5), {}));
    agregarTerritorio(Territorio(30, "Irkutush", buscarContinente(5), {}));
    agregarTerritorio(Territorio(31, "Japon", buscarContinente(5), {}));
    agregarTerritorio(Territorio(32, "Kamtchatca", buscarContinente(5), {}));
    agregarTerritorio(Territorio(33, "Medio Oriente", buscarContinente(5), {}));
    agregarTerritorio(Territorio(34, "Mongolia", buscarContinente(5), {}));
    agregarTerritorio(Territorio(35, "Siam", buscarContinente(5), {}));
    agregarTerritorio(Territorio(36, "Siberia", buscarContinente(5), {}));
    agregarTerritorio(Territorio(37, "Ural", buscarContinente(5), {}));
    agregarTerritorio(Territorio(38, "Yakustsk", buscarContinente(5), {}));
    agregarTerritorio(Territorio(39, "Australia Occidental", buscarContinente(6), {}));
    agregarTerritorio(Territorio(40, "Australia Oriental", buscarContinente(6), {}));
    agregarTerritorio(Territorio(41, "Indonesia", buscarContinente(6), {}));
    agregarTerritorio(Territorio(42, "Nueva Guinea", buscarContinente(6), {}));

  for (int i = 1; i <= 9; i++) {
  buscarContinente(1)->agregarTerritorio(buscarTerritorio(i));
  }
  for (int i = 10; i <= 13; i++) {
  buscarContinente(2)->agregarTerritorio(buscarTerritorio(i));
  }
  for (int i = 14; i <= 20; i++) {
  buscarContinente(3)->agregarTerritorio(buscarTerritorio(i));
  }
  for (int i = 21; i <= 26; i++) {
  buscarContinente(4)->agregarTerritorio(buscarTerritorio(i));
  }
  for (int i = 27; i <= 38; i++) {
  buscarContinente(5)->agregarTerritorio(buscarTerritorio(i));
  }
  for (int i = 39; i <= 42; i++) {
  buscarContinente(6)->agregarTerritorio(buscarTerritorio(i));
  }
  
  agregarCarta(Carta(1, "TR", buscarTerritorio(27), "Soldier"));
  agregarCarta(Carta(2, "TR", buscarTerritorio(1), "Canon"));
  agregarCarta(Carta(3, "TR", buscarTerritorio(2), "Canon"));
  agregarCarta(Carta(4, "TR", buscarTerritorio(10), "Soldier"));
  agregarCarta(Carta(5, "TR", buscarTerritorio(11), "Soldier"));
  agregarCarta(Carta(6, "TR", buscarTerritorio(9), "Soldier"));
  agregarCarta(Carta(7, "TR", buscarTerritorio(28), "Canon"));
  agregarCarta(Carta(8, "TR", buscarTerritorio(24), "Canon"));
  agregarCarta(Carta(9, "TR", buscarTerritorio(23), "Soldier"));
  agregarCarta(Carta(10, "TR", buscarTerritorio(40), "Horse"));
  agregarCarta(Carta(11, "TR", buscarTerritorio(4), "Canon"));
  agregarCarta(Carta(12, "TR", buscarTerritorio(25), "Horse"));
  agregarCarta(Carta(13, "TR", buscarTerritorio(18), "Soldier"));
  agregarCarta(Carta(14, "TR", buscarTerritorio(5), "Horse"));
  agregarCarta(Carta(15, "TR", buscarTerritorio(19), "Horse"));
  agregarCarta(Carta(16, "TR", buscarTerritorio(29), "Horse"));
  agregarCarta(Carta(17, "TR", buscarTerritorio(41), "Soldier"));
  agregarCarta(Carta(18, "TR", buscarTerritorio(30), "Canon"));
  agregarCarta(Carta(19, "TR", buscarTerritorio(31), "Horse"));
  agregarCarta(Carta(20, "TR", buscarTerritorio(32), "Canon"));
  agregarCarta(Carta(21, "TR", buscarTerritorio(26), "Horse"));
  agregarCarta(Carta(22, "TR", buscarTerritorio(33), "Canon"));
  agregarCarta(Carta(23, "TR", buscarTerritorio(34), "Horse"));
  agregarCarta(Carta(24, "TR", buscarTerritorio(42), "Horse"));
  agregarCarta(Carta(25, "TR", buscarTerritorio(21), "Soldier"));
  agregarCarta(Carta(26, "TR", buscarTerritorio(15), "Horse"));
  agregarCarta(Carta(27, "TR", buscarTerritorio(8), "Horse"));
  agregarCarta(Carta(28, "TR", buscarTerritorio(6), "Canon"));
  agregarCarta(Carta(29, "TR", buscarTerritorio(12), "Horse"));
  agregarCarta(Carta(30, "TR", buscarTerritorio(7), "Canon"));
  agregarCarta(Carta(31, "TR", buscarTerritorio(14), "Soldier"));
  agregarCarta(Carta(32, "TR", buscarTerritorio(35), "Horse"));
  agregarCarta(Carta(33, "TR", buscarTerritorio(36), "Soldier"));
  agregarCarta(Carta(34, "TR", buscarTerritorio(22), "Canon"));
  agregarCarta(Carta(35, "TR", buscarTerritorio(16), "Soldier"));
  agregarCarta(Carta(36, "TR", buscarTerritorio(20), "Soldier"));
  agregarCarta(Carta(37, "TR", buscarTerritorio(37), "Soldier"));
  agregarCarta(Carta(38, "TR", buscarTerritorio(13), "Horse"));
  agregarCarta(Carta(39, "TR", buscarTerritorio(39), "Canon"));
  agregarCarta(Carta(40, "TR", buscarTerritorio(17), "Soldier"));
  agregarCarta(Carta(41, "TR", buscarTerritorio(3), "Canon"));
  agregarCarta(Carta(42, "TR", buscarTerritorio(38), "Canon"));
  agregarCarta(Carta(43, "CM", nullptr, "Las Tres"));
  agregarCarta(Carta(44, "CM", nullptr, "Las Tres"));

  buscarTerritorio(1)->setTerritoriosAdyacentes({buscarTerritorio(8), buscarTerritorio(2)});
  
  buscarTerritorio(2)->setTerritoriosAdyacentes({buscarTerritorio(8), buscarTerritorio(6), buscarTerritorio(3), buscarTerritorio(1)});
  
  buscarTerritorio(3)->setTerritoriosAdyacentes({buscarTerritorio(2), buscarTerritorio(6), buscarTerritorio(4), buscarTerritorio(9)});
  
  buscarTerritorio(4)->setTerritoriosAdyacentes({buscarTerritorio(3), buscarTerritorio(9), buscarTerritorio(6), buscarTerritorio(7)});
  
  buscarTerritorio(5)->setTerritoriosAdyacentes({buscarTerritorio(8), buscarTerritorio(6), buscarTerritorio(7), buscarTerritorio(19)});
  
  buscarTerritorio(6)->setTerritoriosAdyacentes({buscarTerritorio(2), buscarTerritorio(8), buscarTerritorio(7), buscarTerritorio(3), buscarTerritorio(4)});
  
  buscarTerritorio(7)->setTerritoriosAdyacentes({buscarTerritorio(6), buscarTerritorio(4), buscarTerritorio(5)});
  
  buscarTerritorio(8)->setTerritoriosAdyacentes({buscarTerritorio(1), buscarTerritorio(2), buscarTerritorio(6), buscarTerritorio(5)});
  
  buscarTerritorio(9)->setTerritoriosAdyacentes({buscarTerritorio(3), buscarTerritorio(4), buscarTerritorio(13)});
  
  buscarTerritorio(10)->setTerritoriosAdyacentes({buscarTerritorio(11), buscarTerritorio(12)});
  
  buscarTerritorio(11)->setTerritoriosAdyacentes({buscarTerritorio(10), buscarTerritorio(12), buscarTerritorio(13), buscarTerritorio(21)});
  
  buscarTerritorio(12)->setTerritoriosAdyacentes({buscarTerritorio(10), buscarTerritorio(11), buscarTerritorio(13)});
  
  buscarTerritorio(13)->setTerritoriosAdyacentes({buscarTerritorio(11), buscarTerritorio(12)});
  
  buscarTerritorio(14)->setTerritoriosAdyacentes({buscarTerritorio(19), buscarTerritorio(18), buscarTerritorio(15), buscarTerritorio(20)});
  
  buscarTerritorio(15)->setTerritoriosAdyacentes({buscarTerritorio(14), buscarTerritorio(18), buscarTerritorio(17), buscarTerritorio(16), buscarTerritorio(20)});
  
  buscarTerritorio(16)->setTerritoriosAdyacentes({buscarTerritorio(20), buscarTerritorio(17), buscarTerritorio(15), buscarTerritorio(21), buscarTerritorio(25)});
  
  buscarTerritorio(17)->setTerritoriosAdyacentes({buscarTerritorio(15), buscarTerritorio(16), buscarTerritorio(18), buscarTerritorio(21)});
  
  buscarTerritorio(18)->setTerritoriosAdyacentes({buscarTerritorio(17), buscarTerritorio(19), buscarTerritorio(14), buscarTerritorio(15)});
  
  buscarTerritorio(19)->setTerritoriosAdyacentes({buscarTerritorio(18), buscarTerritorio(14), buscarTerritorio(5)});

  buscarTerritorio(20)->setTerritoriosAdyacentes({buscarTerritorio(14), buscarTerritorio(15), buscarTerritorio(16), buscarTerritorio(27), buscarTerritorio(33), buscarTerritorio(37)});

  buscarTerritorio(21)->setTerritoriosAdyacentes({buscarTerritorio(17), buscarTerritorio(16), buscarTerritorio(11), buscarTerritorio(23), buscarTerritorio(24), buscarTerritorio(25)});

  buscarTerritorio(22)->setTerritoriosAdyacentes({buscarTerritorio(26), buscarTerritorio(24), buscarTerritorio(23)});

  buscarTerritorio(23)->setTerritoriosAdyacentes({buscarTerritorio(21), buscarTerritorio(22), buscarTerritorio(24), buscarTerritorio(25), buscarTerritorio(26)});

  buscarTerritorio(24)->setTerritoriosAdyacentes({buscarTerritorio(21), buscarTerritorio(22), buscarTerritorio(23)});

  buscarTerritorio(25)->setTerritoriosAdyacentes({buscarTerritorio(16), buscarTerritorio(21), buscarTerritorio(23), buscarTerritorio(33)});

  buscarTerritorio(26)->setTerritoriosAdyacentes({buscarTerritorio(22), buscarTerritorio(23)});

  buscarTerritorio(27)->setTerritoriosAdyacentes({buscarTerritorio(20), buscarTerritorio(28), buscarTerritorio(29), buscarTerritorio(33), buscarTerritorio(37)});

  buscarTerritorio(28)->setTerritoriosAdyacentes({buscarTerritorio(27), buscarTerritorio(29), buscarTerritorio(36), buscarTerritorio(37), buscarTerritorio(34), buscarTerritorio(35)});

  buscarTerritorio(29)->setTerritoriosAdyacentes({buscarTerritorio(27), buscarTerritorio(28), buscarTerritorio(33), buscarTerritorio(35)});

  buscarTerritorio(30)->setTerritoriosAdyacentes({buscarTerritorio(36), buscarTerritorio(38), buscarTerritorio(32), buscarTerritorio(34)});

  buscarTerritorio(31)->setTerritoriosAdyacentes({buscarTerritorio(32), buscarTerritorio(34)});

  buscarTerritorio(32)->setTerritoriosAdyacentes({buscarTerritorio(1), buscarTerritorio(30), buscarTerritorio(31), buscarTerritorio(34), buscarTerritorio(38)});

  buscarTerritorio(33)->setTerritoriosAdyacentes({buscarTerritorio(27), buscarTerritorio(29), buscarTerritorio(25), buscarTerritorio(16), buscarTerritorio(20)});

  buscarTerritorio(34)->setTerritoriosAdyacentes({buscarTerritorio(28), buscarTerritorio(30), buscarTerritorio(31), buscarTerritorio(32), buscarTerritorio(36), buscarTerritorio(38)});

  buscarTerritorio(35)->setTerritoriosAdyacentes({buscarTerritorio(28), buscarTerritorio(29), buscarTerritorio(41)});

  buscarTerritorio(36)->setTerritoriosAdyacentes({buscarTerritorio(27), buscarTerritorio(28), buscarTerritorio(30), buscarTerritorio(34), buscarTerritorio(37), buscarTerritorio(38)});

  buscarTerritorio(37)->setTerritoriosAdyacentes({buscarTerritorio(27), buscarTerritorio(28), buscarTerritorio(36), buscarTerritorio(20)});

  buscarTerritorio(38)->setTerritoriosAdyacentes({buscarTerritorio(30), buscarTerritorio(32), buscarTerritorio(36)});

  buscarTerritorio(39)->setTerritoriosAdyacentes({buscarTerritorio(40), buscarTerritorio(41), buscarTerritorio(42)});

  buscarTerritorio(40)->setTerritoriosAdyacentes({buscarTerritorio(39), buscarTerritorio(42)});

  buscarTerritorio(41)->setTerritoriosAdyacentes({buscarTerritorio(39), buscarTerritorio(35), buscarTerritorio(42)});

  buscarTerritorio(42)->setTerritoriosAdyacentes({buscarTerritorio(39), buscarTerritorio(40), buscarTerritorio(41)});


  for (Territorio &territorio : territorios) {
      grafo.InsVertice(&territorio);
  }
  
}
