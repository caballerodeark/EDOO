
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Correccion {
   string mala, buena;
};

vector<Correccion> lee_tabla(string fichero) {
   vector<Correccion> tabla;
   ifstream F(fichero.c_str());
   Correccion c;
   while (F >> c.mala >> c.buena) {
      tabla.push_back(c);
   }
   return tabla;
}

string sustituye(const vector<Correccion>& tabla,
                 string p) {
   for (int i = 0; i < tabla.size(); i++) {
      if (p == tabla[i].mala) {
         return tabla[i].buena;
      }
   }
   return p;
}

int main() {
   string palabra;
   vector<Correccion> tabla = lee_tabla("sustituciones.txt");
   while (cin >> palabra) {
      cout << sustituye(tabla, palabra) << ' ';
   }
   cout << endl;
}
