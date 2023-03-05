//
//  main.cpp
//  PersonesPerEdats
//
//  Created by Fatos Xhafa on 06/06/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 Problema 1 [1.5 punts]
 
 En el fitxer persones.txt conté la información de persones de diferentes edats i sense cap ordre. El format del fitxer és <DNI Edat>.
 
 a)    Implementeu un mètode per llegir el fitxer i omplir una llista de manera que primer apareguin els menors (0-16 anys), després les persones de les edats majors que 65 anys i al final les persones de les edats entres 16 – 65 anys.
 b)    Implementeu un programa principal per cridar el mètode implementat i escriure la llista de persones en ordre demanat.
 
 Notes:
 1.    Es valorarà l’eficiència. Cal utilizar una sola llista.
 2.    Si feu que les persones de les tres segments d’edats estiguin ordenades per edats, el problema avaluarà a 1.75 punts.
 */

#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

struct Persona{
    string DNI;
    int edat;
    
    Persona(){}
    
    Persona(string pDNI, int pEdat)
    {
        DNI = pDNI;
        edat = pEdat;
    }
    
    Persona(const Persona& P)
    {
        DNI = P.DNI;
        edat = P. edat;
    }
    
    Persona& operator = (const Persona& P)
    {
        if (this != &P)
        {
            DNI = P.DNI;
            edat = P.edat;
        }
        return (*this);
    }
    
    friend bool operator < (const Persona& P1,const Persona& P2)
    {
        return P1.edat < P2.edat;
    }
    
    friend ostream& operator << (ostream& os, const Persona& P)
    {
        os << "DNI: " << P.DNI << " Edat: " << P.edat << endl;
        
        return os;
    }
    
};

//it apunta al primer element del segment [16,65]
void LlistaPersones(ifstream& fpersones, list<Persona>& LP, list<Persona>::iterator it)
    {
        string DNI;
        int edat;
        
        //Llegim les dades de la 1a persona
        fpersones >> DNI >> edat;
        //Creem l'objecte
        Persona P(DNI,edat);
        //Inserim en la llista
        LP.push_back(P);
        //Inicialitzem l'iterador
        if (P.edat < 16)
        {
            it = LP.end();
        }
        else if (16 <= P.edat and P.edat <= 65)
        {
            it = LP.begin();
        }
        else //major que 65
        {
            it = LP.begin();
        }
        
        while (fpersones >> DNI >> edat)
        {
            Persona P(DNI,edat);
            if (P.edat < 16)//inserim al principi, no afecta l'iterador
            {
                LP.push_front(P);
            }
            else if (16 <= P.edat and P.edat <= 65) //inserim al final, , no afecta l'iterador
            {
                LP.push_back(P);
            }
            else //entre 16 i 65, afecta l'iterador
            {
                it = LP.insert(it, P);
            }
        }
        
    }
    
void escriure(list<Persona>& LP)
{
    list<Persona>::iterator it;
    for (it = LP.begin(); it != LP.end(); it++)
    {
        cout << (*it);
    }
}

int main() {
    
    ifstream fpersones("/Users/fatosxhafa/Documents/ProgsC++/PersonesPerEdats/persones.txt");
    
    list<Persona> LP;
    list<Persona>::iterator it;
    
    LlistaPersones(fpersones, LP, it);
    
    
    cout << "=== Lista (sense els segments ordenats internament) ===" << endl;
    escriure(LP);
    

    return 0;
}
