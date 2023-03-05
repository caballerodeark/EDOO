//
//  main.cpp
//  VehiclesHerencia
//
//  Created by Fatos Xhafa on 16/05/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 IMPLEMENTACIÓ DE CLASSES VIA HERÈNCIA
 Vehicle:
    NumBastidor (NIV)
    Matricula
    Data finalització assegurança
    Data finalització ITV
    Velocitat màxima permesa ( -1 )
 Autobus:
    Les dades d’un vehice //aquestes no les repeteixo
    Capacitat passatgers
    TipusServei (urbà, etc.)
 Camion:
    Les dades d’un vehice //aquestes no les repeteixo
    TARA
    Tipus mercaderia, perrillosa?
 Cotxe:
    Les dades d’un vehice ////aquestes no les repeteixo
    Etc.

*/

#include <iostream>
using namespace std;

//
//  main.cpp
//  Data
//
//  Created by Fatos Xhafa on 17/03/2020.
//  Copyright © 2020 Fatos Xhafa. All rights reserved.
//

//Completeu amb d'altres operadors
//Podeu embellir el codi

#include <iostream>
#include<time.h>

using namespace std;

class Data
{
    
    int dia, mes, any;
    
    //Comprovar si la data pertany a un any bissest. Mètode privat. S'utilitza només en la classe
    //Hi ha un altre mètode public amb el mateix nom però sense el paràmetre any.
    bool de_traspas(int any) {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
    
    //Consultar dies d'un mes i any donats. Mètode privat. S'utilitza només en la classe
    int dias_mes(int mes, int any) 
    {
        int dies = 31;
        if (mes == 4 or mes == 6 or mes == 9 or mes == 11) 
        {
            dies = 30;
        }
        else if (mes == 2) 
        {
            if (de_traspas(any) == true) 
            {
                dies = 29;
            }
            else 
            {
                dies = 28;
            }
        }
        return dies;
    }
    
    public:
    
    //Constructor per defecte amb la data actual, que dóna el sistema, llibreria time.h
    Data()
    {
        time_t t; //time_t és una tupla de temps (dia, mes any, hora, mins, segs) definit en time.h
        time( &t );
        struct tm* info = localtime( &t );
        dia = info -> tm_mday;
        mes = info -> tm_mon + 1;
        any = 1900+ info -> tm_year; // l'any es comença a comptar a partir del 1900
    }
    
    //Constructor amb tres paràmetres enters
    Data(int d, int m, int a)
    {
        dia=d;
        mes=m;
        any=a;
    }
    
    //Constructor amb un paràmetre enter ddmmaaaa
    Data(int ddmmaaaa)
    {
        dia=ddmmaaaa/1000000;
        mes=(ddmmaaaa/10000)%100;
        any=ddmmaaaa%10000;
    }
    
    //Constructor amb un paràmetre string en format dd:mm:aaaa o dd-mm-aaaa
    //stoi és una funció per converir un string (p.ex "12") en un enter (p.ex. 12)
    Data(string sd)
    {
        string c1 = sd.substr (0,2);//el string dels caràcters dd
        dia=stoi(c1);
        string c2 = sd.substr (3,2);//el string dels caràcters mm
        mes=stoi(c2);
        string c3 = sd.substr (6); //el substring de la 6à posició fins al final
        any=stoi(c3);
    }
    
    //Constructor de còpia
    
    Data(const Data& D)
    {
        dia = D.dia;
        mes = D.mes;
        any = D.any;
    }
    
    //Mètodes consultors
    int getDia()
    {
        return dia;
    }
    int getMes()
    {
        return mes;
    }
    int getAny()
    {
        return any;
    }
    
    //Comprovar si la data que s'està construïnt es d'un any de traspàs
    bool de_traspas() 
    {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
    
    //Mètodes modificadors. Se suposa que d, m i a són vàlids
    void setDia (int d)
    {
        dia=d;
    }
    void setMes (int m)
    {
        mes=m;
    }
    void setAny (int a)
    {
        any=a;
    }
    
    //Incrementar la data amb una quantitat de dies
    void incrementaData (int dd)
    {
        dia=dia+dd;
        if (dia > dias_mes(mes, any)) 
        {
            dia = dia-dias_mes(mes,any);
            mes++;
            if (mes > 12) 
            {
                mes = 1;
                any++;
            }
        }
    }
    
    Data& operator = (const Data& D)
    {
        if (this != &D)
        {
            dia = D.dia;
            mes = D.mes;
            any = D.any;
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
    
    //Llegir una data pel canal d'entrada
    friend istream& operator >> (istream& is,Data& D)
    {
        is >> D.dia;
        is >> D.mes;
        is >> D.any;
        
        return is;
    }
    //Escriure una data per canal de sortida dd/mm/aaaa
   friend ostream& operator << (ostream& os, Data d)
    {
        os << "Data: ";
        if (d.dia < 10)
        {
            os << "0";
        }
        os << d.dia <<"/";
        
        if (d.mes < 10)
        {
            os << "0";
        }
        os<< d.mes << "/" << d.any<<endl;
        
        return os;
    }
    
};

class Vehicle{

    string numBastidor; //També anomenat Número d'Identificació Vehicular (NIV)
    string matricula;
    Data dataAsseg;
    Data dataITV;
    int max_vel; //Si no té limit de velocitat, max_vel és el de la via de circulació, no del propi vehicle
    
    public:
    
    Vehicle()
    {
        max_vel = -1; //Si no té limit de velocitat, max_vel és el de la via de circulació, no del propi vehicle
    }
    
    Vehicle(string pNumBastidor,string pMatricula,Data pDataAsseg, Data pDataITV)
    {
        numBastidor = pNumBastidor;
        matricula = pMatricula;
        dataAsseg = pDataAsseg;
        dataITV = pDataITV;
    }
    
    Vehicle(const Vehicle& V)
    {
        numBastidor = V.numBastidor;
        matricula = V.matricula;
        dataAsseg = V.dataAsseg;
        dataITV = V.dataITV;
        max_vel = V.max_vel;
    }
    
    //Mètodes
    string getNumBastidor()
    {
        return numBastidor;
    }
    
    string getMatricula()
    {
        return matricula;
    }
    
    Data getDataAsseg()
    {
        return dataAsseg;
    }
    
    Data getDataITV()
    {
        return dataITV;
    }
    
    int getMaxVel()
    {
        return max_vel;
    }

    //Mètodes modificadors
    void setNumBastidor(string NB)
    {
         numBastidor = NB;
    }
    
    void setMatricula(string M)
    {
        matricula = M;
    }
    
    void setDataAsseg(Data& D)
    {
        dataAsseg = D;
    }
    
    void setDataITV(Data D)
    {
        dataITV = D;
    }
    
    void setMaxVel(int MV)
    {
        max_vel = MV;
    }
    
    //Operadors
    Vehicle& operator = (const Vehicle& V)
    {
        if (this != &V)
        {
            numBastidor = V.numBastidor;
            matricula = V.matricula;
            dataAsseg = V.dataAsseg;
            dataITV = V.dataITV;
            max_vel = V.max_vel;
        }
        return (*this);
    }
    
    friend bool operator == (const Vehicle& V1, const Vehicle& V2)
    {
        return V1.numBastidor == V2.numBastidor;
    }
    
    friend istream& operator >> (istream& is,Vehicle& V)
    {
        is >> V.numBastidor;
        is >> V.matricula;
        is >> V.dataAsseg;
        is >> V.dataITV;
        
        return is;
    }
    
    friend ostream& operator << (ostream& os,const Vehicle& V)
    {
        os << "Bastidor: " << V.numBastidor << endl;
        os << "Matricula:" << V.matricula << endl;
        os << "Assegurança venç: " << V.dataAsseg << endl;
        os << "ITV venç: " << V.dataITV << endl;
        if (V.max_vel != -1)
        {
            os << "Té limit de velocitat" << endl;
            os << "Max velocitat: " << V.max_vel << endl;
        }
        else
        {
            os << "No té limit de velocitat. Apliquen les restriccions de la via!" << endl;
        }
        
        return os;
    }
};
    
class Autobus : public Vehicle
{
    int capacitat;
    string servei;
    
    public:

    Autobus(){} //Crida el constr per defecte de Vehicle
    
    //Constructor amb paràmetres
    Autobus(string pNumBastidor,string pMatricula,Data pDataAsseg, Data pDataITV,int pCapacitat,string pServei):Vehicle(pNumBastidor,pMatricula,pDataAsseg,pDataITV)
    {
        capacitat = pCapacitat;
        servei = pServei;
    }
    
    //Constructor amb paràmetres
    Autobus(Vehicle V,int pCapacitat,string pServei):Vehicle(V)
    {
        capacitat = pCapacitat;
        servei = pServei;
    }
    
    //Constructor de còpia
    //La part del vehicle es crea amb el constructor de còpia del Vehicle, la resta de dades es copien directament
    Autobus(const Autobus& A):Vehicle(A)
    {
        capacitat = A.capacitat;
        servei = A.servei;
    }
    
    //Mètodes
    
    int getCapacitat()
    {
        return capacitat;
    }
    
    string getServei()
    {
        return servei;
    }
    
    void setCapacitat(int pCapacitat)
    {
        capacitat = pCapacitat;
    }
    
    void setServei(string pServei)
    {
        servei = pServei;
    }
    
    Autobus& operator = (const Autobus& A)
    {
        if (this != &A)
        {
            //La part de Vehicle és fa amb l'operador = del Vehicle
            Vehicle::operator = (A);
            capacitat = A.capacitat;
            servei = A.servei;
        }
        
        return (*this);
    }
    
    friend istream& operator >> (istream& is, Autobus& A)
    {
        Vehicle V; //La part vehicle de A
        is >> V;
        int cap;
        string serv;
        is >> cap;
        is >> serv;
        Autobus AB(V,cap,serv);
        
        A = AB;
        
        return is;
    }
    
    friend ostream& operator << (ostream& os, const Autobus& A)
    {
        Vehicle V = (Vehicle) A; //Extrau la part del vehicle de A
        os << "Fitxa del vehicle: " << endl;
        os << "------------------" << endl;
        os << V;
        os << endl;
        os << "Capacitat: " << A.capacitat << endl;
        os << "Tipus de servei: " << A.servei << endl;
        os << "------------------" << endl;
        
        return os;
    }
};

int main()
{
    Autobus A;
    cout << "Introdueix les dades d'un autobus (numBastidor, matricula, dataAsseg, dataITV, capacitat, servei):" << endl;
    cin >> A;
    
    
    if (A.getMaxVel() != -1)
    {
        cout << "Hi ha limit de velocitat pel vehicle" << endl;
    }
    else
    {
        cout << "No hi ha limit de velocitat pel vehicle" << endl;
    }
    
    cout << "Canviem la velocitat max a: ";
    
    A.setMaxVel(100);
    
    cout << A.getMaxVel() << endl;
    
    cout << A << endl;
  
    return 0;
}