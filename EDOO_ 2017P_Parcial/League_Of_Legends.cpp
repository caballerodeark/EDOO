#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct equipo
{
    string equipo;
    vector<string> jugador;
    vector<int> puntuacio;
    int total()
    {
        int t=0;
        for (int k=1; k<puntuacio.size(); k++) t+=puntuacio[k];
        return t;
    }
    string jmax()
    {
        string campio;
        int rmax=0;
        for(int k=1; k<puntuacio.size(); k++)
        {
            if(puntuacio[k]>rmax)
            {
                rmax=puntuacio[k];
                campio=jugador[k];
            }
        }
        return campio;
    }
};

void leerfichero(ifstream LoL, vector<equipo>& t)
{
    equipo p;
    string linea, jug;
    int punct;
    while(LoL>>linea)
    {
        int sep=linea.find(":");
        p.equipo = linea.substr(0, sep);
        istringstream resultats(linea.substr(sep+1));
        while(resultats >> punct >> jug)
        {
            p.puntuacio.push_back(punct);
            p.jugador.push_back(jug);
        }
    }
}

int main()
{
    ifstream LoL("LoL.txt");
    vector<equipo> equipos;
    leerfichero(LoL, equipos);
    for(int k=1; k<equipos.size(); k++)
    {
        cout << equipos[k].equipo << ": " << equipos[k].total() << "(" << equipos[k].jmax() << ")" << endl;
    }
}