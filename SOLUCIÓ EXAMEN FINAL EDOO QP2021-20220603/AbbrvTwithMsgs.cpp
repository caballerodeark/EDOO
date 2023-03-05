//
//  main.cpp
//  AbbrvTwithMsgs
//
//  Created by Fatos Xhafa on 06/06/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 Problema 2 [3 punts][Temps 45 min.]
 
 El llenguatge utilitzat en les xarxes social inclou cada vegada més abreviacions de paraules o d’expressions de paraules. Per exemple, en anglès s’utilitzen, PLZ per indicar Please o YOYO per dir You are on your own. Un problema que ha sorgit amb aquest “nou” llenguatge és que per fer processament i anàlisi de missatges, tweets, etc., totes aquestes abreviacions introdueixen un biaix (soroll) en el text.
 
 Es demana que implementeu un mètode que:
 
 •    donat un fitxer de text scriptum.txt, que conté les abreviacions i les seves definicions <abrv,definició>, com ara <YOYO,You are on your own>
 •    donat un fitxer twith.txt, que conté missatges de text originals de la plataforma TWITH en la qual els usuaris utilitzen abreviacions a gust
 
 calculi
 
 •    un nou fitxer del text original però corregit, corrigendum.txt, on cada abreviació s’hagi substituït per la seva definició segons el scriptum.txt.
 •    un fitxer freqs.txt de format <abrv,freq> on freq és la freqüència de l’abreviació (quantes vegades s’ha substituït en el text l’abreviació).
 
 Cal tenir present que:
 •    En el text original pot haver abreviacions encara no recollides en el scriptum.txt; aquestes abreviacions es quedarien tal com venen en el text original.
 •    La llista de les abreviacions és ben llarga i el text original a corregir pot ser molt llarg.
 
 Es valorarà l’eficiència de la implementació.

 */

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct abrv{
    string def_dicc;
    int freq;
    
    abrv(){freq = 0;}
    abrv(string pDef_dicc, int pFreq)
    {
        def_dicc = pDef_dicc;
        freq = pFreq;
    }
    abrv(const abrv& a)
    {
        def_dicc = a.def_dicc;
        freq = a.freq;
    }
    
    abrv& operator = (const abrv& a)
    {
        if (this != &a)
        {
            def_dicc = a.def_dicc;
            freq = a.freq;
        }
        return (*this);
    }
    
    friend ostream& operator << (ostream& os, const abrv& a)
    {
        os << a.def_dicc << ' ' << a.freq << endl;
        
        return os;
    }
};

typedef pair<string,abrv> entrada_dicc;

//Acció per crear el map de les parelles abrv i les seves definicions, i freqüència a zero
void crea_dicc(ifstream& fscriptum, map<string, abrv>& mabrv)
{
    string a, def;
    while (fscriptum >> a)
    {
        //llegim def amb getline
        getline(fscriptum,def);
        abrv ab(def,0);
        entrada_dicc ed(a,ab);
        mabrv.insert(ed);
    }
        
}
void processar(ifstream& ftwith, map<string, abrv>& mabrv, ofstream& fcorrigendum)
{
    //Llegim el fitxer original ftwith a corregir i el processem
    string par; //una paraula del text a corregir
    while (ftwith >> par)
    {
        map<string, abrv>:: iterator it = mabrv.find(par);
        if (it != mabrv.end()) //existeix PLZ
        {
            abrv ab = it -> second;
            fcorrigendum << ab.def_dicc << ' ';
            it->second.freq++;
            
        }
        else
        {
            fcorrigendum << par << ' ';
        }
    }
    
}
    
void freqs(map<string,abrv>& mabrv, ofstream& ffreqs)
{
    map<string,abrv>::iterator it = mabrv.begin();
    while (it != mabrv.end())
    {
        if ((it -> second).freq != 0)
        {
            ffreqs << "Abrev: " << it -> first << " Freq: " << (it -> second).freq << endl;
        }
        it++;
    }
}

int main() {
    map<string, abrv> mabrv;
    ifstream fscriptum("/Users/fatosxhafa/Documents/ProgsC++/AbbrvTwithMsgs/scriptum.txt");
    
    crea_dicc(fscriptum, mabrv);
    
    ifstream ftwith("/Users/fatosxhafa/Documents/ProgsC++/AbbrvTwithMsgs/twith.txt");
    
    ofstream fcorrigendum("/Users/fatosxhafa/Documents/ProgsC++/AbbrvTwithMsgs/corrigendum.txt");

    processar(ftwith, mabrv, fcorrigendum);
    
    ofstream ffreqs("/Users/fatosxhafa/Documents/ProgsC++/AbbrvTwithMsgs/freqs.txt");

    freqs(mabrv, ffreqs);
    
 
    return 0;
}
