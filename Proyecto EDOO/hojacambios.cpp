#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <time.h>
#include <algorithm>

using namespace std;

class Time {

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
    void ShowTime()
    {
        cout<< h << ':' << m << ':' << s << endl;
    }
};

class ticket {

    int place;
    string matricule;
    Time EH;

//API
public:

    //Constructor per defecte
    ticket()
    {
        place = 0;
        matricule = "0000AAA";
    }
    //Constructor amb parametres
    ticket(int p, string mat)
    {
        place = p;
        matricule = mat;
    }
    //Constructor de copia
    ticket(const ticket& TP)
    {
        place = TP.place;
        matricule = TP.matricule;
        EH = TP.EH;
    }

    //Metodes get
    int getP() const
    {
        return place;
    }
    string getM() const
    {
        return matricule;
    }
    Time getEH()
    {
        return EH;
    }
    //M�todes set
    void setPlace(int p)
    {
        place = p;
    }
    void setMatricule(string matr)
    {
        matricule = matr;
    }
    void setEH(Time pEH)
    {
        EH = pEH;
    }
    void AsigMat(string matr)
    {
        matr = matricule;
    }

    //Operadors
    ticket& operator = (const ticket& T)
    {
        if(this != &T)
        {
            place = T.place;
            matricule = T.matricule;
            EH = T.EH;
        }
        return (*this);
    }
    friend bool operator == (const ticket& T1, const ticket& T2)
    {
        return (T1.place == T2.place && T1.matricule == T2.matricule);
    }
    friend bool operator <= (const ticket& T1, const ticket& T2)
    {
        return (T1.place <= T2.place);
    }
    void ShowTicket(int xpl, string matr)
    {
        cout << endl << " ---- Benvingut a Parc Vallés ---- " << endl << endl;
        cout << " Cotxe amb matricula: " << matr << endl;
        cout << " La seva plaça es: " << xpl << endl;
        cout << " L'hora d'entrada es: "; EH.AutomaticTime();
        EH.ShowTime(); cout << endl;
        cout << " --------------------------------- " << endl;
    }

};

class recibo {
    struct dades
    {
        double h, m, s;
        string matricule;
        Time T;
        double hour(){
            T.AutomaticTime();
        return abs((h+(m/60)+(s/3600))-T.CalculeHour());

        }
        void calculprecio(double tarifa, double& precio){
            precio=hour()*tarifa;
        }
    };

    double PREU_SEGONS = 0.0002777777;
    vector<dades> dat;
    double precio, hour, tarifa=PREU_SEGONS*3600;
    string matricule, matr;
    Time T;
    dades d;

    public:
    //Constructor per defecte:
    recibo()
    {
        d.matricule = "0000AAA";
        d.h = 0;
        d.m = 0;
        d.s = 0;
        dat.push_back(d);
    }
    //Constructor amb parametres:
    recibo(string mat, string matri, int s, int m, int h)
    {
        d.matricule = mat;
        d.s = s;
        d.m = m;
        d.h = h;
        matr = matri;
        dat.push_back(d);
    }
    //Constructor de copia:
    recibo(const recibo& Copy)
    {
       d = Copy.d;
       dat = Copy.dat;
    }
    //Constructor de copia afegint matricula de sortida
    recibo(const recibo& Copy, string matricula)
    {
        dat = Copy.dat;
        d = Copy.d;
        matr = matricula;
    }
    //Constructor por archivo:
    recibo(ifstream& datos)
    {
        int numpl;
        while(datos >> d.h >> d.m >> d.s >> d.matricule >> numpl){
            dat.push_back(d);
        }
    }
    //Metodes get:
    double getH() const
    {
        return d.h;
    }
    double getM() const
    {
        return d.m;
    }
    double getS()
    {
        return d.s;
    }
    double getTarifa() const
    {
        return tarifa;
    }
    string getMat() const
    {
        return d.matricule;
    }
    double getPrecioS()
    {
        return PREU_SEGONS;
    }
    double getPrecioH()
    {
        return tarifa;
    }
    //M�todes set:
    void setMat(string mat)
    {
        matricule = mat;
    }
    void setDat(vector<dades> pDat){
        dat = pDat;
    }
    void setHour(double pHour)
    {
        hour = pHour;
    }
    void setPrecioS(double newp)
    {
        PREU_SEGONS=newp;
    }
    void setPreciopH(double newp)
    {
        tarifa=newp;
        PREU_SEGONS=tarifa/3600;
    }

    //Operadors

