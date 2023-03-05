#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

void treu(vector<string>& linia)
{
    for(int k=1; k<linia.size(); k++)
    {
        if(linia[k].substr(0,1)=="//") 
        {
            linia[k].erase();
            k--;
        }
    }
}

vector<string> t(ifstream doc)
{
    vector<string> linia;
    string palabra;
    while(doc>>palabra)
    {
        getline(doc,palabra);
        linia.push_back(palabra);
    }
    return linia;
}

int main()
{
    ifstream doc("doc.txt");
    ofstream sal("doc-nc.txt");
    vector<string> linies;
    linies = t(doc);
    treu(linies);
    for(int k=1; k<linies.size(); k++)
    {
        sal<<linies[k]<<endl;
    }
}