//
//  main.cpp
//  RobotOficina
//
//  Created by Fatos Xhafa on 07/06/2021.
//  Copyright © 2021 Fatos Xhafa. All rights reserved.
//

/*
 Problema 3 [5 punts][Temps 1h.]
 
 Els robots s’utilitzen des de fa molts anys. Si bé abans els robots es veien en les fàbriques de cotxes, d’ordinadors, etc., ara els veiem per casa o en les oficines. Es demana que implementeu una classe robot d’oficina, per una empresa, segons aquesta descripció:
 
 •    L’empresa té una planta que és tota una superfície diàfana organitzada en forma d’una matriu, en algunes de les caselles de la qual hi ha punts de treball (cada punt de treball té unes coordenades x, y dins la planta). Se suposa que cada punt de treball té una casella de correu on deixar cartes.
 •    El robot pot desplaçar-se només en horitzontal ... i en vertical ... segons indica l'enunciat
 •    El robot s’utilitza per enviar cartes als punts de treball, sortint de la seva posició d’origen (0,0) carregat amb els sobres, i seguint els punts d’una ruta prèviament fixada, deixant en cada punt el sobre del torn. El robot es pot desplaçar per totes les caselles sense restriccions.
  
 
 La informació (dades) de la classe robot ha d’incloure:
 •    Un identificador (un enter)
 •    La posició actual (x,y) del robot. Definiu-la com un struct Punt.
 •    Una ruta que consta d’un nombre indeterminat de punts, cadascun d’ells amb les seves coordinades. Cal utilitzar memòria dinàmica per una taula de punts.
 •    Una col·lecció de sobres a repartir a les caselles de correu dels punts de la ruta. Definiu un sobre com un struct amb Id, i les coordenades (x,y) del punt de treball. Escolliu l’estructura de dades adequada per la col·lecció de sobres.
 •    No s’ha de mantenir la informació de la graella ni de tots els punts de treball.
 L’API de la classe robot ha d’incloure:
 •    Constructors (per defecte, amb paràmetres, de còpia). El constructor amb paràmetres ha de:
 o    llegir la informació de la ruta des d’un fitxer, ruta.txt, amb format:
 N //nombre de punts en la ruta
 x1 y1 //coordinades del punt1
 x2 y2 //coordinades del punt2
 ...  ...
 o    llegir la informació dels sobres des d’un fitxer, sobres.txt, amb format:
 Id1 x1 y1
 Id2 x2 y2
 ....
 on cada línia representa un sobre (Id del sobre i les coordenades d’un punt de treball on s’ha de lliurar). Aquests punts coincideixen amb els de la ruta del robot.
 •    Destructor
 •    Mètodes consultors (les que podeu necessitar, p.ex. consultar punt actual, consultar nombre sobres)
 •    Mètodes modificadors:
 o    Un mètode per donar-li al robot una ruta nova.
 o    Un mètode per donar-li al robot un nou repartiment (col·lecció de sobres).
 o    Quatre mètodes per moure el robot, respectivament, amb k caselles a l’esquerra, a la dreta, amunt i avall, per un valor k donat.
 o    Un mètode moure_a_xy per moure el robot des de la seva posició actual a una posició donada (x,y).
 o    Un mètode repartir_correu que a partir de la ruta (vegeu descripció de les dades i el dibuix), el robot es desplaça des de la posició d’origen (0,0) a la posició de cada punt en la ruta, deixa el sobre (simplement l’elimina del contenidor de sobres) fins arribar al final de la ruta i acabar el repartiment.
 o    Un mètode per tornar el robot a l’origen (0,0).
 

 */

#include <iostream>
#include<queue> //FIFO per lliurar els sobres
#include<fstream>

using namespace std;

struct Punt{
    
    int x, y;
    
   Punt():x(0),y(0){}
    
    Punt(int px, int py):x(px),y(py){}
    
    Punt(const Punt& P)
    {
        x = P.x;
        y = P.y;
    }
    Punt& operator = (const Punt& P)
    {
        if (this != &P)
        {
            x = P.x;
            y = P.y;
        }
        return (*this);
    }
};
    
struct Sobre{
    int Id;
    Punt PT; //Punt de treball
    
    Sobre(){}
    
    Sobre(int pID, Punt pPT)
    {
        Id = pID;
        PT = pPT;
    }
    
    Sobre(const Sobre& S)
    {
        Id = S.Id;
        PT = S.PT;
    }
    
    Sobre& operator = (const Sobre& S)
    {
        if (this != &S)
        {
            Id = S.Id;
            PT = S.PT;
        }
        return (*this);
    }
};

