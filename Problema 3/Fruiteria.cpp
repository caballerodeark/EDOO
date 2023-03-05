//Implementeu una jerarquia de tres classes per representar i gestionar informaci� sobre
//diverses fruites

#include<iostream>
#include<time.h>

using namespace std;

/*
La classe base ha de ser Fruita, amb la informaci� i m�todes que siguin comuns
a totes les fruites com ara nom, pes, calories / 100g, data caducitat (cal que utilitzeu
la classe Data), etc.
*/

//Classe Data
class Data{
    
    int dia, mes, any;
    
    //Comprovar si la data pertany a un any bissest. M�tode privat. Nom�s s'utilitzar� en la classe
    //Hi ha un altre m�tode public amb el mateix nom per� sense el par�metre any.
    bool de_traspas(int any) {
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
        
    //Consultar dies d'un mes i any donats. M�tode privat. Nom�s s'utilitzar� en la classe
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
    
    //Constructor per defecte amb la data actual, que d�na el sistema, llibreria time.h
    Data(){
        time_t t; //time_t �s una tupla de temps (dia, mes any, hora, mins, segs) definit en time.h
        time( &t );
        struct tm* info = localtime( &t );
        dia = info -> tm_mday;
        mes = info -> tm_mon + 1;
        any = 1900+ info -> tm_year; // l'any es comen�a a comptar a partir del 1900
    }
    
    //Constructor amb tres par�metres enters
    Data(int d, int m, int a){
        dia=d;
        mes=m;
        any=a;
    }
    
    //Constructor amb un par�metre enter ddmmaaaa
    Data(int ddmmaaaa){
        dia=ddmmaaaa/1000000;
        mes=(ddmmaaaa/10000)%100;
        any=ddmmaaaa%10000;
    }
    
    //Constructor amb un par�metre string en format dd:mm:aaaa o dd-mm-aaaa
    //stoi �s una funci� per converir un string (p.ex "12") en un enter (p.ex. 12)
    Data(string sd){
        string c1 = sd.substr (0,2);//el string dels car�cters dd
        dia=stoi(c1);
        string c2 = sd.substr (3,2);//el string dels car�cters mm
        mes=stoi(c2);
        string c3 = sd.substr (6); //el substring de la 6� posici� fins al final
        any=stoi(c3);
    }
    
    //Constructor de c�pia
    Data(const Data& data)
    {
        dia = data.dia;
        mes = data.mes;
        any = data.any;
    }
    
    //M�todes consultors
    int getDia() const{
        return dia;
    }
    int getMes() const{
        return mes;
    }
    int getAny() const{
        return any;
    }
    
    //Comprovar si la data que s'esta construint �s de trasp�s
    bool anyTraspas() const{
        return ((any % 4 == 0 && any % 100 != 0) or any%400 == 0);
    }
    
    //Comprovar si un any �s de trasp�s
    bool anyTraspas(int aaaa) const{
        return ((aaaa % 4 == 0 && aaaa % 100 != 0) or aaaa%400 == 0);
    }
    
    //M�todes modificadors. Se suposa que d, m i a s�n v�lids
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
    void afegirDies (int dd){
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
    
bool esDiaTraspas(int dd, int mm, int aaaa) 
{
	if (dd == 29 and mm == 2 and anyTraspas(aaaa))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void afegirAnys(int anys)
{
	if (esDiaTraspas(dia,mes,any) and !anyTraspas(any + anys))
	{
		dia = 28;
	}
	any += anys;
}
    
    //Operador d'assignaci�
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
    friend bool operator < (const Data& d1, const Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia < d2.any*10000+d2.mes*100+d2.dia);
    }
    
    //Comparar dues dates ==
    friend bool operator == (const Data& d1, const Data& d2)
    {
        return (d1.any*10000+d1.mes*100+d1.dia == d2.any*10000+d2.mes*100+d2.dia);
    }
    
    
    //Escriure una data per canal de sortida dd/mm/aaaa
    friend ostream& operator << (ostream& os, const Data& d)
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

class Fruita{
	
	//Dades
	string nom;
	double pes; //pes mitj� d'una pe�a de la fru�ta
	double cal; //calories / 100g, s'ha declarat protected, les altres classes tenen
						  //acc�s directa a la dada cal
	Data DC; //Data de caducitat
	//list<string> LP; //Llista de pa�sos de proced�ncia
	// bool comuna;
	
	public:
		
		Fruita(){} //Fruita(){ comuna = true;} en cas d'utilitzar la dada comuna
		Fruita(string nom, double pes, double cal)
		{
			this -> nom = nom;
			this -> pes = pes;
			this -> cal = cal;
		}
		//Altres constructors
		
		//API
		
		Data getDC() const
		{
			return DC;
		}
		void setDC(Data DC) //M�tode que s'ha d'implementar en les classes derivades
		{
			this -> DC = DC;
		}
		//Altres m�todes
		//Operadors...
		friend ostream& operator <<(ostream& os, const Fruita& F)	
		{
			os << F.nom << endl;
			os << F.pes << endl;
			os << F.cal << endl;
		}
};

class FruitaFresca : public Fruita{
	string temporada;
	Data DR; //Data recollida
	string consum; //"immediat" o "en n dies"
	//la DC; ja �s una dada de la classe base Fruita
	
	public:
		FruitaFresca(){}
		
		FruitaFresca(string nom, double pes, double cal, string temporada, Data DR, string consum):Fruita(nom,pes,cal)
		{
			this->temporada = temporada;
			this -> DR = DR;
			this -> consum = consum;
		}

		//...
		
		//API
		void setDC() //M�tode que s'ha d'implementar en la classe de nou, polimorfisme
		{
			Data D = DR; //per no modificar DR
			if (consum == "immediat")
			{
				D.afegirDies(2);
				Fruita::setDC(D); //a la data de recollida se li suma 2 dies 
				
			}
			else if (consum == "n dies")
			{
				cout << "Quants dies vols afegir pel consum, n=?";
				int n; 
				cin >> n;
				D.afegirDies(n);
				Fruita::setDC(D); //a la data de recollida se li suma n dies 
			}
	   }		
	   
	   //Operadors
	   	friend ostream& operator <<(ostream& os, const FruitaFresca& FF)	
		{
			Fruita F = (Fruita) FF;
			os << F;
			cout << "Temporada: " << FF.temporada << endl;
			cout << "Data recollida: " << FF.DR << endl;
			cout << "Consum: " << FF.consum << endl;
			cout << "Data caducitat (consum): " << FF.getDC() << endl;

		}
};

int main()
{
	Data DR; // Data de recollida �s avui
	//pes en grams
	FruitaFresca FF("Maduixa", 17, 9, "primavera", DR, "immediat");

	FF.setDC();
	
	cout << FF;
}