
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Jugadores
{
public:
    int num_jugadores;
    vector<string> nombres;

    int pedirJugadores()
    {
        do
        {
            cout << "Número de jugadores (2-4): ";
            cin >> num_jugadores;
            if (num_jugadores < 2 || num_jugadores > 4)
            {
                cout << "Error en la cantidad, reintente." << endl;
            }
        } while (num_jugadores < 2 || num_jugadores > 4);

        nombres.resize(num_jugadores);
        return num_jugadores;
    }

    void nombreJugadores()
    {
        for (int i = 0; i < num_jugadores; i++)
        {
            cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
            cin >> nombres[i];
            cout << endl;
        }
    }

    void mostrarNombres()
    {
        for (int i = 0; i < num_jugadores; i++)
        {
            cout << nombres[i] << endl;
        }
    }
};
