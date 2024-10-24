#include <iostream>
#include <map>
#include <string>
#include "juego.h"
#include "Tablero.cpp"
#include "dado.cpp"
using namespace std;

class avances
{
     public:
     map<int,int>avances;
     int posicion = 3;
     
};
int juego::PedirJugadores() 
{
    cout << "Ingrese el número de jugadores (entre 2 y 4): " << endl;
    cin >> numJugadores;

    // Validar que el número de jugadores esté entre 2 y 4
    while (numJugadores < 2 || numJugadores > 4) {
        cout << "Número inválido. Ingrese un número entre 2 y 4: " << endl;
        cin >> numJugadores;
    }
    return numJugadores;
}
void juego::StarGame() 
{
    Tablero t;
    dado d;
    int TotalJugadores= PedirJugadores();
    cout<< 
    t.mostrar();
  
}
