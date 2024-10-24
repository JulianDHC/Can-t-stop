#include <iostream>
#include "juego.h"
using namespace std;

<<<<<<< HEAD
=======
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
>>>>>>> d4b34206c3ed73674e52b032f6a708ff017fd853


int main()
{
    juego j;
    j.StarGame();
    return 0;
}