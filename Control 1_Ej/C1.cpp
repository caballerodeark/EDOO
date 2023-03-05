#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

class Data
{
    
    int dia, mes, any;
    
    //Comprovar si la data pertany a un any bissest. Mètode privat. Només s'utilitzarà en la classe
    //Hi ha un altre mètode public amb el mateix nom però sense el paràmetre any.
    bool de_traspas(int any) {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
        
    //Consultar dies d'un mes i any donats. Mètode privat. Només s'utilitzarà en la classe
    int dias_mes(int mes, int any) {
            int dies = 31;
            if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
                dies = 30;
            }
            else if (mes == 2) {
                if (de_traspas(any) == true) {
                    dies = 29;
                }
                else {
                    dies = 28;
                }
            }
            return dies;
        }
    
public:
    
    //Constructor per defecte amb la data actual, que dóna el sistema, llibreria time.h
    Data(){
        time_t t; //time_t és una tupla de temps (dia, mes any, hora, mins, segs) definit en time.h
        time( &t );
        struct tm* info = localtime( &t );
        dia = info -> tm_mday;
        mes = info -> tm_mon + 1;
        any = 1900+ info -> tm_year; // l'any es comença a comptar a partir del 1900
    }
    
    //Constructor amb tres paràmetres enters
    Data(int d, int m, int a){
        dia=d;
        mes=m;
        any=a;
    }
    
    //Constructor amb un paràmetre enter ddmmaaaa
    Data(int ddmmaaaa){
        dia=ddmmaaaa/1000000;
        mes=(ddmmaaaa/10000)%100;
        any=ddmmaaaa%10000;
    }
    
    //Constructor amb un paràmetre string en format dd:mm:aaaa o dd-mm-aaaa
    //stoi és una funció per converir un string (p.ex "12") en un enter (p.ex. 12)
    Data(string sd){
        string c1 = sd.substr (0,2);//el string dels caràcters dd
        dia=stoi(c1);
        string c2 = sd.substr (3,2);//el string dels caràcters mm
        mes=stoi(c2);
        string c3 = sd.substr (6); //el substring de la 6à posició fins al final
        any=stoi(c3);
    }
    
    //Constructor de còpia
    Data(const Data& data)
    {
        dia = data.dia;
        mes = data.mes;
        any = data.any;
    }
    
    //Mètodes consultors
    int getDia(){
        return dia;
    }
    int getMes(){
        return mes;
    }
    int getAny(){
        return any;
    }
    
    //Comprovar si la data que s'esta construint és de traspàs
    bool de_traspas() {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
    
    
    //Mètodes modificadors. Se suposa que d, m i a són vàlids
    void setDia (int d){
        dia=d;
    }
    void setMes (int m){
        mes=m;
    }
    void setAny (int a){
        any=a;
    }
    
    //Incrementar la data amb una quantitat de dies
    void incrementaData (int dd){
        dia=dia+dd;
        if (dia > dias_mes(mes, any)) {
            dia = dia-dias_mes(mes,any);
            mes++;
            if (mes > 12) {
                mes = 1;
                any++;
            }
        }
    }
    
    //Operador d'assignació
    Data& operator = (const Data& data)
    {
        if (this != &data)
        {
            dia = data.dia;
            mes = data.mes;
            any = data.any;
        }
        return (*this);
    }
    
    //Comparar dues dates <
    friend bool operator < (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia < d2.any*10000+d2.mes*100+d2.dia);
    }
    
    //Comparar dues dates ==
    friend bool operator == (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia == d2.any*10000+d2.mes*100+d2.dia);
    }
    
    
    //Escriure una data per canal de sortida dd/mm/aaaa
    friend ostream& operator << (ostream& os, Data d)
    {
        os << "Data: ";
        if (d.dia < 10){
            os << "0";
        }
        os << d.dia <<"/";
        
        if (d.mes < 10){
            os << "0";
        }
        os<< d.mes << "/" << d.any<<endl;
        
        return os;
    }
    
};

struct Porta
{
    int codiP;
    int nivprior;
    bool estat;
};

class Empleat
{
    string DNI;
    int nivperm;
    Data datacaducitat;

    public:
    //Constructors:
    Empleat() {} //Per defecte

    Empleat(string pDNI, int pnivperm, Data pdatacaducitat) //Amb parametres
    {
        DNI = pDNI;
        nivperm = pnivperm;
        datacaducitat = pdatacaducitat;
    }

    Empleat(const Empleat& Emp) //De cópia
    {
        DNI = Emp.DNI;
        nivperm = Emp.nivperm;
        datacaducitat = Emp.datacaducitat;
    }

    //Metodes de consulta:
    string getDNI()
    {
        return DNI;
    }
    int getNivperm()
    {
        return nivperm;
    }
    Data getDatacaducitat()
    {
        return datacaducitat;
    }

    //Metodes modificaors:

    bool incrNiv()
    {
        if(nivperm<3)
        {
            nivperm++;
            return true;
        }  
        return false;
    }

    bool dismNiv()
    {
        if(nivperm>0)
        {
            nivperm--;
            return true;
        }
        return false;
    }

    void incrData(int dies)
    {
        datacaducitat.incrementaData(dies);
    }

    //Operadors:

    void operator=(const Empleat& E)
    {
        nivperm = E.nivperm;
    }

    friend bool operator<=(const Empleat& E1, const Empleat& E2)
    {
        if(E1.nivperm <= E2.nivperm) return true; 
    }

    friend istream& operator >>(istream& is, Empleat& E)
    {
        is >> E.DNI >> " " >> E.nivperm >> " " >> E.datacaducitat.getDia() >> "/" >> E.datacaducitat.getMes() >> "/" >> E.datacaducitat.getAny() >> endl;
        return is;
    }



};