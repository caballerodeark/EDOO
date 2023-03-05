#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

double mitjana(vector<double> numeradors)
{
    double totnum;
    for(int k=1; k<numeradors.size(); k++)
    {
        totnum+=numeradors[k];
    }
    return totnum/numeradors.size();
}

int main()
{
    vector<double> numeradors;
    double num, mitj;
    int nummay=0;
    while(cin>>num)
    {
        numeradors.push_back(num);
    }
    mitj = mitjana(numeradors);
    for(int k=1; k<numeradors.size(); k++)
    {
        if(numeradors[k]>mitj) nummay++;
    }
    cout<<nummay;
}