#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Mapa de colores de fondo para los jugadores
map<int, string> colores_jugadores = {
    {0, "\033[43m"},  // Amarillo
    {1, "\033[41m"},  // Rojo
    {2, "\033[44m"},  // Azul
    {3, "\033[42m"}   // Verde
};

class jugadores {
public:
    int Jugadores;
    vector<string> nombres;

    int PedirJugadores() {
        do {
            cout << "Número de jugadores:" << endl;
            cin >> Jugadores;
            if (Jugadores < 2 || Jugadores > 4) {
                cout << "Error en la cantidad, reintente." << endl;
            }
        } while (Jugadores < 2 || Jugadores > 4);

        nombres.resize(Jugadores);
        return Jugadores;
    }

    void name_player() {
        for (int i = 0; i < Jugadores; i++) {
            cout << "Ingrese el nombre del jugador " << i + 1 << ":" << endl;
            cin >> nombres[i];
            cout << endl;
        }
    }

    void mostrar() {
        for (int i = 0; i < Jugadores; i++) {
            cout << nombres[i] << endl;
        }
    }
};

class celda {
public:
    char c_[4];
    vector<int> fichas;

    // Constructor por defecto
    celda() {
        c_[0] = '1';
        c_[1] = '2';
        c_[2] = '3';
        c_[3] = '4';
    }

    // Mostrar la celda con el color de fondo del jugador correspondiente
    void mostrar() {
        for (int i = 0; i < 4; i++) {
            if (find(fichas.begin(), fichas.end(), i) != fichas.end()) {
                // Si el jugador está en la casilla, coloreamos su número
                cout << colores_jugadores[i] << c_[i] << "\033[0m";
            } else {
                // Si el jugador no está, mostramos el número sin color
                cout << c_[i];
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
    map<int, int> suma_a_fila = {
        {2, 0}, {3, 1}, {4, 2}, {5, 3}, {6, 4}, {7, 5},
        {8, 6}, {9, 7}, {10, 8}, {11, 9}, {12, 10}
    };

public:
    tablero() {
        ptr = new celda*[11];
        for (int j = 0; j < 11; j++) {
            ptr[j] = new celda[guia[j]];
            for (int i = 0; i < guia[j]; i++) {
                // Inicializa cada celda usando el constructor por defecto
                ptr[j][i] = celda();
            }
        }
    }

    int obtener_posicion(int suma, int jugador) {
        int fila = suma_a_fila[suma];
        for (int i = 0; i < guia[fila]; i++) {
            auto& fichas = ptr[fila][i].fichas;
            if (find(fichas.begin(), fichas.end(), jugador) != fichas.end()) {
                return i;
            }
        }
        return -1; // No se encontró ficha
    }

    bool avanzar_ficha(int suma, int jugador) {
        int fila = suma_a_fila[suma];
        int pos_actual = obtener_posicion(suma, jugador);
        
        if (pos_actual == -1) {
            ptr[fila][0].fichas.push_back(jugador);
            return true;
        }
        
        if (pos_actual >= guia[fila] - 1) {
            return false;
        }
        
        ptr[fila][pos_actual].fichas.erase(
            remove(ptr[fila][pos_actual].fichas.begin(),
                  ptr[fila][pos_actual].fichas.end(),
                  jugador),
            ptr[fila][pos_actual].fichas.end());
        
        ptr[fila][pos_actual + 1].fichas.push_back(jugador);
        return true;
    }

    void mostrar() {
        cout << "\n                                 TABLERO" << endl;
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

    ~tablero() {
        for (int i = 0; i < 11; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }
};

class Dado {
public:
    int resultados[4];

    Dado() {
        srand(static_cast<unsigned int>(time(nullptr)));
        lanzar();
    }
    
    void lanzar() {
        for (int i = 0; i < 4; i++) {
            resultados[i] = rand() % 6 + 1;
        }
    }

    void mostrar() {
        for (int resultado : resultados) {
            cout << resultado << " ";
        }
        cout << endl;
    }
};

class juego {
public:
    jugadores objeto_jugadores;
    Dado objeto_dado;            
    tablero tablero_juego;
    int turno;
    map<int, vector<int>> fichas_jugador;

    juego() : turno(0) {}

    void iniciar_juego() {
        objeto_jugadores.PedirJugadores();
        objeto_jugadores.name_player();
        
        for (int i = 0; i < objeto_jugadores.Jugadores; i++) {
            fichas_jugador[i] = vector<int>();
        }
        
        turnos();
    }
    
    bool puedeColocarFicha(int jugador, int suma) {
        if (fichas_jugador[jugador].size() >= 3) {
            return find(fichas_jugador[jugador].begin(),
                       fichas_jugador[jugador].end(),
                       suma) != fichas_jugador[jugador].end();
        }
        return true;
    }
    
    void turnos() {
        bool continuar_turno;
        
        while (true) {
            cout << "\n--------------------------------------------" << endl;
            cout << "Es el turno de " << objeto_jugadores.nombres[turno] << endl;
            
            cout << "Tus fichas están en las filas: ";
            for (int suma : fichas_jugador[turno]) {
                cout << suma << " (posición " 
                     << tablero_juego.obtener_posicion(suma, turno) + 1 << ") ";
            }
            cout << endl;
            
            continuar_turno = true;
            
            while (continuar_turno) {
                objeto_dado.lanzar();
                cout << "\nHas lanzado los dados y has sacado: " << endl;
                for (int i = 0; i < 4; i++) {
                    cout << "Dado " << (i + 1) << ": " << objeto_dado.resultados[i] << endl;
                }
                
                int eleccion1, eleccion2;
                cout << "\nElija un dado a emparejar (1-4): ";
                cin >> eleccion1;
                cout << "Elija el otro (1-4): ";
                cin >> eleccion2;
                eleccion1--;
                eleccion2--;
                
                int suma1 = objeto_dado.resultados[eleccion1] + objeto_dado.resultados[eleccion2];
                
                cout << "\nElegiste las sumas: " << suma1 << endl;
                
                if (!puedeColocarFicha(turno, suma1)) {
                    cout << "No puedes colocar más de 3 fichas en diferentes filas, o ya tienes una ficha en esa fila." << endl;
                    continue;
                }
                
                if (!tablero_juego.avanzar_ficha(suma1, turno)) {
                    cout << "No puedes avanzar más en esta fila." << endl;
                } else {
                    cout << "Has avanzado en la fila de la suma " << suma1 << endl;
                    if (find(fichas_jugador[turno].begin(),
                            fichas_jugador[turno].end(),
                            suma1) == fichas_jugador[turno].end()) {
                        fichas_jugador[turno].push_back(suma1);
                    }
                }
                
                tablero_juego.mostrar();
                
                char decision;
                cout << "\nDeseas continuar lanzando? (s/n): ";
                cin >> decision;
                if (decision == 'n' || decision == 'N') {
                    continuar_turno = false;
                }
            }
            
            turno = (turno + 1) % objeto_jugadores.Jugadores;
        }
    }
};

int main()
{
    juego j;
    j.iniciar_juego();
    return 0;
}
