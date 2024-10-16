#include <iostream>
#include <vector>

using namespace std;

class Tablero {
    
    private:
        vector<int> guia = {3, 5, 7, 9, 11, 13, 11, 9, 7, 5, 3};  
        vector<vector<char>> tablero; 
        
    public:
    int x = 2;
        Tablero() {
            tablero.resize(11);
            
            for(int i = 0; i < 11; i++) {
                tablero[i].resize(guia[i], 'O'); 
            }
        }
        
        void mostrar() {
            for(int i = 0; i < 11; i++) {
                for(int j = 0; j < guia[i]; j++) {
                    cout << tablero[i][j] << " ";
                }
                cout << x++ << endl;
            }
        }
};

int main() {
    
    Tablero t;
    t.mostrar();
    
    return 0;
}        
