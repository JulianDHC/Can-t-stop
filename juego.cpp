
#include "jugadores.cpp"
#include "tablero.cpp"
#include "dado.cpp"
#include <iostream>
using namespace std;

class Juego {
public:
    Jugadores objeto_jugadores;
    Dado objeto_dado;            
    Tablero tablero_juego;
    int turno2 = 0;
    char condicion;
    
    Juego() : turno2(0) {}

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

        tablero_juego.colocarFicha(suma1, turno2);
        tablero_juego.colocarFicha(suma2, turno2);
        tablero_juego.mostrar();
        
        cout << "¿Desea continuar?" << endl;
        cin >> condicion;
        if (condicion == 'n' || condicion == 'N')
        {
            turno2 = (turno2 + 1) % objeto_jugadores.num_jugadores;
        }
    }
}


    void iniciarJuego() 
    {
        objeto_jugadores.pedirJugadores();
        objeto_jugadores.nombreJugadores();
        tablero_juego.mostrar();
        turnos();
    }
};
