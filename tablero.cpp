
#include <iostream>
#include <map>
#include <cstdlib>
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

public:
    Tablero() 
    {
        ptr = (Celda **)malloc(11 * 8);
        for (int j = 0; j < 11; j++) 
        {
            ptr[j] = (Celda *)malloc(guia[j] * sizeof(Celda));
            for (int i = 0; i < guia[j]; i++) 
            {
                ptr[j][i] = Celda('.', '.', '.', '.');
            }
        }
    }

    void colocarFicha(int suma, int jugador) 
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
