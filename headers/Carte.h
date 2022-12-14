#pragma once

#include <iostream>
#include <string>

#include "enums.h"

class Carte
{
    int id;
    std::string nom;
    TypeBatiment type;
    int prix;

  public:
    Carte();
    Carte(int i, std::string n, TypeBatiment t, int p);
    ~Carte();
    std::ostream& toString() const;
    //accessors
    int getId() const;
    std::string getNom() const;
    TypeBatiment getType() const;
    int getPrix() const;
};
