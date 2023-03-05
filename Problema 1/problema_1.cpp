#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class linea
{
    string DNI;
    int edad;
    public:
    linea();
    linea(ifstream s)
    {
        s>>DNI>>edad;
    }
    linea(string DNI, int edad)
    {
        this->DNI=DNI;
        this->edad=edad;
    }
    int getedad()
    {
        return edad;
    }
    string getDNI()
    {
        return DNI;
    }

    vector<linea> lectura(ifstream s)
    {
        linea l;
        vector<linea> L;
        while(s>>l.DNI>>l.edad)
        {
            L.push_back(l);
        }
        return L;
    }

    friend bool operator<(const linea& L1, const linea& L2)
    {
        return L1.edad<L2.edad;
    }

    friend istream& operator>>(istream& is, linea& L)
    {
        is>>L.DNI>>L.edad;
        return is;
    }
    friend ostream& operator<<(ostream& os, linea& L)
    {
        os<<L.DNI<<L.edad;
        return os;
    }
};

void llegiriordenar(ifstream& s,list<linea>& L)
{
    linea l;
    while(s>>l)
    {
        L.push_back(l);
    }
    L.sort();
}

int main()
{
    ifstream persones("persones.txt");
    list<linea> L;
    llegiriordenar(persones,L);
    for(list<linea> :: iterator it=L.begin(); it!=L.end(); it++)
    {
        linea l=(*it);
        cout<<"DNI: "<<l.getDNI()<<" Edat: "<<l.getedad()<<endl;
    }
}