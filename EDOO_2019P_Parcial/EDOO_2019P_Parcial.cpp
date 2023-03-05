#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class Usuario 
{
    string _nombre;
    float _prioridad;

    public:

    string nombre() const { return _nombre; }
    float prioridad() const { return _prioridad; }
    // ...
};

void vacia_cola(vector<Usuario>& cola, int N, float P)
{
    int n=0;
    for(int k=1; k<cola.size(); k++)
    {
        if(cola[k].prioridad()>P)
        {
            cola.erase(cola[k]);
        }
    }
}