#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

class Jugador {
private:
    string nombre;
    map<int, int> posiciones; // Mapa para las posiciones en columnas (2 a 12)
    int columnasGanadas;

public:
    Jugador(string n) : nombre(n), columnasGanadas(0) {
        for (int i = 2; i <= 12; ++i) {
            posiciones[i] = 0; // Todas las posiciones inician en 0
        }
    }

    string getNombre() const {
        return nombre;
    }

    int getPosicion(int columna) const {
        return posiciones.at(columna);
    }

    void mover(int columna, int pasos, int limiteColumna) {
        if (columna >= 2 && columna <= 12 && posiciones[columna] < limiteColumna) {
            posiciones[columna] += pasos;
            if (posiciones[columna] >= limiteColumna) {  // Si el jugador alcanza el final de la columna
                posiciones[columna] = limiteColumna;
                cout << nombre << " ha ganado la columna " << columna << "!\n";
                columnasGanadas++;
            }
        }
    }

    bool haGanado() const {
        return columnasGanadas >= 3; // Gana cuando ha alcanzado 3 columnas
    }

    int getColumnasGanadas() const {
        return columnasGanadas;
    }
};

class Tablero {
private:
    map<int, int> longitudesColumnas; // Mapa de longitud de cada columna
    map<int, vector<char>> tablero; // Mapa de columnas con sus posiciones
    vector<Jugador> jugadores;

public:
    Tablero() {
        // Definir las longitudes de las columnas según la probabilidad de obtener la suma
        longitudesColumnas = {
            {2, 3}, {3, 5}, {4, 7}, {5, 9}, {6, 11},
            {7, 13}, {8, 11}, {9, 9}, {10, 7}, {11, 5}, {12, 3}
        };

        // Inicializar el tablero
        for (const auto& par : longitudesColumnas) {
            int columna = par.first;
            int longitud = par.second;
            tablero[columna] = vector<char>(longitud, '.');
        }
    }

    void mostrar() {
        // Limpia el tablero
        for (auto& par : tablero) {
            fill(par.second.begin(), par.second.end(), '.');
        }

        // Coloca los jugadores en el tablero
        for (const auto& jugador : jugadores) {
            for (const auto& par : longitudesColumnas) {
                int columna = par.first;
                int limiteColumna = par.second;
                int posicion = jugador.getPosicion(columna);
                if (posicion > 0 && posicion <= limiteColumna) {
                    tablero[columna][posicion - 1] = jugador.getNombre()[0]; // Inicial del jugador
                }
            }
        }

        // Muestra el tablero
        cout << "\nTablero:\n";
        for (const auto& par : longitudesColumnas) {
            int columna = par.first;
            cout << columna << " ";
            for (char c : tablero[columna]) {
                cout << c << " ";
            }
            cout << endl;
        }
    }

    void agregarJugador(const Jugador& jugador) {
        jugadores.push_back(jugador);
    }

    vector<Jugador>& getJugadores() {
        return jugadores;
    }

    void lanzarDados(Jugador& jugador) {
        vector<int> dados(4);
        for (int& dado : dados) {
            dado = rand() % 6 + 1; // Dados de 1 a 6
        }

        cout << "Dados lanzados: ";
        for (int dado : dados) {
            cout << dado << " ";
        }
        cout << endl;

        // Generar combinaciones posibles
        vector<pair<int, int>> combinaciones = {
            {dados[0] + dados[1], dados[2] + dados[3]},
            {dados[0] + dados[2], dados[1] + dados[3]},
            {dados[0] + dados[3], dados[1] + dados[2]}
        };

        // Filtrar combinaciones válidas (columna existente)
        vector<pair<int, int>> combinacionesValidas;
        for (const auto& combinacion : combinaciones) {
            if (longitudesColumnas.count(combinacion.first) && longitudesColumnas.count(combinacion.second)) {
                combinacionesValidas.push_back(combinacion);
            }
        }

        if (combinacionesValidas.empty()) {
            cout << "No hay combinaciones válidas disponibles. Turno perdido.\n";
            return;
        }

        // Mostrar opciones
        cout << "Opciones de movimiento:\n";
        for (size_t i = 0; i < combinacionesValidas.size(); ++i) {
            cout << i + 1 << ": (" << combinacionesValidas[i].first << ", " << combinacionesValidas[i].second << ")\n";
        }

        // Selección de combinación por parte del jugador
        int opcion;
        do {
            cout << "Selecciona una combinación (1-" << combinacionesValidas.size() << "): ";
            cin >> opcion;
        } while (opcion < 1 || opcion > combinacionesValidas.size());

        auto movimientos = combinacionesValidas[opcion - 1];

        // Avanza en las columnas dependiendo del movimiento seleccionado
        int limiteColumna1 = longitudesColumnas[movimientos.first];
        int limiteColumna2 = longitudesColumnas[movimientos.second];

        jugador.mover(movimientos.first, 1, limiteColumna1);  // Avanza en la primera columna
        jugador.mover(movimientos.second, 1, limiteColumna2); // Avanza en la segunda columna

        cout << jugador.getNombre() << " se mueve en las columnas " << movimientos.first << " y " << movimientos.second << ".\n";

        // Mostrar el tablero actualizado
        mostrar();
    }

    bool verificarGanador(Jugador& jugador) {
        if (jugador.haGanado()) {
            cout << "\n¡Felicidades! " << jugador.getNombre() << " ha ganado el juego al alcanzar 3 columnas!\n";
            return true;
        }
        return false;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializa la semilla aleatoria

    int cantidadJugadores;
    cout << "¿Cuántos jugadores? (2-4): ";
    cin >> cantidadJugadores;

    Tablero t;

    for (int i = 0; i < cantidadJugadores; ++i) {
        string nombre;
        cout << "Nombre del jugador " << (i + 1) << ": ";
        cin >> nombre;
        t.agregarJugador(Jugador(nombre));
    }

    // Ciclo principal del juego
    bool continuar = true;
    while (continuar) {
        for (auto& jugador : t.getJugadores()) {
            cout << "\nTurno de " << jugador.getNombre() << ":\n";
            char decision;
            cout << "¿Quieres lanzar los dados? (s/n): ";
            cin >> decision;

            if (decision == 's' || decision == 'S') {
                t.lanzarDados(jugador);

                // Verificar si el jugador ha ganado
                if (t.verificarGanador(jugador)) {
                    continuar = false;
                    break;
                }
            } else {
                cout << jugador.getNombre() << " ha decidido no lanzar.\n";
            }
        }
    }

    return 0;
}
