#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

class celda {
public:
    char c_[4];
    vector<int> fichas;

    // Constructor por defecto
    celda() {
        c_[0] = ' ';
        c_[1] = ' ';
        c_[2] = ' ';
        c_[3] = ' ';
    }

    // Constructor parametrizado
    celda(char a, char b, char c, char d) {
        c_[0] = a;
        c_[1] = b;
        c_[2] = c;
        c_[3] = d;
        fichas = vector<int>();
    }

    void mostrar() {
        if (fichas.empty()) {
            cout << c_[0] << c_[1] << c_[2] << c_[3] << "|";
        } else {
            string display = "J";
            for (int jugador : fichas) {
                display += to_string(jugador + 1);
                display += " ";
            }
            while (display.length() < 4) {
                display += " ";
            }
            cout << display << "|";
        }
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
            // Inicializa cada celda con los valores adecuados
            ptr[j][i] = celda('1', '2', '3', '4');
        }
    }
}


    // Devuelve la posición actual de la ficha del jugador en la fila dada
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

    // Avanza la ficha del jugador en la fila correspondiente a la suma
    bool avanzar_ficha(int suma, int jugador) {
        int fila = suma_a_fila[suma];
        int pos_actual = obtener_posicion(suma, jugador);
        
        // Si no hay ficha, la coloca al inicio
        if (pos_actual == -1) {
            ptr[fila][0].fichas.push_back(jugador);
            return true;
        }
        
        // Si ya está en la última posición, no puede avanzar
        if (pos_actual >= guia[fila] - 1) {
            return false;
        }
        
        // Elimina la ficha de la posición actual y la coloca en la siguiente
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
        cout << "     (J1, J2, J3, J4 representan las fichas de cada jugador)" << endl << endl;

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
    int turno;
    map<int, vector<int>> fichas_jugador;  // jugador -> vector de sumas donde tiene fichas

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
            
            // Mostrar las filas donde el jugador tiene fichas
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
                int suma2 = 0;
                for (int i = 0; i < 4; i++) {
                    if (i != eleccion1 && i != eleccion2) {
                        suma2 += objeto_dado.resultados[i];
                    }
                }
                
                cout << "\nSumas disponibles: " << suma1 << " y " << suma2 << endl;
                
                bool puede_suma1 = puedeColocarFicha(turno, suma1);
                bool puede_suma2 = puedeColocarFicha(turno, suma2);
                
                if (!puede_suma1 && !puede_suma2) {
                    cout << "No puedes colocar fichas con ninguna de estas sumas. Tu turno termina." << endl;
                    continuar_turno = false;
                } else {
                    int suma_elegida;
                    do {
                        cout << "¿Qué suma desea utilizar? (" << suma1 << " o " << suma2 << "): ";
                        cin >> suma_elegida;
                    } while (suma_elegida != suma1 && suma_elegida != suma2);
                    
                    if ((suma_elegida == suma1 && puede_suma1) || 
                        (suma_elegida == suma2 && puede_suma2)) {
                        // Si es una nueva fila para el jugador, la registramos
                        if (find(fichas_jugador[turno].begin(),
                               fichas_jugador[turno].end(),
                               suma_elegida) == fichas_jugador[turno].end()) {
                            fichas_jugador[turno].push_back(suma_elegida);
                        }
                        
                        // Avanzamos la ficha en el tablero
                        if (tablero_juego.avanzar_ficha(suma_elegida, turno)) {
                            cout << "Ficha avanzada con éxito!" << endl;
                        } else {
                            cout << "La ficha ya está en la última posición de esa fila!" << endl;
                        }
                    }
                    
                    // Mostrar el estado actual del tablero
                    tablero_juego.mostrar();
                    
                    if (continuar_turno) {
                        char continuar;
                        cout << "¿Desea continuar su turno? (s/n): ";
                        cin >> continuar;
                        continuar_turno = (continuar == 's' || continuar == 'S');
                    }
                }
            }
            
            turno = (turno + 1) % objeto_jugadores.Jugadores;
        }
    }
};

int main()
{
    juego game;  // Instancia del juego
    game.iniciar_juego();  // Iniciar el juego y los turnos
    
    return 0;  // Fin del programa
}