#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;

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
    map<int, string> colores_jugadores
    {
    {0, "\033[43m"},  // Amarillo
    {1, "\033[41m"},  // Rojo
    {2, "\033[44m"},  // Azul
    {3, "\033[42m"}   // Verde
    };
    void mostrar()
    {
        for (int i = 0; i < 4; i++)
        {
            if (c_[i] == '.')
            {
                cout << c_[i];
            }
            else
            {
                cout << colores_jugadores[i] << c_[i] << "\033[0m"; 
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
            if (col_anterior + 1 < guia[fila]) 
            {
                ptr[fila][col_anterior].c_[jugador] = '.'; 
                ptr[fila][col_anterior + 1].c_[jugador] = ' ';
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
                cout << "El jugador ya llego al final en esta fila." << endl;
                for (int i = 0; i < 4; i++) 
                {
                    if (i != jugador) 
                    {
                        for (auto it = posiciones_jugadores[i].begin(); it != posiciones_jugadores[i].end();) {
                            if (it->first == fila) 
                            {
                                it = posiciones_jugadores[i].erase(it);
                                for (int j = 0; j < guia[fila]; j++) 
                                {
                                    ptr[fila][j].c_[i] = '.';
                                }
                            } 
                            else
                            {
                                ++it;
                            }
                        }
                    }
                }
            }
        }
        else 
        {
            if (posiciones_jugadores[jugador].size() < 3) 
            {
                ptr[fila][0].c_[jugador] = ' ';
                posiciones_jugadores[jugador].push_back({fila, 0});
            }
            else 
            {
                cout << "Una de las sumas no coincide." << endl;
            }
        }
    }
    
    bool verificacion(int suma1, int suma2, int jugador) 
    {
        if (posiciones_jugadores[jugador].size() == 3) 
        {
            for (auto& pos : posiciones_jugadores[jugador]) 
            {
                if (pos.first == suma1 - 2 || pos.first == suma2 - 2) 
                {
                    return true;
                }
            }
            cout << "Ninguna suma coincide con las filas, pierdes el turno." << endl;
            return false;
        }
        return true; 
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
