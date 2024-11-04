#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include "colores.h"
using namespace std;

extern map<int, string> colores_jugadores;

class Celda
{
public:
    char c_[4];
    Celda(char a, char b, char c, char d)
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

class Tablero {
private:
    int guia[11] = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};
    string rotulo[11] = {"2 : ", "3 : ", "4 : ", "5 : ", "6 : ", "7 : ", "8 : ", "9 : ", "10: ", "11: ", "12: "};
    Celda **ptr;

    // Vector para rastrear hasta tres posiciones de fichas activas por jugador
    map<int, vector<pair<int, int>>> posiciones_jugadores;

public:
    Tablero() 
    {
        ptr = (Celda **)malloc(11 * sizeof(Celda *));
        for (int j = 0; j < 11; j++) 
        {
            ptr[j] = (Celda *)malloc(guia[j] * sizeof(Celda));
            for (int i = 0; i < guia[j]; i++) 
            {
                ptr[j][i] = Celda('.', '.', '.', '.');
            }
        }
    }

    void colocar_ficha(int suma, int jugador) 
    {
        int fila = suma - 2;

        // Verificar si el jugador ya tiene una ficha en esta fila
        bool ficha_en_fila = false;
        int col_anterior = -1;

        for (auto &pos : posiciones_jugadores[jugador]) 
        {
            if (pos.first == fila) 
            {
                ficha_en_fila = true;
                col_anterior = pos.second;
                break;
            }
        }

        if (ficha_en_fila) 
        {
            // Si ya tiene una ficha en esta fila, avanzar y eliminar posición anterior
            if (col_anterior + 1 < guia[fila]) 
            {
                ptr[fila][col_anterior].c_[jugador] = '.';  // Borrar posición anterior
                ptr[fila][col_anterior + 1].c_[jugador] = ' ';  // Avanzar ficha
                // Actualizar la nueva posición en el vector
                for (auto &pos : posiciones_jugadores[jugador]) 
                {
                    if (pos.first == fila) 
                    {
                        pos.second = col_anterior + 1;
                        break;
                    }
                }
            }
            else 
            {
                cout << "No se puede avanzar más en esta fila." << endl;
            }
        }
        else 
        {
            // Si no tiene una ficha en esta fila, agregar una nueva
            if (posiciones_jugadores[jugador].size() < 3) 
            {
                ptr[fila][0].c_[jugador] = ' ';  // Colocar ficha en la primera posición de la fila
                posiciones_jugadores[jugador].push_back({fila, 0});  // Guardar la posición en el vector
            }
            else 
            {
                cout << "El jugador ya tiene 3 fichas activas en el tablero." << endl;
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
