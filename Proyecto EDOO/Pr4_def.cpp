#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <map>

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
    friend istream& operator >>(istream& is, Time&T)
    {
        string mat;
        int numpl;
        is>>T.h>>T.m>>T.s>>mat>>numpl;
        return is;
    }
};

class ticket
{
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
    friend ostream& operator <<(ostream& os, ticket& T)
    {
        os << " ---- Benvingut a Parc Valles ----" << endl << endl;
        os << " Cotxe amb matricula: " << T.matricule << endl;
        os << " La seva plaÃ§a Ã©s: " << T.place << endl;
        os << " L'hora d'entrada Ã©s: ";
        T.EH.AutomaticTime();
        os << " ---------------------------------- " << endl;
        return os;
    }
    friend istream& operator>>(istream& is, ticket& T)
    {
        int m,h,s,numpl;
        string matricule;
        is>>h>>m>>s>>T.matricule>>T.place;
        T.EH.setHora(h);
        T.EH.setMin(m);
        T.EH.setSeg(s);
        return is;
    }
};

class recibo
{
    struct dades
    {
        double h, m, s;
        string matricule;
        Time T;
        double hour(bool& descuento)
        {
            double hent=(h+(m/60)+(s/3600));
            T.AutomaticTime();
            if(hent>=23 && T.CalculeHour()<=6) return 0;
            else if((hent>=13.5 && T.CalculeHour()<=14.5)||(hent>=21.5 && T.CalculeHour()<=23))
            {
                descuento = true;
                return abs((h+(m/60)+(s/3600))-T.CalculeHour());
            }
            else return abs((h+(m/60)+(s/3600))-T.CalculeHour());
        }
        void calculprecio(double tarifa, double& precio, bool& descuento)
        {
            precio=hour(descuento)*tarifa;
        }
    };
    vector<dades> dat;
    double precio, hour, tarifa=(0.0003*3600);
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
        while(datos >> d.h >> d.m >> d.s >> d.matricule >> numpl)
        {
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

    double getPrecioH() const
    {
        return tarifa;
    }

    //M�todes set:

    void setMat(string mat)
    {
        matricule = mat;
    }

    void setDat(vector<dades> pDat)
    {
        dat = pDat;
    }

    void setHour(double pHour)
    {
        hour = pHour;
    }

    void setPreciopH(double newp)
    {
        tarifa=newp;
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
        bool descuento;
        if(R.matr=="")
        {

            R.d.calculprecio(R.tarifa,R.precio,descuento);
            os << endl << " --------------------------------- " << endl << endl;
            os << " Cotxe amb matricula: " << R.matricule << endl;
            os << " La tarifa son " << R.tarifa <<" EUR/h"<<endl;
            os << " Temps transcorregut des de l'entrada: " << R.hour << endl;
            if(R.precio<0)
            {
                os << " Total cost: 0 EUR (Preu inferior 1 EUR)" <<endl;
                R.T.AutomaticTime();cout<<R.T; cout << endl;
                os << " --------------------------------- " << endl;
            }
            else
            {
                if(descuento)
                {
                    os << " Cost real: " << R.precio << "EUR"<< endl;
                    os << " Total cost: " << (R.precio*0.80) << " EUR (20% de descompte)" << endl;
                    R.T.AutomaticTime();cout<<R.T; cout << endl;
                    os << " --------------------------------- " << endl;
                }
                else
                {
                    os << " Total cost: " << R.precio << " EUR" << endl;
                    R.T.AutomaticTime();cout<<R.T; cout << endl;
                    os << " --------------------------------- " << endl;
                }
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
                    R.dat[L].calculprecio(R.tarifa,R.precio, descuento);
                    os << endl << " --------------------------------- " << endl << endl;
                    os << " Cotxe amb matricula: " << R.dat[L].matricule << endl;
                    os << " La tarifa son " << R.tarifa <<" EUR/h"<<endl;
                    os << " Temps transcorregut des de l'entrada: " << R.dat[L].hour(descuento) << " h" << endl;
                    if(R.precio<0)
                    {
                        os << " Total cost: 0 EUR (Preu inferior 1 EUR)" <<endl;
                        R.T.AutomaticTime();cout<<R.T; cout << endl;
                        os << " --------------------------------- " << endl;
                    }
                    else
                    {
                        if(descuento)
                        {
                            os << " Cost real: " << R.precio << "EUR"<< endl;
                            os << " Total cost: " << (R.precio*0.80) << " EUR (20% de descompte)" << endl;
                            R.T.AutomaticTime();cout<<R.T; cout << endl;
                            os << " --------------------------------- " << endl;
                        }
                        else
                        {
                            os << " Total cost: " << R.precio << " EUR" << endl;
                            R.T.AutomaticTime();cout<<R.T; cout << endl;
                            os << " --------------------------------- " << endl;
                        }
                    }
                    encontrado=true;
                }
            }
            if (encontrado==false)
            {
                os<<"No se ha encontrado su matricula";
            }
        }
        return os;
    }

