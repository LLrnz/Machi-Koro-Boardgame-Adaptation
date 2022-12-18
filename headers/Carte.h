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
    virtual ~Carte();
    virtual std::string to_string() const =0;
    //accessors
    int getId() const;
    std::string getNom() const;
    int getPrix() const;
    virtual void acheter() =0;
};
