//
//  main.cpp
//  ProgrControlAccessEdificis
//
//  Created by Fatos Xhafa on 13/04/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 Implementeu un programa main que:
• Mantingui
a. un vector de portes
b. un vector d’empleats
• Ofereixi un menú d’opcions:
a. Entra: pel DNI d’un empleat i el codi d’una porta, indica si l’empleat pot entrar o no. Per poder entrar, la porta ha d’estar habilitada, l’empleat no ha d’estar bloquejat, el seu permís no ha caducat al dia actual i el seu nivell de permís és superior o igual al nivell prioritat de la porta.
b. Modifica permís: pel DNI d’un empleat, incrementa el seu permís al nivell següent o el baixa a l’anterior.
c. Bloqueja empleat: amb el DNI d’un empleat, el bloqueja a efectes d’entrada a qualsevol porta.
d. Llistat empleats: pel DNI d’un empleat, escrigui un llistat de totes les portes on pot entrar
e. Llistat de portes: pel codi d’una porta, escrigui un llistat de tots els empleats que hi poden entrar.
 */

//  ControlAccesEdifici
//
//  Created by Fatos Xhafa on 13/04/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 ENUNCIAT –APARTAT 1
Les entrades en els edificis de les empreses, universitats, etc. es controlen cada vegada més de forma automàtica. Per això, les portes estan equipades amb sistemes de lectura de targetes per permetre l’entrada de persones que tenen permís per entrar.
Implementeu un programa pel control d’entrada dels empleats en un edifici.
PHASE 1: Lliureu la solució de l’apartat1 a la tasca corresponent dins el termini.
[5 punts, 40 minuts]
Definiu una tupla Porta que manté les següents dades:
• Codi porta
• Nivell Prioritat (un enter, 1-bàsic, 2-alt, 3-admin) que s’estableix per la porta
• Estat (bool: habilitada per entrar amb permís o inhabilitada)
Implementeu una classe Empleat que manté les següents dades
• DNI
• Nivell permis (0-bloquejat, 1-bàsic, 2-alt, 3-total) que s’estableix per l’empleat
• Data caducitat (cal utilitzar la classe Data que ja teniu implementada amb operadors).
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Definiu una tupla Porta
struct Porta{
    int codip; //Codi porta
    int nvprioritat; //Nivell Prioritat (un enter, 1-bàsic, 2-alt, 3-admin) que s’estableix per la porta
    bool estat; //Estat (bool: habilitada per entrar amb permís o inhabilitada)
    
    friend ostream& operator << (ostream& os,const Porta& P)
    {
        os << "Porta:" << endl;
        os << "------------------" << endl;
        os << "Codi: " << P.codip << endl;
        os << "Nivell Prioritat: " << P.nvprioritat << endl;
        (os << "Estat: " << (P.estat)) ? "Habilitada" : "Inhabilitada";
        
        return os;
        
    }
};

//Classe Data
//  Created by Fatos Xhafa on 18/03/2020.
//  Copyright © 2020 Fatos Xhafa. All rights reserved.

class Data{
    
    int dia, mes, any;
    
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
    bool de_traspas(int any) const
    {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
    
    //Consultar dies d'un mes i any donats. Mètode privat. Només s'utilitzarà en la classe
    int dias_mes(int mes, int any) const
    {
            int dies = 31;
            if (mes == 4 or mes == 6 or mes == 9 or mes == 11) {
                dies = 30;
            }
            else if (mes == 2) {
                if (de_traspas(any)) {
                    dies = 29;
                }
                else {
                    dies = 28;
                }
            }
            return dies;
        }
    
    //Comptar els dies des d'1 de gener fins al mes (inclòs) de una data donada
    int compta_dias() const
    {
        int sd = 0; //suma de dies
        for (int i = 1; i<= mes; i++)
        {
            sd = sd + dias_mes(i,any);
        }
        return sd;
    }
    //Diferencia de dies entre dues dates, la data D i la que s'està construint
    int dif_dias(const Data& D) // se suposa que les dates són del mateix any
    {
        //comptem els dies fins el mes (inclòs) i restem els dies que sobren del mes
        return ((D.compta_dias()-(dias_mes(D.mes,D.any)-D.dia)) - (compta_dias()-(dias_mes(mes,any)-dia)));
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
    
    //Diferencia de dies entre dues dates, la data D i la que s'està construint
    int operator - (const Data& D) // se suposa que les dates són del mateix any
    {
        //comptem els dies fins el mes (inclòs) i restem els dies que sobren del mes
        return ((compta_dias()-(dias_mes(mes,any)-dia)) -(D.compta_dias()-(dias_mes(D.mes,D.any)-D.dia)));
    }
    
    //Comparar dues dates <
    friend bool operator < (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia < d2.any*10000+d2.mes*100+d2.dia);
    }
    
    //Comparar dues dates >
    friend bool operator > (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia > d2.any*10000+d2.mes*100+d2.dia);
    }
    
    //Comparar dues dates ==
    friend bool operator == (Data& d1, Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia == d2.any*10000+d2.mes*100+d2.dia);
    }
    
    //Llegir una data per canal d'entrada
    friend istream& operator >> (istream& is, Data& D)
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


