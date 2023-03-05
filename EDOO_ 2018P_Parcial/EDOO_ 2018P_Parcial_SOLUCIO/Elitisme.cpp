
#include <iostream>
#include <vector>
using namespace std;

int main() {
   vector<int> v;
   int n, suma = 0;
   while (cin >> n) {
      v.push_back(n);
      suma += n;
   }
   const double media = double(suma)/double(n);
   int cont = 0;
   for (int i = 0; i < v.size(); i++) {
      if (v[i] > media) cont++;
   }
   cout << cont << endl;
}

