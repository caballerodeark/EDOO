
#include <iostream>
using namespace std;

#include "fecha.h"

int main() 
{
  Fecha f(10, 4, 2019);
  cout << f.dia() << '/' << f.mes() << '/' << f.anyo() << endl;
}