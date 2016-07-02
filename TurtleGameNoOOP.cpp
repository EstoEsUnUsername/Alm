#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

class Tortuga{
private:
  bool cabeza = false;
  bool cuerpo = false;
  int patas = 0;
public:

  void agregarParte(int ndado){
    if(ndado == 2) this -> cabeza = true;
    else if(ndado == 5) this->cuerpo = true;
    else if(ndado == 1) this->patas = this->patas+1;
  }
  bool estaCompleta(){
    if(this->cabeza == true && this->cuerpo == true && this->patas == 4) return true;
    return false;
  }
  bool tieneCabeza(){
    if(this->cabeza == true)
      return true;
    else return false;
  }
  bool tieneCuerpo(){
    if(this->cuerpo == true) return true;
    else return false;
  }

  int getPatas(){
    return patas;
  }

  bool faltanPatas(){
    if(this->patas<5) return true;
    return false;
  }

  void reiniciarTortuga(){
    this->cabeza = false;
    this->cuerpo = false;
    this->patas = 0;
  }
};

class Jugador{
private:
  int idJugador;
  char nombre[50];

public:

  int numTortugas = 0;

  Tortuga tortuga;

  void asignarNombre(char* nombre) {
    strcpy(this->nombre, nombre);
  }

  void asignarTortuga(Tortuga turtle){
    this->tortuga = turtle;
  }

  char* obtenerNombre() {
    return nombre;
  }

  void asignarIdJugador(int id){
    this->idJugador = id;
  }
  int obtenerIdJugador(){
    return idJugador;
  }

  int lanzarDado(){

    int num = 1 + rand() % (6);
    cout << "Soy el jugador " << this->nombre << " y saque "
         << num << " al tirar los dados" << endl;
    return num;
  }

};

class Juego{
  private:
    int ronda;
    int nivelJuego;
    Jugador ganador;
    int numJugadores;
  public:
    Jugador jugadores[10];

    Jugador* obtenerJugadores(){
      return jugadores;
    }

    void asignarNumJugadores(int n) {
      this->numJugadores = n;
    }

    int obtenerNumJugadores() {
      return this->numJugadores;
    }

    bool verificarLanzamiento(int nJugador){
      //Retorno true si es que al jugador se le asign� una pieza, para que vuelva a tirar el dado
      int nDado = jugadores[nJugador].lanzarDado();
      if(nDado == 2 && !jugadores[nJugador].tortuga.tieneCabeza()){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "Obtuviste la cabeza!! " << endl;
        return true;
      }else if(nDado == 5 && jugadores[nJugador].tortuga.tieneCabeza() && !jugadores[nJugador].tortuga.tieneCuerpo()){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "Obtuviste el cuerpo!! " << endl;
        return true;
      }else if(nDado == 1 && jugadores[nJugador].tortuga.tieneCabeza() && jugadores[nJugador].tortuga.tieneCuerpo() && jugadores[nJugador].tortuga.getPatas() < 5){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "Obtuviste una pata!! " << endl;
        return true;
      }else return false;
    }

    void asignarRondas(int ronda) {
      this->ronda = ronda;
    }

    int obtenerRondas() {
      return this->ronda;
    }

    void asignarGanador(Jugador ganador){
      this->ganador = ganador;
    }

    Jugador obtenerGanador() {
      return ganador;
    }


};

