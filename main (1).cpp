#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class jugadores
{
public:
    int Jugadores;
    vector<string> nombres;

    int PedirJugadores()
    {
        do
        {
            cout << "Número de jugadores:" << endl;
            cin >> Jugadores;
            if (Jugadores < 2 || Jugadores > 4)
            {
                cout << "Error en la cantidad, reintente." << endl;
            }
        } while (Jugadores < 2 || Jugadores > 4);

        nombres.resize(Jugadores);
        return Jugadores;
    }

    void name_player()
    {
        for (int i = 0; i < Jugadores; i++)
        {
            cout << "Ingrese el nombre del jugador " << i + 1 << ":" << endl;
            cin >> nombres[i];
            cout << endl;
        }
    }

    void mostrar()
    {
        for (int i = 0; i < Jugadores; i++)
        {
            cout << nombres[i] << endl;
        }
    }
};

//00000000000000000000000000000000000000000000000000000000000000

class celda
{
public:
    char c_[4];
    celda(char a, char b, char c, char d)
    {
        c_[0] = a;
        c_[1] = b;
        c_[2] = c;
        c_[3] = d;
    }
    void mostrar()
    {
        cout << c_[0] << c_[1] << c_[2] << c_[3] << "|";
    }
};

class tablero
{
private:
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    string rotulo[11] = {"2 : ", "3 : ", "4 : ", "5 : ", "6 : ", "7 : ", "8 : ", "9 : ", "10: ", "11: ", "12: "};
    celda **ptr;

public:
    tablero()
    {
        ptr = (celda **)malloc(11 * 8);
        for (int j = 0; j < 11; j++)
        {
            ptr[j] = (celda *)malloc(guia[j]);
        }

        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < guia[i]; j++)
            {
                ptr[i][j] = celda('1', '2', '3', '4');
            }
        }
    }
    void mostrar()
    {
        cout << "                                 TABLERO" << endl;

        for (int i = 0; i < 11; i++)
        {
            cout << rotulo[i];
            for (int k = 0; k < ((13 - guia[i]) / 2); k++)
            {
                cout << "     ";
            }
            cout << "|";
            for (int j = 0; j < guia[i]; j++)
            {
                ptr[i][j].mostrar();
            }
            cout << endl;
        }
    }
};

//00000000000000000000000000000000000000000000000000000000000000

class Dado
{
public:
    int resultados[4];

    Dado()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        lanzar();
    }
    
    void lanzar()
    {
        for (int i = 0; i < 4; i++)
        {
            resultados[i] = rand() % 6 + 1;
        }
    }

    void mostrar()
    {
        for (int resultado : resultados)
        {
            cout << resultado << " ";
        }
        cout << endl;
    }
};

//00000000000000000000000000000000000000000000000000000000000000

class juego
{
public:
    jugadores objeto_jugadores;
    Dado objeto_dado;            
    int turno; 

    juego()
    {
        turno = 0;
    }

    void iniciar_juego()
    {
        objeto_jugadores.PedirJugadores();
        objeto_jugadores.name_player();
        
        turnos();
    }
    
    void turnos()
    {
        int eleccion1;
        int eleccion2;
        int suma1;
        int suma2;
        
        for (int i = 0; i < 5; i++)
        {
            suma2 = 0;
            objeto_dado.lanzar();
            cout << "Es el turno de " << objeto_jugadores.nombres[turno] << endl;
            cout << "Ha lanzado los dados y ha sacado: " << "\nDado 1: " << objeto_dado.resultados[0] << "\nDado 2: " << objeto_dado.resultados[1] << "\nDado 3: " << objeto_dado.resultados[2] << "\nDado 4: " << objeto_dado.resultados[3] << endl;
            cout << "Elija un dado a emparejar: ";
            cin >> eleccion1;
            cout << "Elija el otro: ";
            cin >> eleccion2;
            eleccion1 = eleccion1 - 1;
            eleccion2 = eleccion2 - 1;
            suma1 = objeto_dado.resultados[eleccion1] + objeto_dado.resultados[eleccion2];
            for (int i = 0; i < 4; i++)
            {
                if(eleccion1 != i && eleccion2 != i)
                {
                    suma2 = suma2 + objeto_dado.resultados[i];
                }
            }
            turno = (turno + 1) % objeto_jugadores.Jugadores;
            cout << suma1 << " + " << suma2 << " -> Solo probando sumas" << endl;
        }
    };
};

//00000000000000000000000000000000000000000000000000000000000000

int main()
{
    tablero t;
    Dado d;
    juego game;

    game.iniciar_juego();  
    t.mostrar();
    return 0;
}