//Implementeu una classe Empleat
class Empleat{
    string DNI;
    int nvpermis; //Nivell permis (0-bloquejat, 1-bàsic, 2-alt, 3-total) que s’estableix per l’empleat
    Data datacad; //Data caducitat (cal utilitzar la classe Data que ja teniu implementada amb operadors).
    
public:
    Empleat(){} //constructor per defecte
    //constructor amb paràmetres
    Empleat(string pDNI, int pNvpermis, Data& datac)
    {
        DNI = pDNI;
        nvpermis = pNvpermis;
        datacad = datac;
    }
    //constructor de còpia.
    Empleat(const Empleat& E)
    {
        DNI = E.DNI;
        nvpermis = E.nvpermis;
        datacad = E.datacad;
    }
    //Tres mètodes consultors: un per cada camp
    string getDNI() const
    {
        return DNI;
    }
    int getNvpermis() const
    {
        return nvpermis;
    }
    
    Data getDataCad() const
    {
        return datacad;
    }
    
    bool bloquejat() const
    {
        return nvpermis == 0;
    }
    //Mètode modificador: per modificar el nivell de permís, del nivell actual al següent (incrementar) o a l’anterior (baixar)
    
    bool incrPermis()
    {
        if (nvpermis < 3)
        {
            nvpermis++;
            return true;
        }
        return false;
    }
    
    bool dcrPermis()
    {
        if (nvpermis  > 0)
        {
            nvpermis--;
            return true;
        }
        return false;
    }
    bool permisCaducat()
    {
        Data data;
        return datacad < data; //true si ha caducat
    }
    
    //per canviar la data de caducitat incrementant-la amb una quantitat de dies.
    void incrDataCad(int dies)
    {
        datacad.incrementaData(dies);
    }
    
    void bloqueja()
    {
        nvpermis = 0;
    }
    
    //Quatre operadors: =, <=, >> i <<. Un empleat E1 <= E2 en cas que el nivell de permís de E1 és <= que el nivell de permís de E2.
    
    //Operador =
    Empleat& operator = (const Empleat& E)
    {
        if (this != &E)
        {
            DNI = E.DNI;
            nvpermis = E.nvpermis;
            datacad = E.datacad;
        }
        return (*this);
    }
    //Operador ==
    friend bool operator == (const Empleat& E1, const Empleat& E2)
    {
        return (E1.DNI == E2.DNI);
    }
    //Operador <=
    friend bool operator <= (const Empleat& E1, const Empleat& E2)
    {
        return (E1.nvpermis <= E2.nvpermis);
    }
    //Operador >>
    friend istream& operator >> (istream& is, Empleat& E)
    {
        cout << "Introdueix les dades de l'empleat: DNI, Nivell permis, data caducitat dd/mm/aaaa" << endl;
        is >> E.DNI >> E.nvpermis >> E.datacad;
        
        return is;
    }
    //Operador <<
    friend ostream& operator << (ostream& os, const Empleat& E)
    {
        os << "Les dades de l'empleat són:" << endl;
        os << "---------------------------" << endl;
        os << "DNI: " << E.DNI << endl;
        os << "Nivell permís: " << E.nvpermis << endl;
        os << "Data caducitat: " << E.datacad << endl;
        
        return os;
    }
    
};
    
void menu(int& opc)
{
    cout << "MENÚ D'OPCIONS: Escull una opció." << endl;
    cout << "1. Entra a l'edifici" << endl;
    cout << "2. Modifica permís empleat" << endl;
    cout << "3. Bloqueja empleat" << endl;
    cout << "4. LListat portes d'empleat" << endl;
    cout << "5. Llistat empleats d'una porta" << endl;
    cout << "6. Finalitzar!" << endl;
    cin >> opc;
    while (opc < 1 or opc > 6)
    {
        cout << "Opció incorrecte. Torna a escollir una opció:" << endl;
    cin >> opc;
            
    }
}
    
void llegir_portes(ifstream& fportes,vector<Porta>& VP)
{
    int codip;
    int nvprioritat;
    int habil; // 0/1
    Porta P;
    
    while (fportes >> codip >> nvprioritat >> habil)
    {
        P.codip = codip;
        P.nvprioritat = nvprioritat;
        if (habil)
        {
            P.estat = true;
        }
        else
        {
            P.estat = false;
        }
        VP.push_back(P);
    }
}

void llegir_empleats(ifstream& fempleats,vector<Empleat>& VE)
{
    string DNI;;
    int nvpemis;;
    string datcad; // 03/07/2020
    Empleat E;
        
    while (fempleats >> DNI >> nvpemis >> datcad)
        {
            Data datacad(datcad); //es crea la data
            Empleat E(DNI,nvpemis,datacad);
            VE.push_back(E);
        }
    }
    
    int cerca(const vector<Porta> VP, int cp)
    {
        for (int i = 0; i < VP.size(); i++)
        {
            if (VP[i].codip == cp)
            {
                return i; //la posició de la porta amb codi cp
            }
        }
        return -1; //no existeix la porta amb codi cp
    }
    
    int cerca(const vector<Empleat> VE, string DNI)
    {
        for (int i = 0; i < VE.size(); i++)
        {
            if (VE[i].getDNI() == DNI)
            {
                return i; //la posició de la porta amb codi cp
            }
        }
        return -1; //no existeix la porta amb codi cp
    }

