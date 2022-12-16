#pragma once
#include <iostream>
#include <string>
#include "enums.h"
using namespace std;

class Carte
{
    int id;
    string nom;
    int prix;

  public:
    // Carte();
    Carte(int i, string n, int p);
    ~Carte() = default;
    std::ostream& toString() const;
    //accessors
    int getId() const{return id;};
    std::string getNom() const {return nom;};
    TypeBatiment getType() const;
    int getPrix() const {return prix;};
};
