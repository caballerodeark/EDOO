#include <list>
#include <fstream>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <list>
#include <string>

using namespace std;

class Noticia //Part 1: Classe Notícia
{

    string titol, text, ambit;
    int horOc, datOc, horEnt, datEnt;

    public:
    //Constructors:

    Noticia() //Per defecte
    {
        titol = "";
        text = "";
        ambit = "";
        horOc = 0;
        datOc = 0;
        horEnt = 0;
        datEnt = 0;
    }

    Noticia(string titol, string text, int datOc, int horOc, int datEnt, int horEnt, string ambit) //Per paràmetres
    {
        this -> titol = titol;
        this -> text = text;
        this -> datOc = datOc;
        this -> horOc = horOc;
        this -> datEnt = datEnt;
        this -> horEnt = horEnt;
        this -> ambit = ambit;
    }

    Noticia(const Noticia& C) //De cópia
    {
        this -> titol = C.titol;
        this -> text = C.text;
        this -> datOc = C.datOc;
        this -> horOc = C.horOc;
        this -> datEnt = C.datEnt;
        this -> horEnt = C.horEnt;
        this -> ambit = C.ambit;
    }

    //Métodes consultors

    string gettitol()
    {
        return titol;
    }

    string gettext()
    {
        return text;
    }

    int gethorOc()
    {
        return horOc;
    }

    int getdatOc()
    {
        return datOc;
    }

    int gethorEnt()
    {
        return horEnt;
    }

    int getdatEnt()
    {
        return datEnt;
    }

    //Métodes modificadors

    void settitol(string titol)
    {
        this -> titol = titol;
    }

    void settext(string text)
    {
        this -> text = text;
    }

    void sethorOc(int horOc)
    {
        this -> horOc = horOc;
    }

    void setdatOc(int datOc)
    {
        this -> datOc = datOc;
    }

    void sethorEnt(int horEnt)
    {
        this -> horEnt = horEnt;
    }

    void setdatEnt(int datEnt)
    {
        this -> datEnt = datEnt;
    }

    void setambit(string ambit)
    {
        this -> ambit = ambit;
    }

    //Operadors:

    friend bool operator==(const Noticia& P1, const Noticia& P2)
    {
        if (P1.titol == P2.titol && P1.text == P2.text && P1.horOc == P2.horOc && P1.datOc == P2.datOc && P1.horEnt == P2.horEnt && P1.datEnt == P2.datEnt && P1.ambit == P2.ambit)
        {
            return true;
        }
        else return false;
    }

    friend bool operator!=(const Noticia& P1, const Noticia& P2)
    {
        if (P1.titol == P2.titol && P1.text == P2.text && P1.horOc == P2.horOc && P1.datOc == P2.datOc && P1.horEnt == P2.horEnt && P1.datEnt == P2.datEnt && P1.ambit == P2.ambit)
        {
            return false;
        }
        else return true;
    }

    friend bool operator<=(const Noticia& P1, const Noticia& P2)
    {
        if(P1.datOc <= P2.datOc) return true;
        else return false;
    }

    friend bool operator>=(const Noticia& P1, const Noticia& P2)
    {
        if(P1.horOc <= P2.horOc) return true;
        else return false;
    }

    friend bool operator<(const Noticia& P1, const Noticia& P2)
    {
        if(P1.datOc < P2.datOc) return true;
        else return false;
    }
    
    friend bool operator>(const Noticia& P1, const Noticia& P2)
    {
        if(P1.datOc > P2.datOc) return true;
        else return false;
    }

    friend bool operator<=(const Noticia& P1, const int& T)
    {
        if(P1.datOc <= T) return true;
        else return false;
    }

    friend bool operator>=(const Noticia& P1, const int& T)
    {
        if(P1.horOc <= T) return true;
        else return false;
    }

    friend bool operator<(const Noticia& P1, const int& T)
    {
        if(P1.datOc < T) return true;
        else return false;
    }
    
    friend bool operator>(const Noticia& P1, const int& T)
    {
        if(P1.datOc > T) return true;
        else return false;
    }

    Noticia operator=(Noticia& C)
    {
        this -> titol = C.titol;
        this -> text = C.text;
        this -> datOc = C.datOc;
        this -> horOc = C.horOc;
        this -> datEnt = C.datEnt;
        this -> horEnt = C.horEnt;
        this -> ambit = C.ambit;
    }
};

class AgendaNoticies
{

    list<Noticia> recents, antigues;

    public:

    AgendaNoticies() //Per defecte
    {
        recents.clear();
        antigues.clear();
    }

    AgendaNoticies(list<Noticia> recents, list<Noticia> antigues) //Per paràmetres
    {
        this -> recents = recents;
        this -> antigues = antigues;
    }

    AgendaNoticies(const AgendaNoticies& C) //De cópia
    {
        this -> recents = C.recents;
        this -> antigues = C.antigues;
    }

    //Métodes consultors

    list<Noticia> getrecents()
    {
        return recents;
    }

    list<Noticia> getantigues()
    {
        return antigues;
    }

    Noticia ultima()
    {
        int diamax=0;
        Noticia candidats,mantiga;
        list<Noticia> mateixdia;
        for(list<Noticia> :: iterator it = antigues.begin(); ; it++)
        {

        }
        return mantiga;
    }

    void llistarrecents()
    {

    }


}; 