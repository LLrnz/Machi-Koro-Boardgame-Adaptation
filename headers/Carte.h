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
    std::string to_string() const;
    //accessors
    int getId() const;
    std::string getNom() const;
    TypeBatiment getType() const;
    int getPrix() const;
};
