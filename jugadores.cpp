#include <iostream>
#include <map>
#include <string>
using namespace std;

class jugadores
{

public:
    int numJugadores;
    int PedirJugadores()
    {
        cout << "ingrese el numero de jugadores" << endl;
        cin >> numJugadores;

        while (numJugadores < 3 || numJugadores > 5)
        {
            cout << "Número inválido. Ingrese un número entre 3 y 5: " << endl;
            cin >> numJugadores;
        } 
        return numJugadores;
    }
   
};
