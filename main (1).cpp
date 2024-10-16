#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>

using namespace std;

class Jugador {
private:
    string nombre;
    int posicion;

public:
    Jugador(string n) : nombre(n), posicion(0) {}

    string getNombre() const {
        return nombre;
    }

    int getPosicion() const {
        return posicion;
    }

    void mover(int pasos) {
        posicion += pasos;
    }
};

class Tablero {
private:
    vector<vector<char>> tablero;
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    vector<Jugador> jugadores;

public:
    Tablero() {
        for (int i = 0; i < 11; i++) {
            tablero.push_back(vector<char>(guia[i], '.'));
        }
    }

    void mostrar() {
        // Limpia el tablero
        for (int i = 0; i < 11; i++) {
            fill(tablero[i].begin(), tablero[i].end(), '.');
        }

        // Coloca los jugadores en el tablero
        for (const auto& jugador : jugadores) {
            if (jugador.getPosicion() < 11) { // Verificar que esté dentro de los límites del tablero
                tablero[jugador.getPosicion()].push_back('J'); // J representa un jugador
            }
        }

        // Muestra el tablero
        for (int i = 0; i < 11; i++) {
            cout << string(guia[i], 'c') << " " << (i + 2) << " ";
            for (int j = 0; j < tablero[i].size(); j++) {
                cout << tablero[i][j];
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
            dado = rand() % 6 + 1; // Números del 1 al 6
        }

        cout << "Dados lanzados: ";
        for (int dado : dados) {
            cout << dado << " ";
        }
        cout << endl;

        // Permitir al jugador seleccionar pares de dados para moverse
        int movimiento = seleccionarMovimientos(dados);
        jugador.mover(movimiento);
        cout << jugador.getNombre() << " se mueve a la posición " << jugador.getPosicion() << endl;

        // Mostrar el tablero actualizado
        mostrar();
    }

    int seleccionarMovimientos(const vector<int>& dados) {
        vector<bool> seleccionados(dados.size(), false);
        int movimiento = 0;

        for (int i = 0; i < 2; ++i) {
            cout << "Selecciona un dado (0-" << dados.size() - 1 << "): ";
            int indice;
            cin >> indice;

            // Verificación de selección válida
            if (indice < 0 || indice >= dados.size() || seleccionados[indice]) {
                cout << "Selección inválida. Intenta de nuevo." << endl;
                --i; // Decrementar el contador para volver a preguntar
                continue;
            }

            seleccionados[indice] = true;
            movimiento += dados[indice];
        }

        return movimiento; // Devuelve la suma de los dados seleccionados
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicializa la semilla aleatoria

    int cantidadJugadores;
    cout << "¿Cuántos jugadores? ";
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
            char decision;
            cout << "¿" << jugador.getNombre() << ", quieres lanzar los dados? (s/n): ";
            cin >> decision;

            if (decision == 's' || decision == 'S') {
                t.lanzarDados(jugador);
            } else {
                cout << jugador.getNombre() << " ha decidido no lanzar." << endl;
            }
        }

        // Aquí puedes agregar la lógica para determinar si el juego continúa
        char continuarJuego;
        cout << "¿Continuar el juego? (s/n): ";
        cin >> continuarJuego;
        continuar = (continuarJuego == 's' || continuarJuego == 'S');
    }

    return 0;
}