    friend istream& operator >>(istream& T,recibo& R)
    {
        string numpl;
        T>>R.d.h>>R.d.m>>R.d.s>>R.d.matricule>>numpl;
        R.dat.push_back(R.d);
        return T;
    }

    //Subprogrames:

    //Mostrar recibo:
    void ShowRecip()
    {
        bool descuento;
        d.calculprecio(tarifa,precio,descuento);
        cout << endl << " --------------------------------- " << endl << endl;
        cout << " Cotxe amb matricula: " << matricule << endl;
        cout << " La tarifa son " << tarifa <<" EUR/h"<<endl;
        cout << " Temps transcorregut des de l'entrada: " << hour << endl;
        if(descuento)
        {
            cout << " Cost real: " << precio << " EUR" << endl;
            cout << " Total cost: " << (precio*0.8) << " EUR (20% de descompte) " << endl;
            T.AutomaticTime();cout<<T<<endl;
            cout << " --------------------------------- " << endl;
        }
        else
        {
            cout << " Total cost: " << " EUR" << precio << endl;
            T.AutomaticTime();cout<<T<<endl;
            cout << " --------------------------------- " << endl;
        }
    }

    //Mostrar recibo con archivo:
    void ShowReciptxt(string matr)
    {
        bool encontrado=false, descuento;
        for(int L=1; L<dat.size(); L++)
        {
            if(dat[L].matricule == matr)
            {
                dat[L].calculprecio(tarifa,precio,descuento);
                cout << endl << " --------------------------------- " << endl << endl;
                cout << " Cotxe amb matricula: " << dat[L].matricule << endl;
                cout << " La tarifa son " << tarifa <<" EUR/h"<<endl;
                cout << " Temps transcorregut des de l'entrada: " << dat[L].hour(descuento) << " h" << endl;
                if(descuento)
                {
                    cout << " Cost real: " << precio << " EUR" << endl;
                    cout << " Total cost: " << (precio*0.8) << " EUR (20% de descompte) " << endl;
                    T.AutomaticTime();cout<<T<<endl;
                    cout << " --------------------------------- " << endl;
                }
                else
                {
                    cout << " Total cost: " << " EUR" << precio << endl;
                    T.AutomaticTime();cout<<T<<endl;
                    cout << " --------------------------------- " << endl;
                }
                encontrado=true;
            }
        }
        if (encontrado==false) cout << "No se ha encontrado su matricula";
    }

};

class plaza
{
    const int totpl=100;
    int place,h,m,s;
    bool ocupada;
    string matricule;

    //API
    public:
    
    plaza() //Constructor per defecte
    {
        place = 00;
        matricule = "0000BBB";
        ocupada=false;
    }
    
    plaza(int place, int h, int m, int s, string matricule) //Constructor amb par�metres
    {
        this->place = place;
        this->h = h;
        this->m = m;
        this->s = s;
        this->matricule = matricule;
        this->ocupada=true;
    }

