#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    ifstream seq("grafica.txt");
    int n;
    vector<int> num;
    while(seq>>n) num.push_back(n);
    for(int k=1; k<num.size(); k++)
    {
        for(int i=0; i==num[k]; i++)
        {
            cout<<"*";
        }
        cout<<endl;
    }
}