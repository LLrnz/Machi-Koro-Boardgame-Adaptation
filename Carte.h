#ifndef CARTE_H
#define CARTE_H
#include <iostream>


class Carte
{
    int id;
    string nom;
    EnumType type;
    int prix;

  public:
      Carte(int i, string n, EnumType t, int p):id(i),nom(n),type(t),prix(p);
      ~Carte();
      ostream& tostring() const;
};

#endif // CARTE_H
