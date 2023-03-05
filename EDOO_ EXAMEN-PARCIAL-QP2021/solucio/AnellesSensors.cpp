#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//Classe Sensor
/*
 a)  [1 PUNT] Modifiqueu la classe Sensor (que teniu a l’Atenea) per tal d’afegir en les seves dades el nivell de bateria (de 0 a 100%), i el seu estat (encès/apagat). Després, afegiu els mètodes corresponents per consultar i modificar el nivell de la bateria, consultar i modificar l’estat.
 */

class Sensor{
    
    //PART PRIVADA
    
    //DADES
    
    int Id;
    string tipus; //temp humitat contaminaciÛ...
    vector<double> valors;
    double bateria; //nivell de bateria
    bool estat; //true=encès/ false=apagat
    
    
    //MÈTODES PRIVATS
    //NO HI HA
    
    
    //PART PÚBLICA, API
    
public:
    //CONSTRUCTORS
    
    //PER DEFECTE
    Sensor(){}
    
    //CONSTRUCTOR AMB 1 PAR¿METRE
    Sensor(int Id)
    {
        this->Id = Id; //Ja ho hem explicat
    }
    
    //CONSTRUCTOR AMB 2 PARÀMETRES, EL VECTOR ÉS CREA TAMBÉ
    Sensor(int pId, string pTipus)
    {
        Id = pId;
        tipus = pTipus;
        //CREAR EL VECTOR
        cout << "Quants valors en té?";
        int n; cin >> n;
        cout << "Introdueix " << n << " valors reals del vector:" << endl;
        for (int i=0; i<n;i++)
        {
            double x;
            cin >> x;
            valors.push_back(x);
        }
        cout << "Nivell bateria?";
        cin >> bateria;
        cout << "Estat (encès=1,apagat=0)?";
        int x; cin >> x;
        if (x)
        {
            estat = true;
        }
        else
        {
            estat = false;
        }
    }
    
    //CONSTRUCTOR AMB 3 PARÀMETRES
    Sensor(int pId, string pTipus, vector<double>& pValors)
    {
        Id = pId;
        tipus = pTipus;
        valors = pValors; //es pot fer ja que el vector té definit l'assignació =
                          //però...si els elements del vector són
                          //d'una classe, CAL QUE LA CLASSE TINGUI
                          //SOBRECARREGAT L'OPERADOR =
        cout << "Nivell bateria?";
        cin >> bateria;
        cout << "Estat (encès=1,apagat=0)?";
        int x; cin >> x;
        if (x)
        {
            estat = true;
        }
        else
        {
            estat = false;
        }
    }
    
    //CONSTRUCTOR CÒPIA
    Sensor(const Sensor& S)
    {
        //copiar la informació de S a l'objecte que s'està construint
        Id = S.Id;
        tipus = S.tipus; //temp, humitat, contaminació...
        valors = S.getValors();
        bateria = S.bateria;
        estat = S.estat;
    }
    
    //Mètodes per consultar valors
    //Mètodes getters getX...
    int getId() const
    {
        return Id;
    }
    
