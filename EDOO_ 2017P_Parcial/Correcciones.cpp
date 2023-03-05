#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

using namespace std;

struct corrector
{
    string errata, correccion;
};

void leerfichero(ifstream d, vector<corrector>& correcciones)
{
    corrector c;
    while(d>>c.errata>>c.correccion) correcciones.push_back(c);
}

void corregir(vector<corrector> correcciones, vector<string>& textoent)
{
    for(int k=1; k<textoent.size(); k++)
    {
        for(int l=1; l<correcciones.size(); l++)
        {
            if(textoent[k]==correcciones[l].errata) textoent[k]=correcciones[l].correccion;
        }
    }
}

int main()
{
    ifstream sustituciones("sustituciones.txt");
    vector<corrector> correcciones;
    vector<string> textoent;
    string palabra;
    leerfichero(sustituciones,correcciones);
    while(cin>>palabra) textoent.push_back(palabra);
    corregir(correcciones,textoent);
    for(int k=1; k<textoent.size(); k++)
    {
        cout<<textoent[k];
    }
    cout<<endl;
}