
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

struct Vector2 { float x, y; };

class Cercle {
   Vector2 _centre;
   float _radi;
public:
   Cercle(Vector2 c, float r) {
      _centre = c;
      _radi = r;
   }
   bool xoca(const vector<Cercle>& C);
};

bool Cercle::xoca(const vector<Cercle>& C) {
   for (int i = 0; i < C.size(); i++) {
      float dx = _centre.x - C[i]._centre.x;
      float dy = _centre.y - C[i]._centre.y;
      if (sqrt(dx*dx + dy*dy) < (_radi + C[i]._radi)) {
         return true;
      }
   }
   return false;
}

void xoc_cercles(vector<Cercle>& C, list<int>& xoquen) {
   for (int i = 0; i < C.size(); i++) {
      if (C[i].xoca(C)) {
         xoquen.push_back(i);
      }
   }
}

int main() {}