    recibo& operator = (const recibo& R)
    {
        if (this != &R)
        {
            dat = R.dat;
            precio = R.precio;
            hour = R.hour;
            matricule = R.matricule;
            T = R.T;
            d = R.d;
        }
        return (*this);
    }

	friend bool operator < (const recibo& R1, const recibo& R2)
    {
    	return (R1.precio < R2.precio); // Aqui tienes que hacer un menor que de lo que quieras (ver si por ejemplo si el coche no esta mas de 60min hacer que sea gratis o algo asi) yo te he hecho el operador ahora hay que implementarlo.
	}

    friend bool operator < (const recibo& R1, double& precio)
    {
        return (R1.precio < precio);
    }

    friend bool operator <= (const recibo& R1, const recibo& R2)
    {
    	return (R1.precio <= R2.precio);
	}

    friend ostream& operator <<(ostream& os, recibo& R)
    {
        if(R.matr=="")
        {
        R.d.calculprecio(R.tarifa,R.precio);
        os << endl << " ---- Benvingut a Parc Vall�s ---- " << endl << endl;
        os << " Cotxe amb matricula: " << R.matricule << endl;
        os << " La tarifa son " << R.tarifa <<" EUR/h"<<endl;
        os << " Temps transcorregut des de l'entrada: " << R.hour << endl;
        if(R.precio<0)
        {
            os << " Total cost: 0 EUR (Preu inferior 1 EUR)" <<endl;
            R.T.AutomaticTime();R.T.ShowTime(); cout << endl;
            os << " --------------------------------- " << endl;
        }
        else
        {
            os << " Total cost: " << R.precio << " EUR" << endl;
            R.T.AutomaticTime();R.T.ShowTime(); cout << endl;
            os << " --------------------------------- " << endl;
        }
        return os;
        }
        else
        {
        bool encontrado=false;
        for(int L=1; L<R.dat.size(); L++)
        {
            if(R.dat[L].matricule == R.matr)
            {
                R.dat[L].calculprecio(R.tarifa,R.precio);
                os << endl << " ---- Benvingut a Parc Vall�s ---- " << endl << endl;
                os << " Cotxe amb matricula: " << R.dat[L].matricule << endl;
                os << " La tarifa son " << R.tarifa <<" EUR/h"<<endl;
                os << " Temps transcorregut des de l'entrada: " << R.dat[L].hour() << " h" << endl;
                if(R.precio<0)
                {
                    os << " Total cost: 0 EUR (Preu inferior 1 EUR)" <<endl;
                    R.T.AutomaticTime();R.T.ShowTime(); cout << endl;
                    os << " --------------------------------- " << endl;
                }
                else
                {
                    os << " Total cost: " << R.precio << " EUR" << endl;
                    R.T.AutomaticTime();R.T.ShowTime(); cout << endl;
                    os << " --------------------------------- " << endl;
                }
                encontrado=true;
            }
        }
        if (encontrado==false) os<<"No se ha encontrado su matricula";
        return os;
        }
    }

    void operator >>(ifstream& T)
    {
        int numpl;
        while(T >> d.h >> d.m >> d.s >> d.matricule >> numpl){
            dat.push_back(d);
        }
    }
    //Subprogrames:

    //Mostrar recibo:
    void ShowRecip()
    {
        d.calculprecio(tarifa,precio);
        cout << endl << " ---- Benvingut a Parc Vall�s ---- " << endl << endl;
        cout << " Cotxe amb matricula: " << matricule << endl;
        cout << " La tarifa son " << tarifa <<" EUR/h"<<endl;
        cout << " Temps transcorregut des de l'entrada: " << hour << endl;
        cout << " Total cost: " << precio << endl;
        T.AutomaticTime();T.ShowTime(); cout << endl;
        cout << " --------------------------------- " << endl;
    }
    //Mostrar recibo con archivo:
    void ShowReciptxt(string matr)
    {
        bool encontrado=false;
        for(int L=1; L<dat.size(); L++){
            if(dat[L].matricule == matr){
                dat[L].calculprecio(tarifa,precio);
                cout << endl << " ---- Benvingut a Parc Vall�s ---- " << endl << endl;
                cout << " Cotxe amb matricula: " << dat[L].matricule << endl;
                cout << " La tarifa son " << tarifa <<" EUR/h"<<endl;
                cout << " Temps transcorregut des de l'entrada: " << dat[L].hour() << " h" << endl;
                cout << " Total cost: " << precio << " EUR" << endl;
                T.AutomaticTime();T.ShowTime(); cout << endl;
                cout << " --------------------------------- " << endl;
                encontrado=true;
            }
        }
        if (encontrado==false) cout<<"No se ha encontrado su matricula";
    }
};