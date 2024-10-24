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
    cout << "Ingrese el número de jugadores (entre 3 y 5): " << endl;
    cin >> numJugadores;

    // Validar que el número de jugadores esté entre 3 y 5
    while (numJugadores < 3 || numJugadores > 5) {
        cout << "Número inválido. Ingrese un número entre 3 y 5: " << endl;
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