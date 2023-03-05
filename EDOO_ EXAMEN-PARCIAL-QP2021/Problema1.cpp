#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;

class TextSimil
{

    vector<string> text1, text2, pacom1, pacom2, pacom, padif;

    public:
    //Constructors:
    
    TextSimil();    //Per defecte

    TextSimil(vector<string> text1, vector<string> text2) //Per paràmetres
    {
        this->text1;
        this->text2;
    }

    TextSimil(const TextSimil& P)   //Per cópia
    {
        text1=P.text1;
        text2=P.text2;
    }

    //Métodes consultors:

    void paraules_comunes() //Calcular el vector de les paraules comunes en els dos texts.
    {
        bool encontrado=false;
        for(int k=1; k<text1.size(); k++)
        {
            for(int t=1; t<pacom1.size() || encontrado==true; t++)
            {
                if(text1[k]==pacom1[t]) encontrado=true;
            }
            if(!encontrado) pacom1.push_back(text1[k]);
        }
        encontrado=false;
        for(int k=1; k<text2.size(); k++)
        {
            for(int t=1; t<pacom2.size() || encontrado==true; t++)
            {
                if(text2[k]==pacom2[t]) encontrado=true;
            }
            if(!encontrado) pacom2.push_back(text2[k]);
        }
    }

    int pcomunes1() //Tornar nombre de paraules comunes de Text1
    {
        return pacom1.size();
    }

    int pcomunes2() //Tornar nombre de paraules comunes de Text2
    {
        return pacom2.size();
    }

    double index() //Tornar index de similitud dels dos textos (comunes/diferents)
    {
        int comunes=0, diferents=0;
        bool encontrado=false;
        paraules_comunes();
        for(int k=1; k<pacom1.size(); k++)
        {
            for(int t=1; t<pacom2.size(); t++)
            {
                if(pacom1[k]==pacom2[t]) 
                {
                    comunes++;
                    pacom.push_back(pacom1[k]);
                    encontrado=true;
                }
            }
            if(!encontrado)
            {
                diferents++;
                padif.push_back(pacom1[k]);
            }
            encontrado=false; 
        }

        return (comunes/diferents);
    }

    //Metodes modificadors:

    void Pulir(vector<string>& Text)    //Eliminar paraules consecutives repetides d’un text
    {
        for(int k=1; k<Text.size(); k++)
        {
            if(Text[k]==Text[k++]) 
            {
                Text[k].erase();
                k--;
            }
        }
    }

    //Operadors:

    friend bool operator <=(TextSimil TS1, TextSimil TS2)   //<= (cert, quan l’índex de similitud de un objecte TS1 de la classe TextSimil és <= que el d’un objecte TS2 de la classe TextSimil)
    {
        if(TS1.index()==TS2.index()) return true;
        else return false;
    }

    friend ostream& operator <<(ostream& os, vector<string> Text)  //<< per escriure un text a un fitxer de sortida (haver eliminat les paraules consecutives repetides)
    {
        TextSimil T;
        T.Pulir(Text);
        for(int k=1; k<Text.size(); k++)
        {
            os<<Text[k];
        }
        os<<endl;
    }
};

int main()
{
    TextSimil TS,TS1,TS2;
}