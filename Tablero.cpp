#include <iostream>
#include <string>
#include <map>
using namespace std;

class celda
{
    
   public:
       char c_[4];
    celda(char a, char b, char c, char d)
    {
        c_[0] = a;
        c_[1] = b;
        c_[2] = c;
        c_[3] = d;
    }


     void mostrar()
     {    
          cout << c_[0] << c_[1] << c_[2] << c_[3] << "|";
     }

   
   
};



class Tablero{
    
    private:
        int guia[11] = {3,5,7,9,11,13,11,9,7,5,3};
        string rotulo[11] = {"2 : ","3 : ","4 : ","5 : ","6 : ","7 : ","8 : ","9 : ","10: ","11: ","12: "};
        celda** ptr;
        int numJugadores;
        
    public:
  
        Tablero()
        {
            
            ptr = (celda**)malloc(11*8);
            for(int j=0; j<11 ;j++){
                    ptr[j] = (celda*)malloc(guia[j]);
            }
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i] ;j++){
                    ptr[i][j] = celda('0','0','0','0');
                }
            }
            
        }/*(se cambio el tablero para que cambie por 0 todo y asi sea
        mas manejable y entendible para el usario dando asi que el numero de 0 que
        haya son los numeros de jugadores)*/
        void mostrar() 
        {
            cout << "                                 TABLERO" << endl;
               
            for(int i = 0; i<11 ;i++)
            {
               cout << rotulo[i];
               for(int k=0; k<((13-guia[i])/2) ; k++)
               {
                    cout <<  "     ";
               }
                cout << "|";
                 for(int j=0; j<guia[i]; j++)
                 {
                     ptr[i][j].mostrar();
                 }
                cout << endl;
            }
          
        }
     void actualizarColumna(int columna, int jugador)
        {
            int idx = columna - 2;
            for(int i = 0; i < guia[idx]; i++)
            {
                if(ptr[idx][i].c_[0] == '0')
                {
                    ptr[idx][i] = celda(jugador+'1', '0', '0', '0');
                    break;
                }
            }
        }     
    
};