class RobotOficina{
    int Id;
    Punt PA; //pos actual
    Punt* Ruta;
    int nPunts;
    queue<Sobre> QS;
    
public:
   RobotOficina(){}
    
    RobotOficina(int pId, Punt pPA):Id(pId),PA(pPA){}
    
    //fruta, fitxer dels punts de la ruta
    RobotOficina(int pId, Punt pPA, ifstream& fruta)
    {
        Id = pId;
        PA = pPA;
        //Creem la ruta des del fitxer de punts
        delete[] Ruta;
        fruta >> nPunts;
        Ruta = new Punt[nPunts];
        int x, y;
        int i = 0;
        while (fruta >> x >> y)
        {
            Punt P(x,y);
            Ruta[i] = P;
            i++;
        }
    }
 
    //fruta, fitxer dels punts de la ruta
    //fsobres, fitxer de sobres
    RobotOficina(int pId, Punt pPA, ifstream& fruta,ifstream& fsobres)
    {
        Id = pId;
        PA = pPA;
        //Creem la ruta des del fitxer de punts
        fruta >> nPunts;
        Ruta = new Punt[nPunts];
        int x, y;
        int i = 0;
        while (fruta >> x >> y)
        {
            Punt P(x,y);
            Ruta[i] = P;
            i++;
        }
        //Creem la cua de sobres des del fitxer de punts
        //per respectar l'ordre de lliurament des del 1e al darrer punt
        int Id;
        while (fsobres >> Id >> x >> y)
        {
            Sobre S(Id, Punt(x,y));
            QS.push(S);
        }
    }
    
    //Constr de copia
    RobotOficina(const RobotOficina& RO)
    {
        Id = RO.Id;
        PA = RO.PA;
        delete[] Ruta;
        nPunts = RO.nPunts;
        Ruta = new Punt[nPunts];
        for (int i = 0; i < nPunts; i++)
        {
            Ruta[i] = RO.Ruta[i];
        }
        QS = RO.QS;
    }
    
    ~RobotOficina()
    {
        delete[] Ruta;
    }
    
    // Mètodes consultors (les mínimes que podeu necessitar)
    //Consultar la posició actual
    Punt puntActual()
    {
        return PA;
    }
    
    //Consultar nombre de sobres
    int getNSobres()
    {
        return QS.size();
    }
    
    //Mètodes modificadors.
    
    void setRuta(Punt* R)
    {
        Ruta = R;
    }
    
    void setSobres(queue<Sobre> CuaSobres)
    {
        QS = CuaSobres;
    }
    
    void setRuta(ifstream& fruta)
    {
        //Creem la ruta des del fitxer de punts
        fruta >> nPunts;
        Ruta = new Punt[nPunts];
        int x, y;
        int i = 0;
        while (fruta >> x >> y)
        {
            Punt P(x,y);
            Ruta[i] = P;
            i++;
        }
    }
    
    void setSobres(ifstream& fsobres)
    {
        //Creem la cua de sobres des del fitxer de punts
        //per respectar l'ordre de lliurament des del 1e al darrer punt
        int Id, x, y;
        while (fsobres >> Id >> x >> y)
        {
            Sobre S(Id, Punt(x,y));
            QS.push(S);
        }
    }
    
    //Entre ells ha d’haver-hi
    
    //Mètode moure_a_xy per moure el robot des de la seva posició actual a una posició donada (x,y).
    
    void moure_k_Esq(int k)
    {
        for(int i = 1; i<= k; i++)
        {
            PA.x -= 1;
        }
    }
    void moure_k_Dret(int k)
    {
        for(int i = 1; i<= k; i++)
        {
            PA.x += 1;
        }
    }
    void moure_k_Amunt(int k)
    {
            for(int i = 1; i<= k; i++)
            {
                PA.y += 1;
            }
    }
    void moure_k_Avall(int k)
    {
            for(int i = 1; i<= k; i++)
            {
                PA.y -= 1;
            }
    }
    
