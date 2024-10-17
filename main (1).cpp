#include <iostream>
#include <map>

using namespace std;

class celda{
    
   public:
   
       char c_[4];
       celda(char a, char b, char c, char d){
            c_[0] = a;  
            c_[1] = b; 
            c_[2] = c; 
            c_[3] = d; 
       }
       void mostrar(){
           cout << c_[0] << c_[1] << c_[2] << c_[3] << "|";
       }

   
   
};



class tablero{
    
    private:
        int guia[11] = {3,5,7,9,11,13,11,9,7,5,3};
        celda** ptr;
        
    public:
        tablero(){
            
            ptr = (celda**)malloc(11*8);
            for(int j=0; j<11 ;j++){
                    ptr[j] = (celda*)malloc(guia[j]);
            }
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i] ;j++){
                    ptr[i][j] = celda('1','2','3','4');
                }
            }
            
        }
        void mostrar(){
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i]; j++){
                    ptr[i][j].mostrar();
                }
                cout << endl;
            }
            
        }
    
};





int main(){
    
    
    
    tablero t;
    t.mostrar();
    
    return 0;
}

