//
//  main.cpp
//  OperacionsVector
//
//  Created by Fatos Xhafa on 23/3/22.
//

//Programa per exemplificar les operacions amb els elements d'un vector
//Consultar element
//Modificar element
//Afegir element
//Eliminar element

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class OperacionsV{
    //Dades
    vector<int> v; //per un altre tipus d'elements ja sigui bàsic o una classe seria similar
    
    //API
    public:
        OperacionsV(){}
        OperacionsV(vector<int> v)
        {
            this -> v = v;
        }
        //Constructor de còpia--a completar
        //Operacions de consulta, mètodes const
        int getValori(int i) const
        {
            return v[i]; //retorn l'element a la posició i
        }
        int getN() const
        {
            return v.size(); //nombre d'elements
        }
        
        //Operació per consultar la suma dels elements del vector
        //Amb index i del vector
        int sumaIdx() const
        {
            int s = 0;
            for (int i = 0; i < v.size(); i++)
            {
                s += v[i];
            }
            return s;
        }
        //Operació per consultar la suma dels elements del vector
        //Amb iterador del vector
        int sumaIt() const
        {
            //Recorrem el vector
            int s = 0;
            
            for (vector<int> :: iterator it = v.begin(); it != v.end(); it++)
            {
                s += (*it); //el valor de l'element apuntat per it
            }
            return s;
        }
        
        //Operació de modificar element de la posició i
        void setValori(int i, int pValor)
        {
            v[i] = pValor; //assigna a l'element a la posició i un nou valor
        }
        //Afegir un nou element x
        //Versió 1: afegir al final
        //és eficient, però trenca l'ordenació, en cas que el vector està ordenat
        void afegir(int x)
        {
            v.push_back(x);
        }
        //Versio 2: afegir un element nou x a una posició donada k
        //Preserva l'ordenació, en cas que el vector està ordenat
        //Una versió sense ITERADOR seria la següent, però NO és eficient
        //DesplaÁar els elements k, k+1...una posició a la dreta
        void afegirIdx(int x, int k)
        {
            for (int i = v.size()-1; i >= k; i--)
            {
                v[i+1] = v[i];
            }
            v[k] = x; //escrivim el nou valor
        }
        
        //Versio 3: afegir un element nou x a una posició donada k
        //Preserva l'ordenació, en cas que el vector està ordenat
        //Versió amb ITERADOR, aquesta és la versió eficient
        //Necessitem dues coses:
        //1) declarar / inicialitzar un iterador
        //2) aplicar el mètode insert del vector
        vector<int>::iterator afegirIt(int x, int k)
        {
            vector<int>::iterator it = v.begin(); //declarem un iterador que apunta al principi del vector
            
            it = v.insert(it+k,x); //it+k apunta a l'element k-èssim
            
            return it;
        }
        
        //Eliminar l'element que ocupa la posició donada k
        //Preserva l'ordenació, en cas que el vector està ordenat
        //La versió amb ITERADOR, és la versió eficient
        //Necessitem aplicar el mètode erase del vector
        void eliminarIt(int k)
        {
            vector<int>::iterator it = v.begin(); //declarem un iterador que apunta al principi
            
            v.erase(it+k); //eliminem l'element de la posició k
        }
    
    //Operadors
    //Operadors ==, ... a completar
    
    friend istream& operator >> (istream& is, OperacionsV& OV)
    {
        cout << "Creació vector: Quants elements vols introduir?" << endl;
        int N;
        is >> N;
        cout << "Introdueix " << N << " valors enters:"<< endl;
        int x;
        for (int i = 0; i < N; i++)
        {
            is >> x;
            OV.v.push_back(x);
        }
        return is;
    }
    friend ostream& operator << (ostream& os, const OperacionsV& OV)
    {
        os << "El vector té " << OV.v.size() << " elements " << endl;
        cout << "Els valors són: " << endl;
        for (int i = 0; i < OV.v.size(); i++)
        {
            os << OV.v[i] << ' ';
        }
        os << endl;
        os << "Suma dels elements: " << OV.sumaIt() << endl;
        os << endl;
        
        return os;
    }
};

void menu(int& opc)
{
    cout << "Selecciona una opció:" << endl;
    
    cout << "1. Consultar" << endl;
    cout << "2. Modificar" << endl;
    cout << "3. Afegir" << endl;
    cout << "4. Eliminar" << endl;
    cout << "5. Sortir" << endl;
    cin >> opc;
}
//Programa de prova
int main()
{
    OperacionsV OV;
    cin >> OV;
    
    int op;
    menu(op);
    
    while (op != 5)
    {
        switch(op)
        {
            case 1:
                cout << OV;
                break;
            case 2:
                cout << "Introdueix la posició a modificar:" << endl;
                int i;
                cin >> i;
                cout << "Introdueix el valor nou:" << endl;
                int x;
                cin >> x;
                OV.setValori(i,x);
                cout << OV;
                break;
            case 3:
                cout << "Introdueix la posició a on afegir:" << endl;
                int k;
                cin >> k;
                cout << "Introdueix el valor a afegir:" << endl;
                int y;
                cin >> y;
                OV.afegirIt(y, k);
                cout << OV;
                break;
            case 4:
                cout << "Introdueix la posició a eleminar:" << endl;
                cin >> k;
                OV.eliminarIt(k);
                cout << OV;
                break;
            default:
                cout << "Finalitzat!" << endl;
                break;
        }
        menu(op);
    }

    return 0;
}