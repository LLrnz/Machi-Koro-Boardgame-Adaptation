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
    // Carte();
    Carte(int i, string n, TypeBatiment t, int p);
    ~Carte();
    std::ostream& toString() const;
    //accessors
    int getId() const;
    std::string getNom() const;
    TypeBatiment getType() const;
    int getPrix() const;
};
