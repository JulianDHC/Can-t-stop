#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class dado {

public:
    int resultados[4];
    dado() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < 4; i++) {
            resultados[i] = rand() % 6 + 1;
        }
    }

    void mostrar() {
        for (int resultado : resultados) {
            cout << resultado << " " << endl;
        }
    }
};