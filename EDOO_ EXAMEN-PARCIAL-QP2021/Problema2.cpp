#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

#include <iostream>
#include<vector>
using namespace std;

class Sensor{
    
    //PART PRIVADA
    
    //DADES
    
    int Id;
    
    string tipus; //temp humitat contaminaci�...
    
    vector<double> valors;

    int nivbat;
    string estat;
    
    //double x, y, z; //posici�
    //double bateria; //nivell de bateria
    
    //M�TODES PRIVATS
    //NO HI HA
    
    
    //PART P�BLICA, API
    
public:
    //CONSTRUCTORS
    
    //PER DEFECTE
    Sensor(){}
    
    //CONSTRUCTOR AMB 1 PAR�METRE
    Sensor(int Id)
    {
        this->Id = Id; //Ja ho hem explicat
    }
    
    //CONSTRUCTOR AMB 2 PAR�METRES, EL VECTOR �S CREA TAMB�
    Sensor(int pId, string pTipus)
    {
        Id = pId;
        tipus = pTipus;
        //CREAR EL VECTOR
        cout << "Quants valors en t�?";
        int n; cin >> n;
        cout << "Introdueix " << n << " valors reals del vector:" << endl;
        for (int i=0; i<n;i++)
        {
        	double x;
        	cin >> x;
        	valors.push_back(x);
		}
    }
    
    //CONSTRUCTOR AMB 3 PAR�METRES
    Sensor(int pId, string pTipus, vector<double>& pValors)
    {
        Id = pId;
        tipus = pTipus;
        valors = pValors; //es pot fer ja que el vector t� definit l'assignaci� =
                          //per�...si els elements del vector s�n
                          //d'una classe, CAL QUE LA CLASSE TINGUI
                          //DEFINIT EL CONSTRUCTOR DE COPIA
    }
    
    //CONSTRUCTOR C�PIA
    Sensor(const Sensor& S)
    {
    	//copiar la informaci� de S a l'objecte que s'est� construint
    	Id = S.getId();
		tipus = S.getTipus(); //temp humitat contaminaci�...
		valors = S.getValors();
	}
    
    //M�todes per consultar valors
    //M�todes getters getX...
    int getId() const
    {
        return Id;
    }
    
    string getTipus() const
    {
        return tipus;
    }

    int getbat()
    {
        return nivbat;
    }

    string getestat()
    {
        return estat;
    }
    
    double getAverage() const
    {
    	double s = 0.0;
    	for (int i=0;i<valors.size();i++)
    	{
    		s += valors[i];
		}
		return s/valors.size();
	}
	
	const vector<double>& getValors() const
	{
		return valors;
	}
	
	//void getValors(vector<double>& vValors)
	//{
		//vValors = valors;
	//}
    
    //M�todes per modificar valors
    //M�todes setters setX...
    int setId(int pId)
    {
        Id = pId;
    }
	
	void setTipus(string pTipus)
    {
        tipus = pTipus;
    }

    void setnivbat(int pNivbat)
    {
        nivbat = pNivbat;
    }
    
    void setestat(string pEstat)
    {
        estat=pEstat;
    }

    void addValor(double v)
    {
        valors.push_back(v);
    }
    
    //OPERADOR D'ASSIGNACI�, ha de ser SEMPRE MEMBRE DE LA CLASSE
    Sensor& operator = (const Sensor& S) //assigna el sensor a l'objecte
    {
    	if (this != &S)//faig assignaci�
    	{
    		//copiar informaci�
    		Id = S.getId();
			tipus = S.getTipus(); 
			valors = S.getValors();
		}
		return (*this);
	}
	
	//OPERADOR ==
	//1. COM A MEMBRE DE LA CLASSE
	//2. COM A MEMBRE AMIC, FUNCI� AMIGA, M�TODE AMIC
	
	//COM A MEMBRE
	bool operator == (const Sensor& S)
	{
		//comparem component-wise, camp a camp
		return (Id == S.getId() and tipus == S.getTipus() and valors == S.getValors());
	}
	
	//COM A MEMBRE AMIC (FRIEND)
	//friend permet que un m�tode tingui acc�s directe a les dades de la classe
	bool operator == (Sensor& S)
	{
		//comparem component-wise, camp a camp
		return (Id == S.Id and tipus == S.tipus and valors == S.valors);
	}
	
	//Operador de comparaci�, comparem segons el valor mitja dels seus valors
	bool operator < (const Sensor& S)
	{
		//comparem component-wise, camp a camp
		return (getAverage() < S.getAverage());
	}
	
	//Operador d'entrada (el de l'extracci�) >>
	friend istream& operator >> (istream& entrada, Sensor& S)
	{
		cout << "Introdueix Id:" << endl;
		cin >> S.Id;
		cout << "Introdueix tipus: " << endl;
		cin >> S.tipus;
		
        //CREAR EL VECTOR
        cout << "Quants valors en t�?";
        vector<double> v;
		int n; cin >> n;
        cout << "Introdueix " << n << " valors reals del vector:" << endl;
        for (int i=0; i<n;i++)
        {
        	double x;
        	cin >> x;
        	v.push_back(x);
		}
		S.valors = v;
		return entrada;
	}
	
	//Escriure un sensor per canal de sortida 
    friend ostream& operator << (ostream& sortida, Sensor S)
    {
        sortida << "----------------------"<< endl;
		sortida << "Fitxa del sensor: " << endl;
        sortida << "Id: " << S.Id << endl;
        sortida << "Tipus: " << S.tipus << endl;
        sortida << endl <<"----------------------"<< endl;
        if ((S.valors).size()>0)
		{
			sortida << "Valors del vector:" << endl;
        	for (int i = 0; i< (S.valors).size(); i++)
        	{
        		sortida << S.valors[i] << ' ';
			}
        	sortida << endl;
			sortida << "Mitjana de valors: " << S.getAverage() << endl;
			sortida << endl <<"----------------------"<< endl;
	   }
        return sortida;
    }
};

class AnellesSensors
{
    int N;
};