    plaza(const plaza& P) //Constructor de c�pia
    {
        place=P.place;
        matricule=P.matricule;
        h=P.h;
        m=P.m;
        s=P.s;
        ocupada=P.ocupada;
    }

    //M�todes get

    int getPL() const
    {
        return place;
    }

    string getMAT() const
    {
        return matricule;
    }

    int getH()
    {
        return h;
    }

    int getM()
    {
        return m;
    }

    int getS()
    {
        return s;
    }

    bool getOcupada()
    {
        return ocupada;
    }

    //M�todes set
    void setPla(int p)
    {
        place = p;
    }

    void setMat(string mat)
    {
        matricule = mat;
    }

    void setH(int h)
    {
        this->h=h;
    }

    void setM(int m)
    {
        this->m=m;
    }

    void setS(int s)
    {
        this->s=s;
    }

    void setOcupada(bool ocupada)
    {
        this->ocupada=ocupada;
    }

    //Operadores

    plaza& operator = (const plaza& PL)
    {
        if (this != &PL)
        {
            place = PL.place;
            h = PL.h;
            m = PL.m;
            s = PL.s;
            matricule = PL.matricule;
        }
        return (*this);
    }

    friend bool operator == (const plaza& PL1, const plaza& PL2)
    {
        return (PL1.place == PL2.place && PL1.h == PL2.h && PL1.m == PL2.m && PL1.s == PL2.s && PL1.matricule == PL2.matricule);
    }

    friend bool operator == (plaza& place, const bool& tr)
    {
        return place.getOcupada()==tr;
    }

    friend bool operator<(const plaza& PL1, const plaza& PL2)
    {
    	return (PL1.place < PL2.place);
	}

    friend ostream& operator<<(ostream& os,const plaza& P)
    {
        os<<" "<<P.h<<" "<<P.m<<" "<<P.s<<" "<<P.matricule<<" "<<P.place;
        return os;
    }

    friend istream& operator>>(istream& is,plaza& pl)
    {
        is>>pl.h>>pl.m>>pl.s>>pl.matricule>>pl.place;
        return is;
    }

    //Metodes

    void salida()
    {
        place=00;
        matricule="0000BBB";
        ocupada=false;
        h=0;
        m=0;
        s=0;
    }
};

class Parking
{
    const int totpl=100;
    int ocup,lliur;
    map<int,plaza> plazas;
    Time T;

    public:

    Parking() //Per defecte
    {
        plazas.clear();
        ocup=0;
        lliur=0;
        T.AutomaticTime();
    } 

    Parking(map<int,plaza> plazas, Time T, int ocup) //Per caracters
    {
        this->plazas=plazas;
        this->T=T;
        this->ocup=ocup;
        this->lliur=totpl-ocup;
    }

    Parking(ifstream& fplaces) //Per lectura de fitxer
    {
        plaza C;
        int place,h,m,s;
        string mat;
        ocup=0;
        while(fplaces>>h>>m>>s>>mat>>place)
        {
            C.setMat(mat);
            C.setPla(place);
            C.setH(h);
            C.setM(m);
            C.setS(s);
            C.setOcupada(true);
            pair<int,plaza> newpl(place,C);
            plazas.insert(newpl);
            ocup++;
        }
        lliur=totpl-ocup;
    }

    Parking(Parking& P) //De copia
    {
        this->plazas=P.plazas;
        this->T=P.T;
        this->ocup=P.ocup;
        this->lliur=totpl-P.ocup;
    }

    //Metodes get

    int getOcup()
    {
        return ocup;
    }

    int getLliur()
    {
        return lliur;
    }

    map<int,plaza> getPlazas()
    {
        return plazas;
    }

    Time getT()
    {
        return T;
    }

    //Metodes set

    void setPlazas(map<int,plaza> plazas)
    {
        this->plazas=plazas;
        ocup=0;
        for(int k=1; k<101; k++)
        {
            if(plazas[k].getOcupada())
            {
                ocup++;
            }
        }
        lliur=totpl-ocup;
    }

