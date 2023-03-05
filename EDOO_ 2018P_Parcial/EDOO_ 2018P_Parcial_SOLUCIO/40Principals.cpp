
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

struct Canso {
   int vots;
   string nom;
};

bool mes_vots(const Canso& a, const Canso& b) {
   return a.vots > b.vots;
}

int main() {
   list<Canso> lc;
   Canso c;
   ifstream F("cansons.txt");
   while (F >> c.vots) {
      getline(F, c.nom);
      lc.push_back(c);
   }
   lc.sort(mes_vots);
   lc.resize(40);
   list<Canso>::const_iterator it;
   for (it = lc.begin(); it != lc.end(); it++) {
      cout << it->nom << endl;
   }
}