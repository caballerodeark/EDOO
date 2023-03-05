
#include <iostream>
#include <list>
using namespace std;

struct Vector2 { float x, y; };

class Missil {
   Vector2 _pos;
public:
   Missil(Vector2 pos) { _pos = pos; }
   Vector2 getPos() { return _pos; }
};

void esborra_missils(list<Missil>& L) {
   list<Missil>::iterator it = L.begin();
   while (it != L.end()) {
      Vector2 pos = it->getPos();
      if (pos.x < 0 || pos.x > 1024 || pos.y < 0 || pos.y > 768) {
         it = L.erase(it);
      } else {
         it++;
      }
   }
}

int main() {}