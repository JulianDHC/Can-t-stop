
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

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
