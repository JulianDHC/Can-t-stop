include <iostream>
#include <map>

using namespace std;

//map<char,int> posicion;


//char tablero[13][11];


class tablero{
    
    private:
        int guia[11] = {3,5,7,9,11,13,11,9,7,5,3};
        char** ptr;
        
    public:
        tablero(){
            
            ptr = (char**)malloc(11*8);
            for(int j=0; j<11 ;j++){
                    ptr[j] = (char*)malloc(guia[j]);
            }
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i] ;j++){
                    ptr[i][j] = 'c';
                }
            }
            
        }
        void mostrar(){
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i]; j++){
                    cout << ptr[i][j];
                }
                cout << endl;
            }
            
        }
    
};





int main(){
    
    
    
    tablero t;
    t.mostrar();
    
    r