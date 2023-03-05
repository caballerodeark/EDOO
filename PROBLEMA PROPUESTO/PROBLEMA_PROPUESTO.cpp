#include <map>
#include <fstream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

class CENTRE_ESPORTIU
{
    map<string,SOCI> centre;
    queue <SOCI> sol;
    public:
    //Constructors:
    CENTRE_ESPORTIU(); //Per defecte
    CENTRE_ESPORTIU(map <string, SOCI> centre,queue <SOCI> sol) //Per parametres
    {
        this->centre = centre;
        this->sol = sol;
    }
    CENTRE_ESPORTIU(CENTRE_ESPORTIU& C) //De copia
    {
        this->centre = C.centre;
        this->sol = C.sol;
    }
    //API
    //Metodes get:
    map<string,SOCI> getcentre() 
    {
        return centre;
    }
    queue <SOCI> getsol()
    {
        return sol;
    }
    //Metodes set:
    map<string,SOCI> getcentre(map<string,SOCI> centre) 
    {
        this->centre = centre;
    }
    queue <SOCI> getsol(queue <SOCI> sol)
    {
        this->sol = sol;
    }
    //Metodes:
    //Afegir
    void afegirsoci(pair<string,SOCI> C) //Afegir nou soci al map
    {
        centre.insert(C);
    }
    void afegirsol(SOCI S) //Afegir nova solicitud de soci al queue
    {
        sol.push(S);
    }
    //Eliminar
    void eliminasoci(string ID)
    {
        centre.erase(ID);
    }
    void eliminasol(SOCI S)
    {
        
    }
};

class SOCI
{
    
};