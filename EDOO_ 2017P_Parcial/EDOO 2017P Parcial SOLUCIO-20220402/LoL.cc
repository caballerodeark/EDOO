
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Jugador {
   string nombre;
   int puntos;
};

int main() 
{
   ifstream lol("LoL.txt");
   string equipo;
   
   while (getline(lol, equipo)) 
   {
      Jugador J, Jmax;
      int puntos, total = 0, maximo;
      int sep = equipo.find(':');
      string nombre = equipo.substr(0, sep);
      istringstream S(equipo.substr(sep+1));
      S >> Jmax.nombre >> Jmax.puntos;
      total  = Jmax.puntos;

      while (S >> J.nombre >> J.puntos) 
      {
         if (J.puntos > Jmax.puntos) 
         {
            Jmax = J;
         }
         total += J.puntos;
      }

      cout << nombre << ": " << total << "(" << Jmax.nombre << ")" << endl;
   }
}
