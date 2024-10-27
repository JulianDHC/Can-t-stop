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
                cout << " Turno del jugador " << i + 1 << " (Color: " << colores_jugadores[i] << "\033[0m" ")";
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
        vector<int> marcadores(3);
        int eleccion1 , eleccion2;
        int suma1;
        while ( continuar )
        {  

            d = dado();  // Lanza los dados
            cout << "Dados lanzados: "<< endl;
            d.mostrar();// muestra los dados
            cout << "\nEliga dos dados para sumarlos"<< endl;// tiene dos elecciones
            cin>> eleccion1;
            cin>> eleccion2;
            eleccion1--;// se resta una posicion a eleccion
            eleccion2--;
            suma1 = d.resultados[eleccion1] + d.resultados[eleccion2]; //se suman los resultados en la posicion de las elecciones
            
            int suma2 = 0;
            for (int j = 0; j < 4; j++) 
            {
               if(j != eleccion1 && j != eleccion2) 
               {
                   suma2 += d.resultados[j];
               }
            }
            cout<< "Fila donde avanzaras  " << suma1 << " y  " << suma2 << endl;

          
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
 
        return false;
    }

};
