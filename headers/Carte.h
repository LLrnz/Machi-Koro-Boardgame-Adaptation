#pragma once

#include <iostream>
#include <string>

#include "enums.h"

using namespace std;

class Carte
{
    int id;
    string nom;
    TypeBatiment type;
    int prix;

  public:
    Carte();
    Carte(int i, string n, TypeBatiment t, int p);
    ~Carte();
    string getNom() const {return nom;}
    int getId() const {return id;}
    
    ostream& toString() const;
};
