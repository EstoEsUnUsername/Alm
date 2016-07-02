#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <stdio.h>
#include <fstream>

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
  string nombre;
  int cantidadTortugas = 0;
public:

  Tortuga tortuga;

  void asignarNombre(string nombre) {
    this->nombre = nombre;
  }

  void asignarTortuga(Tortuga turtle){
    this->tortuga = turtle;
  }

  string obtenerNombre() {
    return nombre;
  }

  void asignarIdJugador(int id){
    this->idJugador = id;
  }
  int obtenerIdJugador(){
    return idJugador;
  }

  void setCantidadTortugas(int cantidadTortugas){
    this->cantidadTortugas = this->cantidadTortugas + cantidadTortugas;
  }

  int getCantidadTortugas(){
    return cantidadTortugas;
  }

  int lanzarDado(){

    int num = 1 + rand() % (6);
    /*cout << "Soy el jugador " << this->nombre << " y saque "
         << num << " al tirar los dados" << endl;
         */
	cout<<"\tSAQUE "<<num<<" AL TIRAR LOS DADOS"<<endl;
    return num;
  }
};

class Juego{
  private:
    int ronda;
    int nivelJuego;
    Jugador ganador;

  public:
    vector<Jugador> jugadores;

    vector<Jugador> obtenerJugadores(){
      return jugadores;
    }

    void setNivelJuego(int nivelJuego){
        this->nivelJuego = nivelJuego;
    }

    void setRondas(int rondas){
        this->ronda = rondas;
    }

    int getRondas(){
        return ronda;
    }

    bool verificarLanzamiento(int nJugador){
      //Retorno true si es que al jugador se le asignï¿½ una pieza, para que vuelva a tirar el dado
      int nDado = jugadores[nJugador].lanzarDado();
      if(nDado == 2 && !jugadores[nJugador].tortuga.tieneCabeza()){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "\n\nObtuviste la cabeza para tu tortuga!! " << endl;
        return true;
      }else if(nDado == 5 && jugadores[nJugador].tortuga.tieneCabeza() && !jugadores[nJugador].tortuga.tieneCuerpo()){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "\n\nObtuviste el cuerpo para tu tortuga!! " << endl;
        return true;
      }else if(nDado == 1 && jugadores[nJugador].tortuga.tieneCabeza() && jugadores[nJugador].tortuga.tieneCuerpo() && jugadores[nJugador].tortuga.getPatas() < 5){
        jugadores[nJugador].tortuga.agregarParte(nDado);
        cout << "\n\nObtuviste una pata mas para tu tortuga!! " << endl;
        return true;
      }else return false;
    }

    void asignarGanador(Jugador ganador){
      this->ganador = ganador;
    }

    Jugador getGanador(){
        return ganador;
    }

    int getNivelJuego(){
        return nivelJuego;
    }

    void registrarPartida(char fila[], Juego juego){

       ofstream esc(fila,ios::app);
       if(!esc){  cout<<"\n ERROR al abrir "<<fila;getch();    }
       else{
          esc.write(reinterpret_cast<char *>(&juego),sizeof(Juego));
          esc.close();
       }

    }