    string getTipus() const
    {
        return tipus;
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
    
    double getBateria() const
    {
        return bateria;
    }
    
    bool getEstat() const
    {
        return estat;
    }
    //Mètodes per modificar valors
    //Mètodes setters setX...
    void setId(int pId)
    {
        Id = pId;
    }
    
    void setTipus(string pTipus)
    {
        tipus = pTipus;
    }
    
    void addValor(double v)
    {
        valors.push_back(v);
    }
    
    //Modificar nivell bateria
    void setBateria(double pBateria)
    {
        bateria = pBateria;
    }
    
    //Modificar l'estat
    void encen()
    {
        if (!estat) //està apagat
        {
            estat = true; //s'encèn
        }
    }
    void apagar()
    {
        if (estat) //està encès
        {
            estat = false; //l'apaguem
        }
    }
    
    //OPERADOR D'ASSIGNACIÓ, ha de ser SEMPRE MEMBRE DE LA CLASSE
    Sensor& operator = (const Sensor& S) //assigna el sensor a l'objecte
    {
        if (this != &S)//fem assignació
        {
            //copiar informació
            Id = S.getId();
            tipus = S.getTipus();
            valors = S.getValors();
            bateria = S.getBateria();
            estat = S.getEstat();
        }
        return (*this);
    }
    
    //OPERADOR ==
    //1. COM A MEMBRE DE LA CLASSE
    //2. COM A MEMBRE AMIC, FUNCIÓ AMIGA, MÈTODE AMIC
    
    //COM A MEMBRE
    bool operator == (const Sensor& S)
    {
        //comparem component-wise, camp a camp
        return (Id == S.getId() and tipus == S.getTipus() and valors == S.getValors() and bateria == S.getBateria() and estat == S.getEstat());
    }
    
    //COM A MEMBRE AMIC (FRIEND)
    //friend permet que un mètode tingui accés directe a les dades de la classe
    bool operator == (Sensor& S)
    {
        //comparem component-wise, camp a camp
        return (Id == S.Id and tipus == S.tipus and valors == S.valors and bateria == S.bateria and estat == S.estat);
    }
    
    //Operador de comparació, comparem segons el valor mitja dels seus valors
    bool operator < (const Sensor& S)
    {
        return (getAverage() < S.getAverage());
    }
    
    //Operador d'entrada (el de l'extracció) >>
    friend istream& operator >> (istream& entrada, Sensor& S)
    {
       cout << "Introdueix Id:" << endl;
        entrada >> S.Id;
        cout << "Introdueix tipus: " << endl;
        entrada >> S.tipus;
        
        //CREAR EL VECTOR
       cout << "Quants valors en té?";
        vector<double> v;
        int n; entrada >> n;
       cout << "Introdueix " << n << " valors reals del vector:" << endl;
        for (int i=0; i<n;i++)
        {
            double x;
            entrada >> x;
            v.push_back(x);
        }
        S.valors = v;
        
       cout << "Nivell bateria?";
        entrada >> S.bateria;
       cout << "Estat (encès=1,apagat=0)?";
        int x; entrada >> x;
        if (x)
        {
            S.estat = true;
        }
        else
        {
            S.estat = false;
        }
        
        return entrada;
    }
    
    //Escriure un sensor per canal de sortida
    friend ostream& operator << (ostream& sortida, Sensor S)
    {
        sortida << "----------------------"<< endl;
        sortida << "Fitxa del sensor: " << endl;
        sortida << "Id: " << S.Id << endl;
        sortida << "Tipus: " << S.tipus << endl;
        if ((S.valors).size()>0)
        {
            sortida << "Nb valors del vector: " << (S.valors).size() << endl;
            sortida << "Valors del vector: " << endl;
            for (int i = 0; i< (S.valors).size(); i++)
            {
                sortida << S.valors[i] << ' ';
            }
            sortida << endl;
            sortida << "Mitjana de valors: " << S.getAverage() << endl;
            sortida << "Nivell bateria: " << S.getBateria() << '%' << endl;
            string estat_sens = S.getEstat() ? "Encès" : "Apagat";
            sortida << "Estat: " << estat_sens << endl;
            sortida << endl <<"----------------------"<< endl;
       }
        return sortida;
    }
};
    
/*
b)    [4 PUNTS]  Definiu i implementeu una classe AnellesSensors per mantenir i gestionar una estructura dinàmica dels sensors, organitzat en N anelles (utilitzeu la classe Sensor).
*/
    
class AnellesSensors{
    
    //Dades
    int N; //nombre d'anelles de sensors
    Sensor** AS; //taula d'apuntadors de tipus Sensor
    
public:
    //Constructor per defecte
    AnellesSensors(){}
    
    //Constructor amb paràmetre
    AnellesSensors(ifstream& fsensors)
    {
        fsensors >> N;
        cout << "N=" << N << endl;
        
        AS = new Sensor*[N];
        for (int i = 0; i < N; i++)
        {
            AS[i] = new Sensor[N + 2*i];
            
        }
        for (int i = 0; i < N; i++)
        {
            cout << "Anella " << i << endl;
            for (int j = 0; j < N + 2*(i+1); j++)
            {
                fsensors >> AS[i][j];
                cout << "Sensor num. " << j << " de la anella " << i << endl;
                cout << AS[i][j];
            }
        }
    }