    //Operadores

    void operator=(const Parking& P)
    {
        this->plazas=P.plazas;
        this->T=P.T;
        this->ocup=P.ocup;
        this->lliur=totpl-P.ocup;
    }

    friend bool operator==(const Parking& P1, const Parking& P2)
    {
        return P1.ocup==P2.ocup;
    }

    friend bool operator!=(const Parking& P1, const Parking& P2)
    {
        return P1.ocup!=P2.ocup;
    }

    friend bool operator<(const Parking& P1, const Parking& P2)
    {
        return P1.ocup<P2.ocup;
    }

    friend bool operator>(const Parking& P1, const Parking& P2)
    {
        return P1.ocup>P2.ocup;
    }

    friend bool operator<=(const Parking& P1, const Parking& P2)
    {
        return P1.ocup<=P2.ocup;
    }

    friend bool operator>=(const Parking& P1, const Parking& P2)
    {
        return P1.ocup>=P2.ocup;
    }

    friend ostream& operator<<(ostream& os,const Parking& P)
    {
        map<int,plaza> p=P.plazas;
        for(int k=1; k<101; k++)
        {
            if(p[k].getOcupada())
            {
                os<<p[k]<<endl;
            }
            else os<<"Plaza libre"<<endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Parking& P)
    {
        pair<int,plaza> lect;
        plaza p;
        int h,m,s,place;
        string mat;
        is>>h>>m>>s>>mat>>place;
        p.setH(h); p.setM(m); p.setS(s); p.setMat(mat); p.setPla(place);
        lect.first=place; lect.second=p;
        P.plazas.insert(lect);
        return is;
    }

    //Metodes 

    void vacia(int plaz)
    {
        map<int,plaza> :: iterator it=plazas.find(plaz);
        plazas.erase(it);
    }

    void añadeocambia(plaza P)
    {
        int pl=P.getPL();
        vacia(pl);
        pair<int,plaza> nueva(pl,P);
        plazas.insert(nueva);
    }

    bool ocupado()
    {
        return ocup==totpl;
    }

    bool libre()
    {
        return lliur==totpl;
    }

    bool miraplaza(int numpl)
    {
        return plazas[numpl].getOcupada();
    }

    void mostraparking()
    {
        for(int k=1; k<101; k++)
        {
            if(plazas[k].getOcupada()==true) cout<<plazas[k]<<endl;
            else if(plazas[k].getOcupada()==false) cout<<"VACIA "<<k<<endl;
        }
    }
};



class admin
{
    Time T;
    ticket t;
    recibo r;
    Parking pl;

    public:

    admin() //Per defecte
    {}
    admin(ticket t, recibo r, Parking pl) //Per parametres
    {
        this -> t = t;
        this -> r = r;
        this -> pl = pl;
    }
    admin(ifstream& t) //Per archiu
    {
        Parking pl(t);
        recibo r(t);
        this -> pl = pl;
        this -> r = r;
    }

    ticket getT()
    {
        return t;
    }
    recibo getR()
    {
        return r;
    }
    Parking getPl()
    {
        return pl;
    }
    Time getTim()
    {
        return T;
    }

    void setT(ticket t)
    {
        this->t=t;
    }
    void setR(recibo r)
    {
        this->r=r;
    }
    void setPl(Parking pl)
    {
        this->pl=pl;
    }
    void setTim(Time T)
    {
        this->T=T;
    }

    //Operadors:
    friend istream& operator >>(istream& is,admin& A)
    {
        int h,m,s,numpl;
        string mat;
        is>>h>>m>>s>>mat>>numpl;
        plaza p(numpl,h,m,s,mat);
        Time T(h,m,s);
        A.T.setHora(h);
        A.T.setMin(m);
        A.T.setSeg(s);
        A.t.setMatricule(mat);
        A.t.setPlace(numpl);
        A.t.setEH(T);
        A.r.setMat(mat);
        A.pl.añadeocambia(p);
        return is;
    }

