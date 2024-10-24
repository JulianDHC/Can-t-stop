#include <iostream>
#include "juego.h"
using namespace std;


    int Jugadores;
    int PedirJugadores()
    {
        cout << "ingrese el numero de jugadores" << endl;
        cin >> Jugadores;

        while (Jugadores < 2 || Jugadores > 4)
        {
            cout << "Número inválido. Ingrese un número entre 3 y 5: " << endl;
            cin >> Jugadores;
        } 
        return Jugadores;
    } 


int main()
{
    juego j;
    j.StarGame();
    return 0;
}
