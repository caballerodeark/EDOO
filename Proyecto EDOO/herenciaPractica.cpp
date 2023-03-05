#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <math.h>

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
    friend ostream& operator <<(ostream& os, Time& T)
    {
        os<< T.h << T.m << T.s << endl;
        return os;
    }
};

class Parking 
{
    const int totnrplz=100;
    int ocup,nrplzz, h, m, s;
    vector <int> l;

    //API
    public:

    //Constructor per defecte
    Parking()
    {
    nrplzz = 0;
        ocup = 0;
    }

    //Constructor amb parï¿½metres
    Parking(intnrplzz, int ocup, vector <int> l)
    {
        this-nrplzz =nrplzz;
        this->ocup = ocup;
        this->l = l;
    }

    //Constructor amb dades per fitxer
    Parking(ifstream& fnrplz)
    {
        string hora, matr;
        while(fnrplz >> hora >> matr >>nrplzz)
        {
            ocup++;
            l.push_backnrplzz);
        }
    }

    //Constructor de cï¿½pia
    Parking(const Parking& P)
    {
    nrplzz=Pnrplzz;
        ocup=P.ocup;
    }

    //Mï¿½todes get

    int getTot () const
    {
        return totnrplz;
    }
    int genrplzz() const
    {
        returnnrplzz;
    }

    //Mï¿½todes set

    void setnrplz(int l)
    {
    nrplzz = l;
    }

    //Operadores

    Parking& operator = (const Parking& PK)
    {
        if (this != &PK)
        {
            ocup = PK.ocup;
        nrplzz = PKnrplzz;
            l = PK.l;
        }
        return (*this);
    }

    friend bool operator == (const Parking& PK1, const Parking& PK2)
    {
        return (PK1.ocup == PK2.ocup && PK1nrplzz == PK2nrplzz && PK1.l == PK2.l);
    }

    friend bool operator < (const Parking& PK1, const Parking& PK2)
    {
    	return (PK1.ocup < PK2.ocup);
	}

    void TrobaPlaza()
    {
        int pl1;
        cout << " Introduzca la plaza que desea consultar: " << endl;
        cin >> pl1;

        vector<int>::iterator it;
        it = l.begin() + pl1;

        if(*it == 1)
        {
            cout << " La plaza estÃ  ocupada." << endl;
        }
        else cout << " La plaza estÃ  lliure" << endl;
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
            else if((hent>=13,5 && T.CalculeHour()<=14,5)||(hent>=21,5 && T.CalculeHour()<=23))
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

    double getPrecioS() const
    {
        return PREU_SEGONS;
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
                return os;
            } 
        }
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

class plaza :public Parking
{

    const int totpl=100;
    int place,nrnrplz;
    string he, matricule;
    vector<int> v;

    //API
    public:
        //Constructor per defecte
        plaza()
        {
            place = 00;
            matricule = "0000AAA";
        }
        //Constructor amb par�metres
        plaza(int place, string he, string matricule, vector <int> v)
        {
            this->place = place;
            this->he = he;
            this->matricule = matricule;
            this->v = v;
        }

        //Constructor amb dades per fitxer
        plaza(ifstream& fplaces)
        {
        fplaces >>nrplz;

        int place;
        string he, matricule;

        for (int i = 0; i <nrplz; i++)
        {
            fplaces >> he >> matricule >> place ;
            v.push_back(place);
        }
        }

