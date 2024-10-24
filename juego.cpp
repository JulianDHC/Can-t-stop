#include <iostream>
#include <map>
#include <string>
#include "Tablero.cpp"
#include "dado.cpp"
#include <vector>
using namespace std;

class avances
{
     public:
     map<int,int>avances;
     int posicion = 3;
     
};
class juego
{
     public:
     map<int, string> colores_jugadores = {
     {0, "\033[43m"},  // Amarillo
     {1, "\033[41m"},  // Rojo
     {2, "\033[44m"},  // Azul
     {3, "\033[42m"}   // Verde7
     };
     int numJugadores;
     int PedirJugadores()
     {
      cout << "Ingrese el número de jugadores (entre 2 y 4): " << endl;
      cin >> numJugadores;

      // Validar que el número de jugadores esté entre 2 y 4
      while (numJugadores < 2 || numJugadores > 4)
      {
          cout << "Número inválido. Ingrese un número entre 2 y 4: " << endl;
          cin >> numJugadores;
      }
      return numJugadores;
     }
     
     void StarGame()
    {
        Tablero t;
        dado d;
        int TotalJugadores = PedirJugadores();
        t.mostrar();
        bool gameOver = false;

        while (!gameOver)
        {
            for (int i = 0; i < numJugadores; i++)
            {
                cout << "Turno del jugador " << i + 1 << " (Color: " << colores_jugadores[i] << "\033[0m" ")";
                turno(t, d, TotalJugadores);
                t.mostrar();

                // Verificamos si alguien ha ganado (logrando 3 columnas completas)
                if (verificarVictoria(t))
                {
                    cout << "¡El jugador " << i + 1 << " ha ganado!";
                    gameOver = true;
                    break;
                }
            }
        }
    }

    void turno(Tablero &t, dado &d, int jugador)
    {
        bool continuar = true;
        vector<int> avances;

        while (continuar)
        {
            d = dado();  // Lanza los dados
            cout << "Dados lanzados: "<< endl;
            d.mostrar();
            cout << "\nElige dos pares de números de la tirada para avanzar en las columnas."<< endl;

     
            int columna1, columna2;
            cout << "Elige la primera columna (2 a 12): ";
            cin >> columna1;
            cout << "Elige la segunda columna (2 a 12): ";
            cin >> columna2;

            if (columna1 < 2 || columna1 > 12 || columna2 < 2 || columna2 > 12)
            {
                cout << "Columnas inválidas. Intenta de nuevo.";
                continue;
            }

            t.actualizarColumna(columna1, jugador);
            t.actualizarColumna(columna2, jugador);

            char decision;
            cout << "¿Deseas continuar lanzando los dados? (s/n): ";
            cin >> decision;
            if (decision == 'n' || decision == 'N')
            {
                continuar = false;
            }
        }
    }

    bool verificarVictoria(Tablero &t)
    {
        // Lógica para verificar si algún jugador ha ganado (por ejemplo, logrando 3 columnas)
        return false;
    }

};
