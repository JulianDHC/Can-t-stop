#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Cuadrado {
public:
    std::string color;

    Cuadrado(const std::string& c) : color(c) {}
};

class Marcador {
public:
    int posicion;
    std::string jugador;

    Marcador(int p, const std::string& j) : posicion(p), jugador(j) {}
    void mover(int pasos) {
        posicion += pasos; // Mover según el número de pasos
    }
};

class Columna {
public:
    int numero;
    std::vector<Marcador> marcadores;

    Columna(int n) : numero(n) {}

    void agregarMarcador(Marcador m) {
        marcadores.push_back(m);
    }

    bool esGanada() {
        for (const auto& marcador : marcadores) {
            if (marcador.posicion >= numero) {
                return true;
            }
        }
        return false;
    }

    void mostrarEstado() {
        std::cout << "Columna " << numero << ": ";
        for (const auto& marcador : marcadores) {
            std::cout << "[" << marcador.jugador << " en " << marcador.posicion << "] ";
        }
        std::cout << std::endl;
    }
};

class Tablero {
public:
    std::vector<Columna> columnas;

    Tablero() {
        for (int i = 1; i <= 12; ++i) {
            columnas.emplace_back(i);
        }
    }

    void mostrarEstado() {
        std::cout << "Estado del Tablero:\n";
        for (auto& columna : columnas) {
            columna.mostrarEstado();
        }
        std::cout << std::endl; // Espacio adicional entre turnos
    }

    bool verificarColumnaGanada(int num) {
        return columnas[num - 1].esGanada();
    }
};

class Jugador {
public:
    std::string color;
    std::vector<Cuadrado> cuadrados;
    std::vector<Marcador> marcadores;
    int columnasGanadas;

    Jugador(const std::string& c) : color(c), columnasGanadas(0) {
        for (int i = 0; i < 3; ++i) { // Cada jugador tiene tres marcadores
            marcadores.emplace_back(0, c);
        }
    }

    int tirarDados() {
        int dado1 = rand() % 6 + 1;
        int dado2 = rand() % 6 + 1;
        int dado3 = rand() % 6 + 1;
        int dado4 = rand() % 6 + 1;
        std::cout << color << " ha tirado: " << dado1 << " " << dado2 << " " << dado3 << " " << dado4 << std::endl;
        return dado1 + dado2 + dado3 + dado4;
    }

    void mostrarMarcadores() {
        std::cout << color << " tiene los siguientes marcadores:\n";
        for (size_t i = 0; i < marcadores.size(); ++i) {
            std::cout << "Marcador " << i + 1 << ": en " << marcadores[i].posicion << std::endl;
        }
    }
};

class Juego {
public:
    std::vector<Jugador> jugadores;
    Tablero tablero;
    int turnoActual;

    Juego() : turnoActual(0) {
        jugadores.emplace_back("Rojo");
        jugadores.emplace_back("Verde");
        jugadores.emplace_back("Azul");
        jugadores.emplace_back("Amarillo");
    }

    void iniciarJuego() {
        std::cout << "¡El juego ha comenzado!" << std::endl;
    }

    void siguienteTurno() {
        Jugador& jugadorActual = jugadores[turnoActual];
        bool turnoActivo = true;

        while (turnoActivo) {
            int totalDado = jugadorActual.tirarDados();
            int pareja1, pareja2;

            // Elegir pareja de números
            std::cout << "Crea una pareja (ejemplo: 6 y 10): ";
            std::cin >> pareja1 >> pareja2;

            // Validar las parejas
            if (pareja1 < 1 || pareja1 > 12 || pareja2 < 1 || pareja2 > 12) {
                std::cout << "Pareja no válida. Intenta de nuevo." << std::endl;
                continue;
            }

            // Mover o agregar marcadores
            moverMarcadores(jugadorActual, pareja1, pareja2);

            tablero.mostrarEstado();

            // Verificar si hay un ganador
            if (verificarGanador()) {
                std::cout << jugadorActual.color << " ha ganado el juego!" << std::endl;
                exit(0);
            }

            std::string continuar;
            std::cout << "¿Quieres continuar tirando? (s/n): ";
            std::cin >> continuar;
            if (continuar != "s") {
                turnoActivo = false; // Terminar el turno si el jugador no quiere continuar
            }
        }

        turnoActual = (turnoActual + 1) % jugadores.size(); // Pasar al siguiente jugador
    }

    void moverMarcadores(Jugador& jugador, int col1, int col2) {
        for (int i = 0; i < 2; ++i) { // Por cada columna elegida
            int columnaElegida = (i == 0) ? col1 : col2;

            // Si la columna ya tiene un marcador
            if (jugador.marcadores[i].posicion == columnaElegida) {
                jugador.marcadores[i].mover(1); // Mover hacia arriba
            } else {
                // Agregar nuevo marcador en la columna
                jugador.marcadores[i].posicion = columnaElegida;
                tablero.columnas[columnaElegida - 1].agregarMarcador(jugador.marcadores[i]);
            }
        }
    }

    bool verificarGanador() {
        for (const auto& jugador : jugadores) {
            if (jugador.columnasGanadas >= 3) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Para generar números aleatorios
    Juego juego;
    juego.iniciarJuego();

    // Simulación de turnos
    while (true) {
        juego.siguienteTurno();
    }

    return 0;
}