    //Subprogramas:
    void hazlistado()
    {
        for(int k=1; k<101; k++)
        {
            cout<<pl.getPlazas()[k]<<endl;
        }
    }

    void inoutpl(string inout)
    {
        map<int,plaza> plazas = pl.getPlazas();
        vector<int> pllib;
        if(inout=="in")
        {
            if(pl.ocupado()==true)
            {
                cout<<"Parking completo"<<endl;
            }
            else
            {
                for(int k=1; k<101; k++)
                {
                    if(plazas[k].getOcupada()==false)
                    {
                        cout<<k<<" ";
                        pllib.push_back(k);
                    }
                }
                cout << endl << "Eliga en que plaza desea añadir vehiculo:"<<endl;
                cout<<endl;
                int dec;
                bool hecho=false;
                while(hecho==false)
                {
                    bool acierto;
                    cin>>dec;
                    for(int k; k<pllib.size();k++)
                    {
                        if(pllib[k]==dec)
                        {
                            acierto=true;
                        }
                    }
                    if(acierto==true)
                    {
                        string mat;
                        Time T;
                        cout<<"Introduzca matricula" << endl;
                        cin>>mat;
                        T.AutomaticTime();
                        plaza newocup(dec,T.getHora(),T.getMinutes(),T.getSeconds(),mat);
                        plazas.insert(pair<int,plaza>(dec,newocup));
                        hecho=true;
                    }
                    else cout<<"Plaza no elegida, vuelva a escribir"<<endl;
                }
                pl.setPlazas(plazas);
            }
        }
        else
        {
            if(pl.getOcup()==0)
            {
                cout<<"Parking vacio"<<endl;
            }
            else
            {
                cout<<"Eliga la plaza que quiera limpiar: " ;
                for(int k=1; k<101; k++)
                {
                    if(plazas[k].getOcupada()==true)
                    {
                        cout<<k<<" " ;
                        pllib.push_back(k);
                    }
                }
                cout<<endl;
                bool hecho=false;
                while(hecho)
                {
                    int dec;
                    bool acierto;
                    cin>>dec;
                    for(int k; k<pllib.size();k++)
                    {
                        if(pllib[k]==dec)
                        {
                            acierto=true;
                        }
                    }
                    if(acierto==true)
                    {
                        map<int,plaza> :: iterator borrar = plazas.find(dec);
                        plazas.erase(borrar);
                        hecho=true;
                    }
                    else cout<<"Plaza no elegida, vuelva a escribir"<<endl;
                }
                pl.setPlazas(plazas);
            }
        }
    }
};

int main()
{
    ifstream datos("DatosParking.txt");
    ticket TP;
    recibo r;
    vector<int> v;
    Time T;
    Parking P(datos);
    admin A(TP,r,P);

    T.AutomaticTime();
    cout<<T;
    setlocale(LC_ALL,"CATALAN");
    string ident;
    cout << "Identificació com a client o com administrador -> client/admin " << endl;
    cin >> ident;
    if(ident == "admin")
    {
        int cod_seg;
        cout << "Per favor introdueix la clau de seguretat: " << endl;
        cin >> cod_seg;
        if(cod_seg == 687956)
        {
            int b1;
            cout << " Hola administrador, quina funció desitja realitzar: " << endl;
            cout << " 1) Veure si una plaça es troba ocupada. " << endl;
            cout << " 2) Afegir un vehícile a una plaça. " << endl;
            cout << " 3) Treure un vehícle d'una plaça. " << endl;
            cout << " 4) Fer un llistat amb tots els vehícles que han entrat al parking. " << endl;
            cout << " 6) Sortir. " << endl;
            cin >> b1;
            if(b1 == 1)
            {
                int plaza;
                cout << " Quina plaça vol consultar?" << endl;
                cin>>plaza;
                if(P.miraplaza(plaza)==false)
                {
                    cout << "La plaça " << plaza << " es troba lliure." << endl;
                }
                else cout << "La plaça " << plaza << " ocupada." << endl;
            }
            else if(b1 == 2)
            {
                //afegir vehicle
                A.inoutpl("in");
            }
            else if(b1 == 3)
            {
                //treure vehícle
                A.inoutpl("out");
            }
            else if(b1 == 4)
            {
                //Hacer listado
                A.hazlistado();
            }
            else cout << " Ha sortit del programa amb exit. " << endl;
        }
        else
        {
            int n = 0;
            while (cod_seg != 687956 && n != 2)
            {
                cout << " La clau és incorrecta torni a intentar-ho " << endl;
                cin >> cod_seg;
                n++;
            }
            cout << "Acces denegat" << endl;
        }
    }
    else
    {
        string matr;
        int a1;
        cout << endl << "Bienvingut, quina funci� desitja que realitzi el programa? " << endl << endl;
        cout << "1) Generar ticket de parking. " << endl;
        cout << "2) Sortir. " << endl << endl;
        cout << "3) Consultar tarifes. " << endl;
        cin >> a1;
        if(a1==1)
        {
            int npl; 
            bool elegida=false;
            P.mostraparking();
            cout<<"Introdueixi el numero de pla�a que vol ocupar: "; 
            cin>>npl;
            cout<<endl;
            P.miraplaza(npl);
            while(elegida==false)
            {
                if(npl<0 || 100<npl)
                {
                    cout<<"La Plaza que desea ocupar no existe"<<endl;
                    elegida = false; 
                }
                else
                { 
                    if (P.miraplaza(npl))
                    {
                        cout<<"Plaza ocupada"<<endl;
                        elegida = false;
                    }
                    else if(!P.miraplaza(npl))
                    {
                        cout<<"Plaza libre"<<endl;
                        elegida = true;
                    }
                }
                if(elegida==false)
                {
                    cout<<"Introdueixi el numero de pla�a que vol ocupar: ";
                    cin>>npl;
                }
            }
            cout << endl << "Introdueixi la matr�cula del cotxe: " << endl;
            cin >> matr;
            T.AutomaticTime();
            plaza p(npl,T.getHora(),T.getMinutes(),T.getSeconds(),matr);
            P.añadeocambia(p);
            TP.setMatricule(matr);
            cout << TP;
        }
        else if( a1 == 3)
        {
            string dia;
            cout << "Especifiqui el dia de la semana: " << endl;
            cin >> dia;

            if(dia == "disabte" || dia == "diumenge")
            {
                cout << "El preu/hora és de: 0,50 EUR" << endl;
            }
            else cout << "El preu/hora és de: 1 EUR" << endl;
        }
        else cout << endl << "Gr�cies per la seva visita " << endl << endl;

        int a2;
        cout << "1) Generar rebut a la sortida del parking. (si el preu es menor a 1 EUR sortirà gratuïtament i s'aplica un 20% de descompte si ha desat entre 13:30-14:30 o 21:30-23:00)" << endl << endl;
        cin >> a2;
        if(a2 == 1)
        {
            ifstream fplaces("DatosParking.txt");
            recibo r(fplaces, matr);
            string dia;
            cout<<"Indique su matricula y dia"<<endl;
            cin>>matr>>dia;
            for (bool correcto=false; correcto==true; correcto=false)
            {
                if(dia == "disabte" || dia == "diumenge")
                {
                    cout << "El preu/hora és de: 0,50 €" << endl;
                    r.setPreciopH(0.5);
                    correcto=true;
                }
                else if(dia=="divendres" || dia=="dilluns" || dia=="dimarts" || dia=="dimecres" || dia=="dijous")
                {
                    cout << "El preu/hora és de: 1 €" << endl;
                    r.setPreciopH(1);
                    correcto=true;
                }
            }
            cout<<r;
        }
        else  cout << endl << "Que disfruti de la seva estancia al centre comercial, si necessita ajuda contacti amb el t�cnic al c�rrec. " << endl;
    }
}