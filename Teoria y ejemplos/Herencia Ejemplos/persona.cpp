
#include <iostream>
using namespace std;

class Persona
{
  string _nombre, _apellido1, _apellido2;
  string _DNI;
  int _edad;
protected: // 6) Los miembros 'protected' son accesibles por las clases 
           //    derivadas pero nadie más.
  bool _casado;

public:
  Persona(string nombre, string a1, string a2,
          string DNI, int edad);
  string nombre() const { return _nombre; }
  int edad() const { return _edad; }

  string nombre_completo() const;

  void muestra_info() const;
};

Persona::Persona(string nombre, string a1, string a2,
                 string DNI, int edad)
{
  _nombre = nombre;
  _edad = edad;
  _apellido1 = a1;
  _apellido2 = a2;
  _DNI = DNI;
}

string Persona::nombre_completo() const
{
  return _nombre + " " + _apellido1 + " " + _apellido2;
}

void Persona::muestra_info() const
{
  cout << "Nombre: " << nombre_completo() << endl;
  cout << "DNI:    " << _DNI << endl;
  cout << "Edad:   " << _edad << endl;
  cout << "Casado: ";
  if (_casado) {
    cout << "si";
  } else {
    cout << "no";
  }
  cout << endl;
}

struct Fecha
{
  int dia, mes, anyo;
};

// 1) La herencia entre clases require poner:
//  class Derivada : public Base { ... }
class Empleado : public Persona
{
  Fecha _contratacion;
  double _salario;

public:
  // 2) El constructor _NO_ se hereda -> tengo que hacer uno.
  Empleado(string nombre, string a1, string a2,
           string DNI, int edad, Fecha contr, double s);

  // 4) Sobrecargamos el método 'muestra_info' para poder
  //    mostrar no solamente los datos de la persona sino los añadidos
  //    del empleado.
  void muestra_info() const;
};

Empleado::Empleado(string nombre, string a1, string a2,
                   string DNI, int edad, Fecha contr, double s)
    // 3) Para inicializar la parte "base" (en este caso la Persona)
    //    hay que llamar al constructor aquí
    : Persona(nombre, a1, a2, DNI, edad)
{
  _casado = false; // 6) ... puedo acceder a miembros 'protected'.
  _contratacion = contr;
  _salario = s;
}

void Empleado::muestra_info() const
{
  // 5) Llamamos al método 'muestra_info' de Persona para no repetir
  //    el código que ya hemos hecho. (Si no pones 'Persona::' la llamada
  //    es recursiva).
  Persona::muestra_info();
  cout << "Salario: " << _salario << endl;
  cout << "Contratacion: "
       << _contratacion.dia << '/' << _contratacion.mes
       << '/' << _contratacion.anyo << endl;
}

int main()
{
  Persona bond("James", "Bond", "García", "07007007X", 27);
  bond.muestra_info();
  Empleado bond2("James", "Bond", "García", "07007007X", 27,
  {5, 10, 1957}, 180000);
  bond2.muestra_info();
}
