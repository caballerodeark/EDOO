#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <sstream>

using namespace std;

struct cancion
{
    int pos;
    string nom;
};

vector<cancion> lista(ifstream canciones)
{
    vector<cancion> t;
    string linea;
    cancion c;
    vector<cancion> vec;
    while(getline(canciones, linea))
    {
        c.pos==substr();
    }
}