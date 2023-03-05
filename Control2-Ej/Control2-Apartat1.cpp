#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <locale>
#include <time.h>

using namespace std;

class Time
{

    int h, m, s;


    //API
    public:
    //Constructor per defecte
    Time()
    {
        h=00; m=00; s=00;
    }

    //Constructor amb par�metres
    Time(int hour, int minutes, int seconds)
    {
        h = hour;
        m = minutes;
        s = seconds;
    }
    //Constructor de c�pia
    Time(const Time& T)
    {
        h = T.h;
        m = T.m;
        s = T.s;
    }
    void AutomaticTime()
    {
        struct tm* RealTime;
        time_t t;
        time( &t );
        RealTime = localtime( &t );
        h = RealTime -> tm_hour;
        m = RealTime -> tm_min;
        s = RealTime -> tm_sec;
    }
    double CalculeHour()
    {
        return (h*60.0 + m)/60.0;
    }
    int CalculeMinutes()
    {
        return (h*60 + m);
    }
    int CalculeSeconds()
    {
        return (h*3600 + m*60 + s);
    }
    //M�tode per consultar dades
    int getHora()
    {
        return h;
    }
    int getMinutes()
    {
        return m;
    }
    int getSeconds()
    {
        return s;
    }
    void setHora(int h)
    {
        this->h=h;
    }
    void setMin(int m)
    {
        this->m=m;
    }
    void setSeg(int s)
    {
        this->s=s;
    }
    friend ostream& operator <<(ostream& os, Time& T)
    {
        os<< T.h << T.m << T.s << endl;
        return os;
    }
};

struct Persona
{
    string INS;
    Time Hassig;
    bool ocupat;
};

class AnaliticaCAP
{
    queue<Persona> Cola;
    Persona Boxes[10]; 

    public:
    AnaliticaCAP();
    AnaliticaCAP(queue<Persona> Cola)
    {
        this -> Cola = Cola;
    }
    AnaliticaCAP(ifstream& Datos)
    {
        Persona muchotexto;
        int h,m,s;
        while(Datos>>muchotexto.INS>>h>>m>>s)
        {
            muchotexto.Hassig.setHora(h);
            muchotexto.Hassig.setMin(m);
            muchotexto.Hassig.setSeg(s);
            Cola.push(muchotexto);
        }
    }
    //Consultors;
    //Metodes get
    queue<Persona> getCola()
    {
        return Cola;
    }
    vector<Persona> getBoxes()
    {
        vector<Persona> P;
        for(int k=0; k<10; k++)
        {
            P.push_back(Boxes[k]);
        }
    }
    //Retornar primera persona
    Persona getPersona1(bool haypers)
    {
        if(!Cola.empty())
        {
            return Cola.front();
            haypers=true;
        }
        else haypers=false;
    }
    //Consultar si n'hi queden persones en cua
    bool haypers()
    {
        if(Cola.empty())
        {
            return false;
        }
        else return true;
    }
    //Consultar primer box lliure
    int Boxlliure()
    {
        int h=10,s=59,m=59,numbox,numboxlibre;
        bool haylibre=false;
        for(int k=0; k<10 || haylibre; k++)
        {
            if(!Boxes[k].ocupat)
            {
                haylibre=true;
                numbox=k++;
            }
        }
        if(haylibre)return numbox;
        else
        {
            for(int k=0;k<10;k++)
            {
                if(Boxes[k].Hassig.getHora()<h)
                {
                    h=Boxes[k].Hassig.getHora();
                    m=Boxes[k].Hassig.getMinutes();
                    s=Boxes[k].Hassig.getSeconds();
                    numbox=k++;
                }
                else if(Boxes[k].Hassig.getHora()==h)
                {
                    if(Boxes[k].Hassig.getMinutes()<m)
                    {
                        h=Boxes[k].Hassig.getHora();
                        m=Boxes[k].Hassig.getMinutes();
                        s=Boxes[k].Hassig.getSeconds();
                        numbox=k++;
                    }
                    else if(Boxes[k].Hassig.getMinutes()==m)
                    {
                        if (Boxes[k].Hassig.getSeconds()<s)
                        {
                            h=Boxes[k].Hassig.getHora();
                            m=Boxes[k].Hassig.getMinutes();
                            s=Boxes[k].Hassig.getSeconds();
                            numbox=k++;
                        }
                    }   
                }
            }
            return numbox;
        }
    }
    //Metodes modificadors
    //Metodes set
    void setCola(queue<Persona> Cola)
    {
        this->Cola=Cola;
    }
    //Omplir cua amb fitxer
    void omplecua(ifstream& Dades)
    {
        Persona muchotexto;
        int h,m,s;
        while(Dades>>muchotexto.INS>>h>>m>>s)
        {
            muchotexto.Hassig.setHora(h);
            muchotexto.Hassig.setMin(m);
            muchotexto.Hassig.setSeg(s);
            Cola.push(muchotexto);
        }
    }
    //Assignar 10 primeres persones
    void assig10pers()
    {
        for(int k=0; k<10; k++)
        {
            Boxes[k]=Cola.front();
            Boxes[k].ocupat=true;
            Cola.pop();
        }
    }
    //Assignar primera persona de la cua a box lliure
    void assigpers()
    {
        int lliure=Boxlliure();
        Boxes[lliure--]=Cola.front();
        Boxes[lliure--].ocupat=true;
        Cola.pop();
    }
    //Cambiar de lliure a ocupat
    void canviLliureOcupat(int numbox)
    {
        Boxes[numbox--].ocupat=true;
    }
    //Cambiar de lliure a ocupat
    void canviOcupatLliure(int numbox)
    {
        Boxes[numbox--].ocupat=false;
    }
    //Si no presentat cancel·la assignació
    void cancel()
    {
        Cola.pop();
    }
    //Operadors
    //=
    void operator=(const AnaliticaCAP& C)
    {
        this->Cola=C.Cola;
    }
    //<<
    friend ostream& operator<<(ostream& os, AnaliticaCAP& C)
    {
        queue<Persona> p=C.Cola;
        for(int k=0; k<10; k++)
        {
            if(C.Boxes[k].ocupat)
            {
                os<<"Box "<<k<<": "<<C.Boxes[k].INS<<endl;;
            }
            else os<<"Box "<<k<<": Lliure"<<endl;
        }
        os<<"Persones en cua:"<<endl;
        if(p.empty()) os<<"Cola buida"<<endl;
        else
        {
            for(int k=0; k<p.size();k++)
            {
                os<<p.front().INS<<" "<<p.front().Hassig.getHora()<<":"<<p.front().Hassig.getMinutes()<<p.front().Hassig.getSeconds()<<endl;
                p.pop();
            }
        }
    }
    //>>
    friend istream& operator>>(istream& is, AnaliticaCAP& C)
    {
        int h,m,s;
        string INS;
        Persona lectura;
        while(is>>lectura.INS>>h>>m>>s)
        {
            lectura.Hassig.setHora(h);
            lectura.Hassig.setMin(m);
            lectura.Hassig.setSeg(s);
            C.Cola.push(lectura);
        }
    }
};