int main()
{
    vector<Porta> VP; //un vector de portes
    vector<Empleat> VE; //un vector d’empleats
    
    ifstream fportes("/Users/fatosxhafa/Documents/ProgsC++/ProgrControlAccessEdificis/portes.txt");
    
    ifstream fempleats("/Users/fatosxhafa/Documents/ProgsC++/ProgrControlAccessEdificis/empleats.txt");
    
    //Carreguem dades
    llegir_portes(fportes, VP);
    llegir_empleats(fempleats, VE);
        
    cout << "Hi ha " << VP.size() << " portes" << endl;
    cout << "Hi ha " << VE.size() << " empleats" << endl;

    
    int opc;
    menu(opc);
            
    while (1 <= opc and opc <= 5)
    {
    switch (opc)
        {
        case 1: //entrar a edifici DNI, porta
            {
                cout << "Entra a l'edifici: " << endl;
                //1. Llegim dades de l'empleat i la porta
                cout << "DNI? (p.ex. 23456711A)";
                string DNI;
                cin>> DNI;
                //cerquem la posició de l'empleat
                int posempl = cerca(VE, DNI);
                cout << "Codi porta? (p.ex. 23) ";
                int cp;
                cin>> cp;
                //cerquem la pos de la porta
                int posporta = cerca(VP, cp);
                //si existeix empleat i porta...
                if (posempl != -1 and posporta != -1)
                {
                    //mirem si empleat pot entrar a la porta
        
                    if (VP[posporta].estat and !VE[posempl].bloquejat() and !VE[posempl].permisCaducat() and VP[posporta].nvprioritat <= VE[posempl].getNvpermis())
                    {
                        cout << "Empleat ha entrat! " << endl;
                    }
                    else
                    {
                        cout << "Accés denegat! " << endl;

                    }
                }
                else if (posempl == -1)
                {
                    cout << "Empleat no existeix! " << endl;
                }
                else if (posporta == -1)
                {
                    cout << "Porta no existeix! " << endl;
                }
                break;
            }
        case 2: //Modifica permís
            {
                //Llegim dades de l'empleat i la porta
                cout << "DNI? (p.ex. 23456711A)";
                string DNI;
                cin>> DNI;
                //cerquem la posició de l'empleat
                int posempl = cerca(VE, DNI);
                if (posempl != -1)
                {
                    cout << "El nivell del permís de l'empleat és: " << VE[posempl].getNvpermis() << endl;
                    cout << "Vols incrementar o decrementar el seu permís? (+/-)" << endl;
                    char resp;
                    cin >> resp;
                    if (resp == '+')
                    {
                        VE[posempl].incrPermis();
                    }
                    else if (resp == '-')
                    {
                        VE[posempl].dcrPermis();
                    }
        cout << "Permís modificat (si fora el cas)!" << endl;
                }
                else
                {
                    cout << "Empleat no existeix! " << endl;
                }
                break;
            }
        case 3: //Bloqueja empleat
            {
                //Llegim dades de l'empleat i la porta
                cout << "DNI? (p.ex. 23456711A)";
                string DNI;
                cin>> DNI;
                //cerquem la posició de l'empleat
                int posempl = cerca(VE, DNI);
                if (posempl != -1)
                {
                    VE[posempl].bloqueja();
                }
                else
                {
                    cout << "Empleat no existeix! " << endl;
                }
                    break;
            }
        case 4: //Llistat portes d'empleat
            {
                //Llegim dades de l'empleat
                cout << "DNI? (p.ex. 98897667B)";
                string DNI;
                cin>> DNI;
                //cerquem la posició de l'empleat
                int posempl = cerca(VE, DNI);
                if (posempl != -1)
                {
                    for (int i = 0; i < VP.size(); i++)
                    {
                        if (VE[posempl].getNvpermis() >= VP[i].nvprioritat)
                        {
                            cout << VP[i] << endl;
                        }
                    }
                }
                else
                {
                    cout << "Empleat no existeix! " << endl;
                }
                break;
            }
        case 5: //Llistat de portes
            {
                cout << "Codi porta? (p.ex. 13) ";
                int cp;
                cin>> cp;
                //cerquem la pos de la porta
                int posporta = cerca(VP, cp);
                if (posporta != -1)
                {
                    for (int i = 0; i < VE.size(); i++)
                    {
                        if (VE[i].getNvpermis() >= VP[posporta].nvprioritat)
                        {
                            cout << VE[i] << endl;
                        }
                    }
                }
                else
                {
                    cout << "Porta no existeix! " << endl;
                }
                break;
            }
        default:
            {
                cout << "Programa finalitzat!" << endl;
            }
        }
            menu(opc);
    }

    
    
    return 0;
}