void empezarJuego(int nivel, int n) {

  ofstream escribeFacil("nivel1.txt", ios::app);
  ofstream escribeMedio("nivel2.txt", ios::app);
  ofstream escribeDificl("nivel3.txt", ios::app);

  char name[50];
  Jugador jugador;
  Juego juego;

  juego.asignarNumJugadores(n);

  for(int i = 0; i < n; i++){
    cout<<"Jugador "<<i+1<<": "; cin>>name;
    jugador.asignarNombre(name);
    Tortuga turtle;
    jugador.asignarTortuga(turtle);
    jugador.asignarIdJugador(i+1);
    juego.jugadores[i] = jugador;//guardo cada jugador, su nombre y tortuga
    cout<<endl;
  }
  fflush(stdin); // Para que no capture este enter y pueda seguir la ejecucion normal

  bool ganador = false;
  int dado, k = 0, rondas = 0;

  while (ganador == false) {
      if(k == n){
          k = 0;
          rondas++;
      }
      system("cls");
      cout << "--------- RONDA [ " << rondas << " ] ----------" << endl;
      cout << "Turno de -" << juego.jugadores[k].obtenerNombre() << " - " << endl;
      cout << "Tengo " << juego.jugadores[k].numTortugas << " tortuga(s)" << endl;
      cout << "Tengo cabeza?: " << juego.jugadores[k].tortuga.tieneCabeza() << endl;
      cout << "Tengo cuerpo?: " << juego.jugadores[k].tortuga.tieneCuerpo() << endl;
      cout << "Tengo : " << juego.jugadores[k].tortuga.getPatas() << endl;
      cout << "Presione ENTER para lanzar los dados: " << endl;
      cin.get();
      if(!juego.verificarLanzamiento(k)){
          cout << "No obtuviste numero requerido" << endl << endl;
          k++; // Turno del siguiente jugador
          system("pause>null");
          continue;
      } else {
          if(juego.jugadores[k].tortuga.estaCompleta()){
              juego.jugadores[k].numTortugas++;
              juego.jugadores[k].tortuga.reiniciarTortuga();
              if(juego.jugadores[k].numTortugas == nivel) {
                cout << " Tienes "<< juego.jugadores[k].numTortugas <<" tortuga(s) !!" << endl;
                cout << "\t\tGANASTE!!!!!!!";
                juego.asignarGanador(juego.jugadores[k]);
                juego.asignarRondas(rondas);
                switch (nivel) {
                  case 1:
                    escribeFacil.write(reinterpret_cast <char*>(&juego), sizeof(Juego));
                    break;
                  case 2:
                    escribeMedio.write(reinterpret_cast <char*>(&juego), sizeof(Juego));
                    break;
                  case 3:
                    escribeDificl.write(reinterpret_cast <char*>(&juego), sizeof(Juego));
                    break;
                }


                ganador = true;
              }
          }
          system("pause>null");
      }

  }
}

void resultados() {

  int op;
  char nivel[20];
  system("cls");
  cout<<"\t\tMOSTRAR RESULTADOS";
  cout<<"\n\n1. Nivel facil";
  cout<<"\n2. Nivel intermedio";
  cout<<"\n3. Nivel dificil";
  cout<<"\n\nIngrese el nivel que desea: "; cin>>op;

  system("cls");

  switch (op) {
    case 1:
      strcpy(nivel, "nivel1.txt");
      break;
    case 2:
      strcpy(nivel, "nivel2.txt");
      break;
    case 3:
      strcpy(nivel, "nivel3.txt");
      break;
  }

  int j = 1;
  Juego juego;

  ifstream lee(nivel);

  lee.read(reinterpret_cast <char*> (&juego), sizeof(Juego));

  while(!lee.eof()) {
    cout << endl << "PARTIDA " << j << endl;
    cout << "  Numero de jugadores: " << juego.obtenerNumJugadores() << endl;
    cout << "  Rondas: " << juego.obtenerRondas() << endl;
    cout << "  Ganador: " << juego.obtenerGanador().obtenerNombre() << endl;
    cout << "  Jugadores: " << endl;
    cout << "    Nombre\t\tTortugas\t\tCabeza\t\tCuerpo\t\tPatas"<<endl;
    for(int i = 0; i < juego.obtenerNumJugadores(); i++) {
      cout << "    " << juego.jugadores[i].obtenerNombre();
      cout << "\t\t" << juego.jugadores[i].numTortugas;
      if(juego.jugadores[i].tortuga.tieneCabeza())
        cout << "\t\tSi";
      else
        cout << "\t\tNo";
      if(juego.jugadores[i].tortuga.tieneCuerpo())
        cout << "\t\tSi";
      else
        cout << "\t\tNo";
      cout << "\t\t" << juego.jugadores[i].tortuga.getPatas() << endl;
    }
    lee.read(reinterpret_cast <char*> (&juego), sizeof(Juego));
    j++;
  }

  lee.close();

  system("pause>null");
}

void juego(){
  int opcion, n, numeroDado, tiempo;
  system("cls");
  cout<<"\t\tJUEGO NUEVO";
  cout<<"\n\n1. Nivel facil";
  cout<<"\n2. Nivel intermedio";
  cout<<"\n3. Nivel dificil";
  cout<<"\n\nIngrese el nivel que desea: "; cin>>opcion;
  cout<<"\n\nIngrese numero de jugadores: "; cin >> n;
  cout<<endl;

  empezarJuego(opcion, n);
}

int main(int argc, char const *argv[]) {

  srand(time(NULL));

  int nJugadores;
  char nombreJugador[50];
  Jugador jugador;
  Tortuga tortuga;

  int opc;

  do{
    system("cls");
    cout << "\t\t*******JUEGO DE LA TORTUGA*******"<<endl;
    cout<<"\n\n1. Juego nuevo";
    cout<<"\n2. Ver resultados";
    cout<<"\n3. Salir";
    cout<<"\n\nSu opcion es: "; cin>>opc;

    switch(opc){
      case 1:juego();  cin.get(); break;
      case 2: resultados(); cin.get(); break;
      case 3: return 0;
    }
  }while(opc < 4);

  return 0;
}