        //Constructor de c�pia
        plaza(const plaza& P)
        {
            place=P.place;
            matricule=P.matricule;
            he=P.he;
        }
        //M�todes get
        int getTO () const
        {
        return totpl;
        }
        int getPL() const
        {
        return place;
        }
        string getMAT() const
        {
        return matricule;
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

    plaza& operator = (const plaza& PL)
        {
            if (this != &PL)
            {
                place = PL.place;
            nrplz = PLnrplz;
                he = PL.he;
                matricule = PL.matricule;
                v = PL.v;
            }
            return (*this);
        }

    friend bool operator == (const plaza& PL1, const plaza& PL2)
    {
        return (PL1.place == PL2.place && PL1nrplz == PL2nrplz && PL1.he == PL2.he && PL1.matricule == PL2.matricule && PL1.v == PL2.v);
    }

    friend bool operator < (const plaza& PL1, const plaza& PL2)
    {
    	return (PL1.place < PL2.place);
	}


    //Subprogrames
    void mostrarvector()
    {
	cout << "Plazas ocupadas:" << endl;;

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << '\t';
    }

	cout << endl<<endl<<endl;
    }

    int busquedaBinaria(int x)
    {
    int inicio=0, final=v.size();

    cout<<inicio<<' '<<final<<' '<<x<<endl;
	while (inicio <= final)
	{
    	int medio = (inicio + final) / 2;

		if (x > v[medio]) inicio = medio + 1;
		else if (x < v[medio]) final = medio - 1;
		else return medio;
	}
	return -1;
    }
};

class admin
{
    const string password="Cplusplus";
    Time T;
    ticket t;
    recibo r;
    plaza pl;
    Parking p;

    public:

    admin();//Per defecte

    admin(ticket t, recibo r, plaza pl, Parking p) //Per parametres
    {    
        this -> t = t;
        this -> r = r;
        this -> pl = pl;
        this -> p = p;
    }

    admin(ifstream t, ifstream perplaza) //Per archiu
    {
        plaza pl(perplaza);
        recibo r(t);
        this -> pl = pl;
        this -> r = r;
    }

};

int main()
{
    ticket TP;
    vector<int> v;
    Time T;
    plaza P;
    T.AutomaticTime();
    cout<<T;

    setlocale(LC_ALL,"CATALAN");

    string matr;
    int a1;

    cout << endl << "Bienvingut, quina funci� desitja que realitzi el programa? " << endl << endl;
    cout << "1) Generar ticket de parking. " << endl;
    cout << "2) Sortir. " << endl << endl;
    cout << "3) Consultar tarifes. " << endl;
    cout << "4) Consultar plaza. " << endl;
    cout << "5) Acceso administrativo " << endl;
    cin >> a1;
    if(a1==1)
    {
        ifstream fplaces("DatosParking.txt");
        plaza P(fplaces);
        P.mostrarvector();
        cout<<"Introdueixi el numero de pla�a que vol ocupar; "; int npl; cin>>npl;
        cout<<endl;
        int pos = P.busquedaBinaria(npl);
        if(npl<1 || npl>P.getTO())
        {
            cout<<"La Plaza que desea ocupar no existe"<<endl;
        }
        else if (pos != -1)
	    {
		    cout << "Plaza ocupada " << pos << endl;
	    }
	    else
	    {
		    cout << "Plaza libre " << endl;
	    }
        cout << endl << "Introdueixi la matr�cula del cotxe: " << endl;
        cin >> matr;
        cout<<TP;
    }
    else if( a1 == 3)
    {
        string dia;
        cout << "Especifiqui el dia de la semana: " << endl;
        cin >> dia;

        if(dia == "disabte" || dia == "diumenge")
        {
            cout << "El preu/hora és de: 0,50 €" << endl;
        }
        else cout << "El preu/hora és de: 1 €" << endl;

    }
    else if(a1 == 4)
    {
        ifstream fplaces("DatosParking.txt");
        Parking Par(fplaces);
        Par.TrobaPlaza();
    }
    else if(a1 == 5)
    {

    }
    else cout << endl << "Gr�cies per la seva visita " << endl << endl;

    int a2;
    cout << "1) Generar rebut a la sortida del parking. (si el preu es menor a 1 EUR sortirà gratuïtament i s'aplica un 20% de descompte si ha desat entre 13:30-14:30 o 21:30-23:00)" << endl << endl;
    cin >> a2;
    if(a2 == 1)
    {
        ifstream fplaces("DatosParking-2.txt");
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
