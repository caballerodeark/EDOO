
#include <iostream>
using namespace std;

struct Vehiculo {
  string modelo;
  double peso;
  void muestra() const;
};

void Vehiculo::muestra() const {
  cout << "Modelo: " << modelo << endl;
  cout << "Peso: " << peso << endl;
}

struct Coche : Vehiculo {
  int npuertas;
  string matricula;
};

struct CocheGasolina : Coche {
  double cilindrada;
};

struct CocheElectrico : Coche {
  double tamanyo_bateria;
};

int main() {
  Vehiculo v;
  Coche c;
  CocheGasolina g;
  CocheElectrico e;
  v.modelo = "<ni idea>";
  v.peso = 1000;
  c.modelo = "<un coche>";
  c.peso = 700;
  e.modelo = "Tesla Model 3";
  e.tamanyo_bateria = 89;
  v.muestra();
  c.muestra();
  g.muestra();
  e.muestra();
}