    //Constructor de còpia
    AnellesSensors(const AnellesSensors& AnSen)
    {
        N = AnSen.N;
        
        AS = new Sensor*[N];
        for (int i = 0; i < N; i++)
        {
            AS[i] = new Sensor[N+2*i];
            
        }
        //Ara podem assignar a les cel.les de la matriu
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N + 2*(i+1) ; j++)
            {
                AS[i][j] = AnSen.AS[i][j];
            }
        }
    }
    
    //Destructor, és necessari ja que el constructor ha adquirit memòria
    ~AnellesSensors()
    {
        for(int i = 0; i < N; i++)
        {
            delete[] AS[i]; //alliberar memòria
        }
        
        delete[] AS; //alliberar memòria
    }
    
    //Consultar nombre d'ANELLES
    int getN() const
    {
        return N;
    }
    
    //Un mètode per consultar el nombre dels sensors d’una anella concreta que estan encesos .
    int encesosA(int i) const
    {
        int compt = 0;
        for (int j = 0; j < N + 2*(i+1); j++)
        {
            if (AS[i][j].getEstat())
            {
                compt++;
            }
        }
        return compt;
    }
    
   // Un mètode per consultar el nombre dels sensors que estan encesos de tota la xarxa.
    int encesosX() const
    {
        int s = 0;
        for (int i = 0; i < N; i++)
        {
            s += encesosA(i);
        }
        return s;
    }
   // Un mètode que, pel número d'una anella, apaga tots els sensors de l'anella que tenen un nivell de bateria més baix que 10%.
    void apagaA(int i)
    {
        for (int j = 0; j < N + 2*(i+1); j++)
        {
            if (AS[i][j].getBateria() < 10.0)
            {
                AS[i][j].apagar();
            }
        }
    }
    
    //Un mètode que reb d'entrada un caràcter char posicio i en cas que posició és igual a 'p' apaga tots els sensors de les anelles de posicions parells que tenen un nivell de bateria més baix que 10% i si posició és igual a 's' apaga tots els sensors de les anelles de posicions senars  que tenen un nivell de bateria més baix que 10%.
    void apagarX(char posicio)
    {
        if (posicio == 'p')
        {
            for (int i = 0; i < N; i = i + 2)
            {
                apagaA(i);
            }
        }
        else if (posicio == 's')
        {
            for (int i = 1; i < N; i = i + 2)
            {
                apagaA(i);
            }
        }
    }
    
    //Operador d'extracció >> per llegir dades des del fitxer
    //Nota: el paràmetre entr pot ser un fitxer ifstream
    friend istream& operator >> (istream& entr,AnellesSensors& AnSen)
    {
        
        //Primer llegim la N
        cout << "Introdueix el nombre d'anelles N:" << endl;
        entr >> AnSen.N;
                
        //Es crea la taula dinàmicament, adquireix memòria
        //S'ha de fer com a una taula de taules
        AnSen.AS = new Sensor*[AnSen.N];
        
        //Adquirim memòria per cada fila
        for(int i = 0; i < AnSen.N; i++)
        {
            AnSen.AS[i] = new Sensor[AnSen.N + 2*(i+1)];
        }
        //Ara podem llegir dades del fitxer
        for (int i = 0; i < AnSen.N; i++)
        {
        cout << "Introdueix les dades de " << AnSen.N+2*(i+1) << " dels sensors de l'anella " << i+1 << endl;
        for (int j = 0; j < AnSen.N+2*(i+1); j++)
            {
                entr >> AnSen.AS[i][j];
        cout << "------------" << endl;
        cout <<AnSen.AS[i][j];
        cout << "------------" << endl;
            }
        }
        return entr;
    }
    
    friend ostream& operator << (ostream& os, const AnellesSensors& AnSen)
    {
        os << "La informació de les anelles dels sensors és:" << endl;
        os << "Nombre d'anelles: " << AnSen.getN() << endl;
        os << "Nombre de sensors en cada anellas: " << endl;
        for (int i = 0; i < AnSen.getN(); i++)
        {
            os << "----------------------------" << endl;
            os << "Anella " << i << ':' << endl;
            os << "Sensors encesos: " << AnSen.encesosA(i) << endl;
            os << "Sensors apagats: " << AnSen.getN() + 2*(i+1) - AnSen.encesosA(i) << endl;
            os << "----------------------------" << endl;
        }
        os << "Total sensors encesos: " << AnSen.encesosX() << endl;

        return os;
    }

};

int main() {
        
    // ifstream fsensors("sensors.txt");
    //AnellesSensors AnSen(fsensors);
    AnellesSensors AnSen;
    cin >> AnSen;
    cout << AnSen;
    cout << "Apaguem una anella...la 1a:" << endl;
    AnSen.apagaA(0);
        
    cout << AnSen;

    return 0;
}