
#include <fstream>
#include <iostream>
using namespace std;

int main() {
   int n;
   ofstream G("grafica.txt");
   while (cin >> n) {
      string s(n, '*');
      G << s << endl;
   }
}