    void visualizarPartida(char fila[]){
        int j = 1;
        Juego juego;
        ifstream lec(fila);
        if(!lec){        cout<<"\n ERROR al abrir "<<fila;getch();     }
        else {
          cout<<"\n MOSTRANDO DATOS DEL ARCHIVO "<<fila;
          lec.read(reinterpret_cast <char*>(&juego),sizeof(Juego));
            while(!lec.eof()) {
                cout << endl << "PARTIDA " << j << endl;
                cout << "  Numero de jugadores: " << juego.obtenerJugadores().size() << endl;
                cout << "  Rondas: " << juego.getRondas() << endl;
                cout << "  Ganador: " << juego.getGanador().obtenerNombre() << endl;
                cout << "  Jugadores: " << endl;
                cout << "    Nombre\t\tTortugas\t\tCabeza\t\tCuerpo\t\tPatas"<<endl;
                for(int i = 0; i < juego.obtenerJugadores().size(); i++) {
                  cout << "    " << juego.jugadores[i].obtenerNombre();
                  cout << "\t\t" << juego.jugadores[i].getCantidadTortugas();
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
                lec.read(reinterpret_cast <char*> (&juego), sizeof(Juego));
                j++;
              }
	      lec.close();
        }
    }

    void play () {
      int opcion, n, k = 0, cantTortugas = 1, rondas = 0, tiempo;
      string name = "";
      Jugador jugador;
      Juego juego;
      system("cls");
      cout<<"\t\tJUEGO NUEVO";
      cout<<"\n\n1. Nivel facil";
      cout<<"\n2. Nivel intermedio";
      cout<<"\n3. Nivel dificil";
      cout<<"\n\nIngresa el nivel que deseas: "; cin>>opcion;
      cout<<"\nIngresa el numero de jugadores: "; cin >> n;
      for(int i = 0; i < n; i++){
        cout<<"\nJugador "<<i+1<<": "; cin>>name;
        jugador.asignarNombre(name);
        Tortuga turtle;
        jugador.asignarTortuga(turtle);
        jugador.asignarIdJugador(i+1);
        juego.jugadores.push_back(jugador);//guardo cada jugador, su nombre y tortuga
      }
      cout<<endl;

      bool ganador = false;
      int dado;
      switch(opcion){
        case 1:
        case 2:
        case 3://acÃ¡ solo debe formar una tortuga

                //clock_t start = clock();
                juego.setNivelJuego(opcion);
                //cout << "ELEGISTE EL NIVEL: " << juego.getNivelJuego() << " !! " << endl;
                while (ganador == false) {
                    system("cls");
                    if(k == n){
                        k = 0;
                        rondas++;
                    }
                    cout << "--------- RONDA [ " << rondas << " ] ----------" << endl;
                    cout << "Turno de ---" << juego.jugadores[k].obtenerNombre() << "---" << endl;
                    cout << "Tienes " << juego.jugadores[k].getCantidadTortugas() << " tortugas " << endl;
                    cout << "Tu tortuga actual tiene cabeza?: " << juego.jugadores[k].tortuga.tieneCabeza() << endl;
                    cout << "Tu tortuga actual tiene cuerpo?: " << juego.jugadores[k].tortuga.tieneCuerpo() << endl;
                    cout << "Tu tortuga actual tiene " << juego.jugadores[k].tortuga.getPatas() << " patas" <<endl;
                    cout << "Presiona ENTER para lanzar los dados: " << endl;
                    getch();
                    if(!juego.verificarLanzamiento(k)){
                        cin.get();
                        cout << "\n\nNo obtuviste un numero valido";
                        k++; // Turno del siguiente jugador
                        continue;
                    } else {
                        cin.get();
                        if(juego.jugadores[k].tortuga.estaCompleta()){
                                juego.jugadores[k].setCantidadTortugas(cantTortugas); // Agregamos una tortuga
                                juego.jugadores[k].tortuga.reiniciarTortuga();
                                cin.get();
                                cout << "Ahora tienes " << juego.jugadores[k].getCantidadTortugas() << " tortugas " << endl;
                                cin.get();
                                if (juego.jugadores[k].getCantidadTortugas() == juego.getNivelJuego()) {
                                    cin.get();
                                    cout << "\n¡¡ GANASTE !!" << endl;
                                    juego.asignarGanador(juego.jugadores[k]);
                                    juego.setRondas(rondas);
                                    system("cls");
                                    cout << "EL GANADOR ES: " << juego.getGanador().obtenerNombre() << endl;
                                    ganador = true;
                                } else {
                                    cin.get();
                                    cout << "Te faltan " << juego.getNivelJuego() - juego.jugadores[k].getCantidadTortugas()
                                         << " para ganar !! " << endl;
                                }
                        }
                    }
                }
                //tiempo  = ((double)clock() - start) / CLOCKS_PER_SEC;
                registrarPartida("juego.txt", juego);
                break;

        case 4:
                return;
                break;
      }
    }
};

int main(int argc, char const *argv[]) {

  srand(time(NULL));
  Juego juego;
  int opc;

  do{
    system("cls");
    cout << "\t\t*******JUEGO DE LA TORTUGA*******"<<endl;
    cout<<"\n\n1. Juego nuevo";
    cout<<"\n2. Ver resultados";
    cout<<"\n3. Salir";
    cout<<"\n\nSu opcion es: "; cin>>opc;

    switch(opc){
      case 1:juego.play();  cin.get(); break;
      case 2:juego.visualizarPartida("juego.txt"); cin.get(); break;
      case 3: return 0;
    }
  }while(opc < 4);

  return 0;
}
