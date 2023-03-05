#include <map>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void correccio(ifstream& scriptum, ifstream& twith)
{
    map<string,string> correc;
    pair<string,string> newl;
    map<string,int> freqs;
    pair<string,int> newfreq;
    string abrev, correc;
    int freq;
    while(scriptum>>abrev>>" ">>correc)
    {

    }
}