    //Cal cobrir tots els casos possibles de posicionament del PA (punt actual) i el punt donat P diferent de PA
    void moure_a_xy(Punt P)
    {
        if (P.x >= PA.x and P.y >= PA.y)
        {
            //moure a la dreta
            moure_k_Dret(P.x - PA.x);
            //moure amunt
            moure_k_Amunt(P.y - PA.y);
        }
        else if (P.x >= PA.x and P.y <= PA.y)
        {
            //moure a la dreta
                moure_k_Dret(P.x - PA.x);
                //moure avall
                moure_k_Avall(PA.y - P.y);
        }
        else if (PA.x >= P.x and P.y >= PA.y)
        {
                moure_k_Esq(PA.x - P.x);
                moure_k_Amunt(P.y - PA.y);
        }
        else if (PA.x >= P.x and PA.y >= P.y)
        {
                moure_k_Esq(PA.x - P.x);
                moure_k_Avall(PA.y - P.y);
        }
        else if (P.x >= PA.x and P.y <= PA.y)
        {
                moure_k_Dret(P.x - PA.x);
                moure_k_Avall(PA.y - P.y);
        }
        else if (P.x <= PA.x and P.y <= PA.y)
        {
                moure_k_Esq(PA.x - P.x);
                moure_k_Avall(PA.y - P.y);
        }
    }
    
    //repartir_correu que a partir de la ruta (vegeu descripció de les dades i el dibuix), el robot es desplaça des de la posició origen (0,0) a la posició de cada punt en la ruta, deixa el sobre (simplement l’elimina del contenidor de sobres) fins arribar al final i acabar el repartiment.
    
    void repartir_correu()
    {
        //Punt actual ha de ser origen de les coord.
        retornar_a_origen();
        
        for (int i = 0; i < nPunts; i++)
        {
            moure_a_xy(Ruta[i]);
            QS.pop();
            //Movem Punt Actual
            PA = Ruta[i];
        }
    }
    
    // retornar_a_origen per retornar el robot des de la posició actual (final de la ruta) a l’origen (0,0).
    
    void retornar_a_origen()
    {
        PA = Ruta[nPunts-1]; //PA és el punt final de la ruta, en realitat no cladria ja que al final del repartiment del correu, el PA es quedaria en el darrer punt de la ruta.
        moure_a_xy(Punt(0,0)); //moure al punt d'origen

    }
    
    // Operador d’assignació =
    
    RobotOficina& operator = (const RobotOficina& RO)
    {
        if (this != &RO)
        {
            Id = RO.Id;
            PA = RO.PA;
            delete[] Ruta;
            nPunts = RO.nPunts;
            Ruta = new Punt[nPunts];
            for (int i = 0; i < nPunts; i++)
            {
                Ruta[i] = RO.Ruta[i];
            }
            QS = RO.QS;
        }
        return (*this);
    }
    
    //Operador <<
    friend ostream& operator << (ostream& os, const RobotOficina& RO)
    {
        os << "Fitxa del robot: " << endl;
        os << "Id: " << RO.Id << endl;
        os << "Punt Actual: (" << RO.PA.x << ',' << RO.PA.y << ')' << endl;
        os << "===Ruta:====" << endl;
        for (int i = 0; i < RO.nPunts; i++)
        {
            os << '(' << RO.Ruta[i].x << ',' << RO.Ruta[i].y << ')' << endl;

        }
        
        return os;
    }
};

int main()
{
    RobotOficina ROBO;
    ifstream FRuta("/Users/fatosxhafa/Documents/ProgsC++/RobotOficina/ruta.txt");
    ifstream FSobres("/Users/fatosxhafa/Documents/ProgsC++/RobotOficina/sobres.txt");
    
    //Crear el punt origen
    Punt Origen(0,0);
    
    //Crear un robot, amb la ruta i els sobres
    RobotOficina RO(0, Origen,FRuta,FSobres);
    //Escriure robot
    cout << "===Robot RO:===" << endl;
    cout << RO;

    //Repartim el correu
    cout << "Repartim el correu: " << endl;
    cout << "Nombre de sobres a repartir: " << RO.getNSobres() << endl;
    RO.repartir_correu();
    cout << "Queden " << RO.getNSobres() << " a repartir! " << endl;
    
    cout << "Posició Actual del Robot Al final del repartiment: (" << RO.puntActual().x << ',' << RO.puntActual().y << ')' << endl;
    
    cout << "Fem retornar el robot a casella (0,0):" << endl;
    RO.moure_a_xy(Punt(0,0));
    cout << "Posició Actual del Robot: (" << RO.puntActual().x << ',' << RO.puntActual().y << ')' << endl;
    
    ifstream FRuta1("/Users/fatosxhafa/Documents/ProgsC++/RobotOficina/ruta1.txt");
    
    ifstream FSobres1("/Users/fatosxhafa/Documents/ProgsC++/RobotOficina/sobres.txt");

    Punt PA(1,5);

    RobotOficina RO1(1, PA);
    RO1.setRuta(FRuta1);
    RO1.setSobres(FSobres1);
    cout << "===Robot RO1:===" << endl;
    cout << RO1;
    
    
    return 0;
}
