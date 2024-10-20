#include <iostream>
#include <map>
#include <string>
#include "Tablero.cpp"
#include "jugadores.cpp"
using namespace std;

int main(){
    
    jugadores j;
    j.PedirJugadores();
    tablero t;
    t.mostrar();
    return 0;
}
