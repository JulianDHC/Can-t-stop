#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

map<int, string> colores_jugadores = 
{
    {0, "\033[43m"},  // Amarillo
    {1, "\033[41m"},  // Rojo
    {2, "\033[44m"},  // Azul
    {3, "\033[42m"}   // Verde
};

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
        for (int i = 0; i < 4; i++)
        {
            if (c_[i] == '.')
            {
                cout << c_[i];  // Sin color para los puntos
            }
            else
            {
                cout << colores_jugadores[i] << c_[i] << "\033[0m";  // Color según el jugador
            }
        }
        cout << "|";
    }
};

class tablero {
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
            ptr[j] = (celda *)malloc(guia[j] * sizeof(celda));
            for (int i = 0; i < guia[j]; i++) 
            {
                ptr[j][i] = celda('.', '.', '.', '.');
            }
        }
    }

    void colocar_ficha(int suma, int jugador) 
    {
        int fila = suma - 2;
        
        for (int i = 0; i < guia[fila]; i++) 
        {
            if (ptr[fila][i].c_[jugador] == '.') 
            {  
                ptr[fila][i].c_[jugador] = ' ';
                break;
            }
        }
    }

    void mostrar() {
        cout << "                                 TABLERO" << endl;
        for (int i = 0; i < 11; i++) {
            cout << rotulo[i];
            for (int k = 0; k < ((13 - guia[i]) / 2); k++) {
                cout << "     ";
            }
            cout << "|";
            for (int j = 0; j < guia[i]; j++) {
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

class juego {
public:
    jugadores objeto_jugadores;
    Dado objeto_dado;            
    tablero tablero_juego;
    int turno2 = 0;
    bool turno;
    char condicion;
    
    juego() : turno2(0) {}

    void turnos() {
    int eleccion1, eleccion2;
    int suma1, suma2;
    
    while (true)
    {
        suma2 = 0;
        objeto_dado.lanzar();
        cout << "Es el turno de " << objeto_jugadores.nombres[turno2] << endl;
        cout << "Ha lanzado los dados y ha sacado: " << "\nDado 1: " << objeto_dado.resultados[0] 
             << "\nDado 2: " << objeto_dado.resultados[1] << "\nDado 3: " << objeto_dado.resultados[2] 
             << "\nDado 4: " << objeto_dado.resultados[3] << endl;
        cout << "Elija un dado a emparejar (1-4): ";
        cin >> eleccion1;
        cout << "Elija el otro (1-4): ";
        cin >> eleccion2;
        eleccion1--;
        eleccion2--;
        
        suma1 = objeto_dado.resultados[eleccion1] + objeto_dado.resultados[eleccion2];
        for (int j = 0; j < 4; j++) 
        {
            if(j != eleccion1 && j != eleccion2) 
            {
                suma2 += objeto_dado.resultados[j];
            }
        }

        tablero_juego.colocar_ficha(suma1, turno2);
        tablero_juego.colocar_ficha(suma2, turno2);
        tablero_juego.mostrar();
        
        cout << "¿Desea continuar?" << endl;
        cin >> condicion;
        if (condicion == 'n' || condicion == 'N')
        {
            turno2 = (turno2 + 1) % objeto_jugadores.Jugadores;
        }
    }
}


    void iniciar_juego() 
    {
        objeto_jugadores.PedirJugadores();
        objeto_jugadores.name_player();
        tablero_juego.mostrar();
        turnos();
    }
};

//00000000000000000000000000000000000000000000000000000000000000

int main()
{
    juego game;
    game.iniciar_juego();  
    return 0;
}
