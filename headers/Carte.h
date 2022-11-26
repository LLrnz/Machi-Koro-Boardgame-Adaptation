#pragma once

#include <iostream>
#include <string>

#include "enums.h"

class Carte
{
    int id;
    std::string nom;
    EnumType type;
    int prix;

  public:
    Carte(int i, std::string n, EnumType t, int p) :id(i),nom(n),type(t),prix(p) {};
    ~Carte();
    std::ostream& toString() const;
};
