#include <iostream>
#include <map>
#include <string>
#include "Tablero.cpp"
//#include "juego.cpp"
using namespace std;

    int Jugadores;
    int PedirJugadores()
    {
        cout << "ingrese el numero de jugadores" << endl;
        cin >> Jugadores;

        while (Jugadores < 3 || Jugadores > 5)
        {
            cout << "Número inválido. Ingrese un número entre 3 y 5: " << endl;
            cin >> Jugadores;
        } 
        return Jugadores;
    } 


int main(){
    int Jugadores = PedirJugadores();
    tablero t(Jugadores);
    t.mostrar();
    return 0;
}
