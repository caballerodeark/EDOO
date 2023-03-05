
#include <fstream>
using namespace std;

int main() {
   ifstream F("doc.txt");
   ofstream G("doc-nc.txt");
   string lin;
   while (getline(F, lin)) {
      if (!(lin[0] == '/' and lin[1] == '/')) {
         G << lin << endl;
      }
   }
}