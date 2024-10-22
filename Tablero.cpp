#include <iostream>
#include <string>
#include "juego.cpp"
using namespace std;

class celda
{
    
   public:
       char c_[4];
       celda()
       {
         for(int i=0 ;i<4;i++ ) 
          c_[i]=' ';
       }  
     

     void asignarJugadores(int numJugadores)// Asigna un '0' por cada jugador 
     { 
        for (int i = 0; i < numJugadores; ++i) 
        {
          c_[i] = '0'; 
        }   
     }


     void mostrar()
     {    
          cout << c_[0] << c_[1] << c_[2] << c_[3] << c_[4]<< "|";
     }

   
   
};



class tablero{
    
    private:
        int guia[11] = {3,5,7,9,11,13,11,9,7,5,3};
        string rotulo[11] = {"2 : ","3 : ","4 : ","5 : ","6 : ","7 : ","8 : ","9 : ","10: ","11: ","12: "};
        celda** ptr;
        int numJugadores;
        
    public:
        tablero(int numJugadores): numJugadores(numJugadores)
        {
            
            ptr = (celda**)malloc(11*8);
            for(int j=0; j<11 ;j++){
                    ptr[j] = (celda*)malloc(guia[j]);
            }
            
            for(int i = 0; i<11 ;i++){
                for(int j=0; j<guia[i] ;j++){
                    ptr[i][j].asignarJugadores(numJugadores);
                  //  ptr[i][j] = celda('0','0','0','0');
                }
            }
            
        }/*(se cambio el tablero para que cambie por 0 todo y asi sea
        mas manejable y entendible para el usario dando asi que el numero de 0 que
        haya son los numeros de jugadores)*/
        void mostrar() 
        {
             //cout<< numJugadores<<endl;
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
    
};

