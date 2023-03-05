
#ifndef FECHA_H
#define FECHA_H
#include <vector>

class Fecha 
{
  int _dia, _mes, _anyo;
  vector<int> _blablah;
  public:
  Fecha(int dia, int mes, int anyo);
  int dia() const { return _dia; }
  int mes() const { return _mes; }
  int anyo() const { return _anyo; }
};

#endif